open Jest;

open Game;

open Board;

open Minimax;

open Expect;

describe("Eval", () => {
  let board = empty() |> default;
  let depth = 4;
  test("first move (Black)", () => {
    let Eval(move, _) = minimax(board, Black, depth, ());
    expect(move) |> toEqual({prev: Coord(0, 1), next: Coord(0, 3)});
  });
  test("first move (White)", () => {
    let Eval(move, _) = minimax(board, White, depth, ());
    expect(move) |> toEqual({prev: Coord(7, 6), next: Coord(7, 4)});
  });
});