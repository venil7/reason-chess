let default: (ReasonChess.Game.board) => ReasonChess.Game.board;
let empty: (unit) => ReasonChess.Game.board;
let iterate: (ReasonChess.Game.board) => list(ReasonChess.Game.cell);
let makeMove:
  (ReasonChess.Game.move, ReasonChess.Game.board) => ReasonChess.Game.board;
let possiblePieceMoves:
  (ReasonChess.Game.coord, ReasonChess.Game.piece, ReasonChess.Game.player,
  ReasonChess.Game.board) => list(ReasonChess.Game.move);
let possibleMoves:
  (ReasonChess.Game.player, ReasonChess.Game.board) =>
  list(ReasonChess.Game.move);
let cpu:
  (ReasonChess.Game.board, ~player: ReasonChess.Game.player=?, ~depth: 
  int=?, unit) => ReasonChess.Game.board;
let minimax:
  (ReasonChess.Game.board, ReasonChess.Game.player, int,
  ~move: ReasonChess.Game.move=?, unit) => ReasonChess.Game.eval;
