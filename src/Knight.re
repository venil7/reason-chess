open Coord;

open Game;

let possibleMoves =
    (coord: coord, board: board, player: player)
    : list(coord) => {
  let moves = [
    coord |> next(North) |> next(NorthEast),
    coord |> next(North) |> next(NorthWest),
    coord |> next(East) |> next(NorthEast),
    coord |> next(East) |> next(SouthEast),
    coord |> next(South) |> next(SouthEast),
    coord |> next(South) |> next(SouthWest),
    coord |> next(West) |> next(SouthWest),
    coord |> next(West) |> next(NorthWest),
  ];
  moves |> List.filter(Piece.isWalkable(board, player));
};