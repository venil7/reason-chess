open Game;

open Coord;

exception InvalidMove(string);

let side = 8;

let empty = () : board => Array.make(side * side, Empty) |> Array.to_list;

let default = (board: board) : board =>
  board
  |> List.mapi((idx, _) =>
       switch (idx, false) {
       | (0 | 7, _) => Occupied(Black, Rook)
       | (1 | 6, _) => Occupied(Black, Knight)
       | (2 | 5, _) => Occupied(Black, Bishop)
       | (3, _) => Occupied(Black, Queen)
       | (4, _) => Occupied(Black, King)
       | (8 | 9 | 10 | 11 | 12 | 13 | 14 | 15, _) => Occupied(Black, Pawn)
       | (48 | 49 | 50 | 51 | 52 | 53 | 54 | 55, _) => Occupied(White, Pawn)
       | (59, _) => Occupied(White, Queen)
       | (60, _) => Occupied(White, King)
       | (56 | 63, _) => Occupied(White, Rook)
       | (57 | 62, _) => Occupied(White, Knight)
       | (58 | 61, _) => Occupied(White, Bishop)
       | _ => Empty
       }
     );

let at = (coord: coord, board: board) : cell => {
  let index = indexOfCoord(coord);
  List.nth(board, index);
};

let makeMove = ({prev, next}: move, board: board) => {
  let prevIndex = indexOfCoord(prev);
  let nextIndex = indexOfCoord(next);
  board
  |> List.mapi((index, cell) =>
       switch index {
       | idx when idx == prevIndex && cell != Empty => Empty
       | idx when idx == prevIndex =>
         raise(InvalidMove("cant move empty cell"))
       | idx when idx == nextIndex => board |> at(prev)
       | _ => cell
       }
     );
};
/* let possibleMoves = (coord: coord, board: board) : list(move) => {
     let cell = board |> at(coord);
     switch cell {
     | Occupied(Black, Pawn) => []
     | Occupied(White, Pawn) => []
     | _ => []
     };
   }; */