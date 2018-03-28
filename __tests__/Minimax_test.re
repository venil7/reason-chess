open Jest;

open Game;

open Board;

open Minimax;

open Expect;

describe("Eval", () => {
  let board = empty() |> default;
  let depth = 4;
  test("first move (Black)", () => {
    let Eval(move, _) = minimax(Black, depth, board);
    expect(move) |> toEqual({prev: Coord(0, 1), next: Coord(0, 3)});
  });
  test("first move (White)", () => {
    let Eval(move, _) = minimax(White, depth, board);
    expect(move) |> toEqual({prev: Coord(7, 6), next: Coord(7, 4)});
  });
  describe("Game over", () =>
    test("black wins", () => {
      let board' =
        board
        |> makeMove({prev: Coord(4, 6), next: Coord(7, 5)})
        |> setAt(Occupied(Black, Queen), Coord(4, 4))
        |> cpu(~depth=2);
      expect(board'.winner) |> toEqual(Some(Black));
    })
  );
});