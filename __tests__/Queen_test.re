open Jest;

open Game;

open Board;

open Expect;

describe("Queen", () => {
  let board = empty() |> default;
  test("possible steps", () => {
    let board = board |> setAt(Queen, Black, Coord(3, 3));
    let moves =
      Queen.possibleMoves(Coord(3, 3), board, Black) |> Array.of_list;
    expect(moves)
    |> toBeSupersetOf([|
         Coord(2, 2),
         Coord(4, 2),
         Coord(2, 4),
         Coord(1, 5),
         Coord(0, 6),
         Coord(4, 4),
         Coord(5, 5),
         Coord(6, 6),
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