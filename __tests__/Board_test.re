open Jest;

open Game;

open Board;

open Expect;

describe("Board", () => {
  test("length", () =>
    expect(List.length(empty())) |> toEqual(64)
  );
  test("empty", () =>
    expect(List.for_all(c => c == Empty, empty())) |> toBe(true)
  );
  test("default", () => {
    let board = empty() |> default;
    expect(board |> List.filter(cell => cell != Empty) |> List.length)
    |> toBe(32);
  });
  test("at", () => {
    let board = empty() |> default;
    let cell = board |> at(Coord(0, 0));
    expect(cell) |> toEqual(Occupied(Black, Rook));
  });
  test("makeMove", () => {
    let board = empty() |> default;
    let board' = board |> makeMove({prev: Coord(0, 1), next: Coord(0, 2)});
    let prev = board' |> at(Coord(0, 1));
    let next = board' |> at(Coord(0, 2));
    expect((prev, next)) |> toEqual((Empty, Occupied(Black, Pawn)));
  });
});