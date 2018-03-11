open Jest;

open Board;

open Minimax;

open Expect;

describe("Eval", () => {
  let board = empty() |> default;
  test("first move", () => {
    let board' = cpu(board, ());
    expect(board') |> toEqual(board');
  });
});