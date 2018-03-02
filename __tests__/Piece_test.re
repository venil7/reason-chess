open Jest;

open Game;

open Board;

open Piece;

open Coord;

open Expect;

describe("Piece", () => {
  let board = empty() |> default;
  test("enemy of white -> black", () => {
    let cell = board |> at(Coord(0, 0));
    expect(cell |> enemyOf(White)) |> toBe(true);
  });
  test("enemy of black -> white", () => {
    let cell = board |> at(Coord(0, 7));
    expect(cell |> enemyOf(Black)) |> toBe(true);
  });
  test("enemy of empty -> none", () => {
    let cell = board |> at(Coord(0, 4));
    expect(cell |> enemyOf(Black)) |> toBe(false);
  });
  test("enemy of empty -> none 2", () => {
    let cell = board |> at(Coord(0, 4));
    expect(cell |> enemyOf(White)) |> toBe(false);
  });
  test("opposite White -> Black", () =>
    expect(opposite(White)) |> toBe(Black)
  );
  test("opposite Black -> White", () =>
    expect(opposite(Black)) |> toBe(White)
  );
});