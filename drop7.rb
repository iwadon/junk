class Board
  WALL = :WALL
  STONE = :STONE
  BROKEN_STONE = :BROKEN_STONE
  PIECE = {1 => "1", 2 => "2", 3 => "3", 4 => "4", 5 => "5", 6 => "6", 7 => "7", nil => " ", WALL => "=", STONE => 'O', BROKEN_STONE => '*'}

  attr_reader :current_piece

  def initialize
    @board = []
    ((7 * 7) .. (7 * 7 + 6)).each do |i|
      @board[i] = WALL
    end
    srand
    next_piece
  end

  def next_piece
    @current_piece = 1 + rand(7)
  end

  def show
    puts("abcdefg")
    8.times do |y|
      7.times do |x|
        putc(PIECE[@board[y * 7 + x]])
      end
      puts
    end
  end

  def put_piece(pos)
    raise "bas pos" unless pos and puttable?(pos)
    pos_ = pos
    while not @board[pos_ + 7]
      pos_ += 7
    end
    @board[pos_] = @current_piece
  end

  def puttable?(pos)
    @board[pos].nil?
  end

  def game_over?
    7.times do |x|
      return false if puttable?(x)
    end
    true
  end
end

if __FILE__ == $0
  board = Board.new
  loop do
    board.show
    break if board.game_over?
    print("#{Board::PIECE[board.current_piece]}> ")
    STDOUT.flush
    pos = gets
    begin
      board.put_piece("abcdefg".index(pos[0]))
      board.next_piece
    rescue RuntimeError => e
      puts("Error: #{e}")
    end
  end
  puts("Game Over...")
end
