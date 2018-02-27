open Jest;

open Game;

open Board;

open Coord;

open Expect;

describe("Index", () => {
  test("under index", () =>
    expect(validIndex(-1)) |> toBe(false)
  );
  test("over index", () =>
    expect(validIndex(64)) |> toBe(false)
  );
  test("valid", () =>
    expect(validIndex(2)) |> toBe(true)
  );
  test("convert to coord", () =>
    expect(coordOfIndex(36)) |> toEqual(Coord(4, 4))
  );
});

describe("Coord", () => {
  test("under index", () =>
    expect(validCoord(Coord(-5, -7))) |> toBe(false)
  );
  test("over index", () =>
    expect(validCoord(Coord(8, 8))) |> toBe(false)
  );
  test("valid", () =>
    expect(validCoord(Coord(4, 4))) |> toBe(true)
  );
  test("convert to index", () =>
    expect(indexOfCoord(Coord(4, 4))) |> toEqual(36)
  );
  test("at", () => {
    let board = empty() |> default;
    let cell = board |> at(Coord(0, 0));
    expect(cell) |> toEqual(Occupied(Black, Rook));
  });
});