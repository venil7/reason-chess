open Game;

exception InvalidIndex(int);

exception InvalidCoord(coord);

let validIndex = (index: int) => index >= 0 && index <= 63;

let isValid = (coord: coord) : bool =>
  switch (coord) {
  | Coord(col, row) when (col >= 0 && col <= 7) && row >= 0 && row <= 7 =>
    true
  | _ => false
  };

let coordOfIndex = (index: int) : coord =>
  switch (index) {
  | i when validIndex(i) => Coord(index mod 8, index / 8)
  | _ => raise(InvalidIndex(index))
  };

let indexOfCoord = (coord: coord) : int =>
  switch (coord) {
  | Coord(col, row) when isValid(coord) => row * 8 + col
  | _ => raise(InvalidCoord(coord))
  };

let next = (direction: direction, coord: coord) : coord =>
  switch (direction, coord) {
  | (North, Coord(x, y)) => Coord(x, y - 1)
  | (NorthEast, Coord(x, y)) => Coord(x + 1, y - 1)
  | (East, Coord(x, y)) => Coord(x + 1, y)
  | (SouthEast, Coord(x, y)) => Coord(x + 1, y + 1)
  | (South, Coord(x, y)) => Coord(x, y + 1)
  | (SouthWest, Coord(x, y)) => Coord(x - 1, y + 1)
  | (West, Coord(x, y)) => Coord(x - 1, y)
  | (NorthWest, Coord(x, y)) => Coord(x - 1, y - 1)
  };

let at = (coord: coord, board: board) : cell => {
  let index = indexOfCoord(coord);
  List.nth(board.cells, index);
};