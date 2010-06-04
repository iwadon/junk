# -*- coding: utf-8 -*-
class Board
  BLACK = :BLACK
  WHITE = :WHITE
  PIECE = {BLACK => 'X', WHITE => 'O', nil => ' '}

  attr_reader :side

  def initialize
    @board = []
    @side = BLACK
    put(:d4, :e4, :e5, :d5)
  end

  def put(*positions)
    positions.each do |pos|
      @board[name2idx(pos)] = @side
      #puts("#{pos} #{PIECE[@side]}")
      @side = @side == BLACK ? WHITE : BLACK
    end
  end

  def show
    puts(" abcdefgh")
    8.times do |y|
      print("#{y + 1}")
      8.times do |x|
        putc(PIECE[@board[y * 8 + x]])
      end
      puts
    end
  end

  def name2idx(name)
    x, y = name.downcase[0].ord, name[1].ord
    x -= 'a'.ord
    y -= '1'.ord
    y * 8 + x
  end
end

if __FILE__ == $0
  board = Board.new
  while true
    board.show
    STDOUT.print("#{board.side}: ")
    STDOUT.flush
    pos = STDIN.gets
    board.put(pos)
  end
end
