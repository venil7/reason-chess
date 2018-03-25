open Game;

open Coord;

open Player;

module PawnPiece = Piece.Make(Pawn);

module RookPiece = Piece.Make(Rook);

module KnightPiece = Piece.Make(Knight);

module BishopPiece = Piece.Make(Bishop);

module QueenPiece = Piece.Make(Queen);

module KingPiece = Piece.Make(King);

exception InvalidMove(string);

let side = 8;

let iterate = (board: board) : list(cell) => board.cells;

let empty = () : board => {
  let cells = Array.make(side * side, Empty) |> Array.to_list;
  {castling: (false, false), captured: [], cells, winner: None, moves: []};
};

let default = (board: board) : board => {
  let cells =
    board
    |> iterate
    |> List.mapi((idx, _) =>
         switch (idx, false) {
         | (0 | 7, _) => Occupied(Black, Rook)
         | (1 | 6, _) => Occupied(Black, Knight)
         | (2 | 5, _) => Occupied(Black, Bishop)
         | (3, _) => Occupied(Black, Queen)
         | (4, _) => Occupied(Black, King)
         | (8 | 9 | 10 | 11 | 12 | 13 | 14 | 15, _) => Occupied(Black, Pawn)
         | (48 | 49 | 50 | 51 | 52 | 53 | 54 | 55, _) =>
           Occupied(White, Pawn)
         | (59, _) => Occupied(White, Queen)
         | (60, _) => Occupied(White, King)
         | (56 | 63, _) => Occupied(White, Rook)
         | (57 | 62, _) => Occupied(White, Knight)
         | (58 | 61, _) => Occupied(White, Bishop)
         | _ => Empty
         }
       );
  {...board, cells};
};

let makeMove = (move: move, board: board) => {
  let {prev, next} = move;
  let prevIndex = indexOfCoord(prev);
  let nextIndex = indexOfCoord(next);
  let nextCell = board |> at(prev);
  let prevCell = board |> at(next);
  let cells =
    board
    |> iterate
    |> List.mapi((index, cell) =>
         switch (index) {
         /* move from */
         | idx when idx == prevIndex && cell != Empty => Empty
         /* trying to move emty cell */
         | idx when idx == prevIndex =>
           raise(InvalidMove("cant move empty cell"))
         /* move to */
         | idx when idx == nextIndex => nextCell
         /* default */
         | _ => cell
         }
       );
  switch (prevCell) {
  | Empty => {...board, cells, moves: [move, ...board.moves]}
  | Occupied(player, piece) => {
      ...board,
      cells,
      moves: [move, ...board.moves],
      winner: piece == King ? Some(opposite(player)) : None,
      captured: [(player, piece), ...board.captured],
    }
  };
};

let setAt = (piece: piece, player: player, coord: coord, board: board) : board => {
  let setIndex = indexOfCoord(coord);
  let cells =
    board
    |> iterate
    |> List.mapi((index, cell) =>
         switch (index) {
         | idx when idx == setIndex => Occupied(player, piece)
         | _ => cell
         }
       );
  {...board, cells};
};

let possiblePieceMoves =
    (coord: coord, piece: piece, player: player, board: board)
    : list(move) =>
  switch (piece) {
  | Pawn => PawnPiece.possibleMoves(coord, board, player)
  | Rook => RookPiece.possibleMoves(coord, board, player)
  | Knight => KnightPiece.possibleMoves(coord, board, player)
  | Bishop => BishopPiece.possibleMoves(coord, board, player)
  | Queen => QueenPiece.possibleMoves(coord, board, player)
  | King => KingPiece.possibleMoves(coord, board, player)
  };

let possibleMoves = (player: player, board: board) : list(move) =>
  board
  |> iterate
  |> List.mapi((index, cell) =>
       switch (cell) {
       | Occupied(player', piece) when player == player' =>
         board |> possiblePieceMoves(coordOfIndex(index), piece, player)
       | _ => []
       }
     )
  |> List.concat;