type coord =
  | Coord(int, int);

type path = list(coord);

exception InvalidIndex(int);

exception InvalidCoord(coord);

let validIndex = (index: int) => index >= 0 && index <= 63;

let validCoord = (coord: coord) : bool =>
  switch coord {
  | Coord(col, row) when (col >= 0 && col <= 7) && row >= 0 && row <= 7 => true
  | _ => false
  };

let coordOfIndex = (index: int) : coord =>
  switch index {
  | i when validIndex(i) => Coord(index mod 8, index / 8)
  | _ => raise(InvalidIndex(index))
  };

let indexOfCoord = (coord: coord) : int =>
  switch coord {
  | Coord(col, row) when validCoord(coord) => row * 8 + col
  | _ => raise(InvalidCoord(coord))
  };