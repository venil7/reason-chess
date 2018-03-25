type player =
  | Black
  | White;

type piece =
  | Pawn
  | Rook
  | Knight
  | Bishop
  | Queen
  | King;

type cell =
  | Empty
  | Occupied(player, piece);

type coord =
  | Coord(int, int);

type move = {
  prev: coord,
  next: coord,
};

type board = {
  cells: list(cell),
  castling: (bool, bool),
  captured: list((player, piece)),
  winner: option(player),
  moves: list(move),
};

type direction =
  | North
  | NorthEast
  | East
  | SouthEast
  | South
  | SouthWest
  | West
  | NorthWest;

type score = float;

type eval =
  | Eval(move, score);