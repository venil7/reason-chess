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
  describe("All the way", () => {
    test("North", () => {
      let path = Coord(0, 6) |> Piece.allTheWay(board, White, North);
      expect(path)
      |> toEqual([
           Coord(0, 5),
           Coord(0, 4),
           Coord(0, 3),
           Coord(0, 2),
           Coord(0, 1)
         ]);
    });
    test("NorthWest", () => {
      let path = Coord(6, 2) |> Piece.allTheWay(board, Black, SouthWest);
      expect(path)
      |> toEqual([Coord(5, 3), Coord(4, 4), Coord(3, 5), Coord(2, 6)]);
    });
    test("cornercase", () => {
      let path = Coord(0, 0) |> Piece.allTheWay(board, Black, NorthWest);
      expect(path) |> toEqual([]);
    });
    test("friendly fire", () => {
      let path = Coord(7, 2) |> Piece.allTheWay(board, White, South);
      expect(path) |> toEqual([Coord(7, 3), Coord(7, 4), Coord(7, 5)]);
    });
  });
});