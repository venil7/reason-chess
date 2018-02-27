open Coord;

open Game;

let pieceWeight = 1.0;

let coefficient = 0.01;

let weight = (coord: coord, player: player) : float =>
  switch (coord, player) {
  | (Coord(_, y), Black /*cpu*/) =>
    pieceWeight -. float_of_int(y) *. coefficient
  | (Coord(_, y), White /*human*/) =>
    pieceWeight -. (7.0 -. float_of_int(y)) *. coefficient
  };

/* let f = Piece.f; */

let possibleMoves =
    (coord: coord, board: board, player: player)
    : list(coord) =>
  switch player {
  | Black => {
    let forward = coord |> next(South);
    let moves = [forward, coord |> next(SouthEast), coord |> next(SouthWest)];
    switch coord {
    | Coord(_,1) => [forward |> next(South),...moves]
    | _ => moves;
    }
  }
  | White => []
  };