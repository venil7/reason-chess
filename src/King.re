open Coord;

open Game;

let possibleMoves =
    (coord: coord, board: board, player: player)
    : list(coord) => {
  let moves = [
    coord |> next(North),
    coord |> next(NorthEast),
    coord |> next(East),
    coord |> next(SouthEast),
    coord |> next(South),
    coord |> next(SouthWest),
    coord |> next(West),
    coord |> next(NorthWest),
  ];
  moves |> List.filter(Piece.isWalkable(board, player));
};