open Jest;

open Game;

open Board;

open Expect;

describe("Bishop", () => {
  let board = empty() |> default;
  test("possible steps", () => {
    let board = board |> setAt(Bishop, Black, Coord(3, 3));
    let moves =
      Bishop.possibleMoves(Coord(3, 3), board, Black) |> Array.of_list;
    expect(moves)
    |> toBeSupersetOf([|
         Coord(2, 2),
         Coord(4, 2),
         Coord(2, 4),
         Coord(1, 5),
         Coord(0, 6),
         Coord(4, 4),
         Coord(5, 5),
         Coord(6, 6)
       |]);
  });
});