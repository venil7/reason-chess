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

type board = {
  cells: list(cell),
  blackCastling: bool,
  whiteCastling: bool
};

type coord =
  | Coord(int, int);

type path = list(coord);

type direction =
  | North
  | NorthEast
  | East
  | SouthEast
  | South
  | SouthWest
  | West
  | NorthWest;

type move = {
  prev: coord,
  next: coord
};