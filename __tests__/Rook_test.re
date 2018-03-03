open Jest;

open Game;

open Board;

open Expect;

describe("Rook", () => {
  let board = empty() |> default;
  test("possible steps", () => {
    let board = board |> setAt(Rook, Black, Coord(3, 3));
    let moves = Rook.possibleMoves(Coord(3, 3), board, Black) |> Array.of_list;
    expect(moves)
    |> toBeSupersetOf([|
         Coord(0, 3),
         Coord(1, 3),
         Coord(2, 3),
         Coord(4, 3),
         Coord(5, 3),
         Coord(6, 3),
         Coord(7, 3),
         Coord(3, 2),
         Coord(3, 4),
         Coord(3, 5),
         Coord(3, 6)
       |]);
  });
});