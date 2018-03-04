open Jest;

open Game;

open Board;

open Expect;

describe("Knight", () => {
  let board = empty() |> default;
  test("possible steps (cornercase, friendly fire)", () => {
    let board' = board |> makeMove({prev: Coord(7, 1), next: Coord(7, 2)});
    let moves =
      Knight.possibleMoves(Coord(6, 0), board', Black) |> Array.of_list;
    expect(moves) |> toBeSupersetOf([|Coord(5, 2)|]);
  });
  test("possible steps (2 attacks)", () => {
    let board' = board |> makeMove({prev: Coord(6, 0), next: Coord(3, 4)});
    let moves =
      Knight.possibleMoves(Coord(3, 4), board', Black) |> Array.of_list;
    expect(moves)
    |> toBeSupersetOf([|Coord(2, 2), Coord(4, 2), Coord(2, 6), Coord(4, 6)|]);
  });
});