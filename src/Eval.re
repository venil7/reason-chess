open Game;

open Coord;

let pawnWeight = (player: player, coord: coord) : score => {
  let pieceWeight = 1.0;
  let coefficient = 0.1;
  switch (coord, player) {
  | (Coord(_, 0), White) => 5.0 /* reaching this cell */
  | (Coord(_, 7), Black) => 5.0 /* pawn becomes queen */
  | (Coord(_, y), White) =>
    pieceWeight +. (7.0 -. float_of_int(y)) *. coefficient
  | (Coord(_, y), Black) => pieceWeight +. float_of_int(y) *. coefficient
  };
};

let weight = (player: player, coord: coord, piece: piece) : score =>
  switch (piece) {
  | Pawn => pawnWeight(player, coord)
  | Rook
  | Bishop => 2.0
  | Knight => 3.0
  | Queen => 5.0
  | King => 10.0
  };

let minimize = (Eval(_, score1), Eval(_, score2)) : int =>
  score1 > score2 ? 1 : score1 < score2 ? (-1) : 0;

let maximize = (Eval(_, score1), Eval(_, score2)) : int =>
  score2 > score1 ? 1 : score2 < score1 ? (-1) : 0;

let score = (board: board, player: player, depth: int) : score => {
  let score' =
    board.cells
    |> List.mapi((index, cell: cell) => (index, cell))
    |> List.fold_left(
         (acc, (index, cell)) =>
           switch (cell) {
           | Occupied(player', piece) when player' == player =>
             acc +. weight(player, coordOfIndex(index), piece)
           | Occupied(player', piece) when player' != player =>
             acc -. weight(player', coordOfIndex(index), piece)
           | _ => acc
           },
         0.0,
       );
  score' -. float_of_int(depth);
};