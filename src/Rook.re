open Game;

let pieceWeight = 2.0;

let weight = (_coord: coord, _player: player) : float => pieceWeight;

let possibleMoves = (coord: coord, board: board, player: player) : list(coord) =>
  coord |> Piece.allTheWays(board, player, [North, East, South, West]);