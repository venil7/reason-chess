open Jest;

open Game;

open Board;

open Expect;

describe("King", () => {
  let board = empty() |> default;
  test("possible steps", () => {
    let board' = board |> makeMove({prev: Coord(4, 1), next: Coord(4, 2)});
    let moves =
      King.possibleMoves(Coord(4, 0), board', Black) |> Array.of_list;
    expect(moves) |> toBeSupersetOf([|Coord(4, 1)|]);
  });
});