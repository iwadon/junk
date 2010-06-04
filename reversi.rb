# -*- coding: utf-8 -*-
# 参考:
# - http://soranoumi.net/diary/の『「リバーシのアルゴリズム」をRubyで』

class Board
  NONE = nil
  WALL = 0
  BLACK = 1
  WHITE = -1
  PIECE = {BLACK => 'X', WHITE => 'O', NONE => ' ', WALL => '+'}
  DIR = [[-10, 1 << 0], [-9, 1 << 1], [ 1, 1 << 2], [ 11, 1 << 3],
         [ 10, 1 << 4], [ 9, 1 << 5], [-1, 1 << 6], [-11, 1 << 7]]
  DIR_U, DIR_UR, DIR_R, DIR_DR, DIR_D, DIR_DL, DIR_L, DIR_UL = (0..7).to_a

  attr_reader :side

  def initialize
    reset
  end

  def reset
    @board = []
    @side = BLACK
    @board[0 .. 9] = WALL
    (1..8).each do |y|
      @board[y * 10 + 0] = WALL
      @board[y * 10 + 9] = WALL
    end
    @board[90 .. 99] = WALL
    @board[44] = WHITE
    @board[45] = BLACK
    @board[54] = BLACK
    @board[55] = WHITE
  end

  def put_pieces(*positions)
    positions.each do |pos|
      put_piece(pos)
    end
  end

  def put_piece(pos)
    dirs = puttable_dirs(pos)
    raise "bad pos" if dirs.zero?
    idx = name2idx(pos)
    @board[idx] = @side
    flip_pieces(idx, dirs)
    @side = -@side
  end

  def show
    puts(" abcdefgh")
    (1..8).each do |y|
      print("#{y}")
      (1..8).each do |x|
        putc(PIECE[@board[y * 10 + x]])
      end
      puts
    end
  end

  def name2idx(name)
    x, y = name[0].downcase.ord, name[1].ord
    x -= 'a'.ord - 1
    y -= '1'.ord - 1
    raise if x < 1 or x > 8
    raise if y < 1 or y > 8
    y * 10 + x
  end

  def puttable_dirs(pos)
    idx = name2idx(pos)
    return 0 if @board[idx]
    r = 0
    8.times do |i|
      r |= puttable_dir(idx, *DIR[i])
    end
    r
  end

  def puttable_dir(idx, dir, value)
    i = idx - dir
    return 0 if @board[i] != -@side
    begin
      i -= dir
    end while @board[i] == -@side
    @board[i] == @side ? value : 0
  end

  def flip_pieces(idx, dirs)
    8.times do |i|
      dir = DIR[i]
      flip_piece(idx, dir[0]) if (dirs & dir[1]) != 0
    end
  end

  def flip_piece(idx, dir)
    i = idx - dir
    while @board[i] == -@side
      @board[i] = @side
      i -= dir
    end
  end
end

if __FILE__ == $0
  board = Board.new
  while true
    board.show
    print("#{Board::PIECE[board.side]}: ")
    STDOUT.flush
    pos = gets
    begin
      board.put_piece(pos)
    rescue RuntimeError => e
      puts("Error: #{e}")
    end
  end
end
