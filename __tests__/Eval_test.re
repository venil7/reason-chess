open Jest;

open Game;

open Eval;

open Expect;

describe("Eval", () => {
  describe("Pawn", () => {
    test("pawn default, black", () =>
      expect(weight(Black, Coord(0, 1), Pawn)) |> toBe(1.1)
    );
    test("pawn default, white", () =>
      expect(weight(White, Coord(0, 6), Pawn)) |> toBe(1.1)
    );
    test("pawn forward, black,", () =>
      expect(weight(Black, Coord(0, 3), Pawn)) |> toBe(1.3)
    );
    test("pawn forward, white,", () =>
      expect(weight(White, Coord(0, 4), Pawn)) |> toBe(1.3)
    );
    test("pawn turns queen, black,", () =>
      expect(weight(Black, Coord(0, 7), Pawn)) |> toBe(5.0)
    );
    test("pawn turns queen, white,", () =>
      expect(weight(White, Coord(0, 0), Pawn)) |> toBe(5.0)
    );
  });
  describe("Others", () => {
    let weight' = weight(Black, Coord(0, 0));
    test("rook", () =>
      expect(weight'(Rook)) |> toBe(2.0)
    );
    test("knight", () =>
      expect(weight'(Knight)) |> toBe(3.0)
    );
    test("bishop", () =>
      expect(weight'(Bishop)) |> toBe(2.0)
    );
    test("queen", () =>
      expect(weight'(Queen)) |> toBe(5.0)
    );
    test("king", () =>
      expect(weight'(King)) |> toBe(10.0)
    );
  });
  describe("Eval board", () => {
    open Board;
    let board = empty() |> default;
    test("default White", () =>
      expect(score(board, White, 0)) |> toBe(0.0)
    );
    test("default Black", () =>
      expect(score(board, Black, 0)) |> toBe(0.0)
    );
    test("White advantage", () => {
      let board' =
        board |> Board.makeMove({prev: Coord(1, 6), next: Coord(1, 4)});
      expect(score(board', White, 0)) |> toBeCloseTo(0.2);
    });
    test("Black advantage", () => {
      let board' =
        board
        |> Board.makeMove({prev: Coord(1, 6), next: Coord(1, 5)})
        |> Board.makeMove({prev: Coord(5, 1), next: Coord(5, 3)});
      expect(score(board', Black, 0)) |> toBeCloseTo(0.1);
    });
    test("depth disadvantage", () =>
      expect(score(board, White, 1)) |> toBeCloseTo(-1.0)
    );
  });
  describe("Eval sort", () => {
    let move = {prev: Coord(1, 2), next: Coord(3, 4)};
    let map = (Eval(_, score)) => score;
    let evals: list(eval) = [
      Eval(move, 1.2),
      Eval(move, 0.9),
      Eval(move, -3.4),
    ];
    test("sorting for minimizer", () =>
      expect(evals |> List.sort(minimize) |> List.map(map))
      |> toEqual([(-3.4), 0.9, 1.2])
    );
    test("sorting for maximizer", () =>
      expect(evals |> List.sort(maximize) |> List.map(map))
      |> toEqual([1.2, 0.9, (-3.4)])
    );
  });
});