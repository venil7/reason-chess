let weight: (ReasonChess.Game.coord, ReasonChess.Game.player) => float;

let possibleMoves:
  (ReasonChess.Game.coord, ReasonChess.Game.board, ReasonChess.Game.player) =>
  list(ReasonChess.Game.coord);