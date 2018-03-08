open Game;

let possibleMoves =
    (coord: coord, board: board, player: player)
    : list(coord) =>
  coord
  |> Piece.allTheWays(
       board,
       player,
       [NorthEast, NorthWest, SouthEast, SouthWest],
     );