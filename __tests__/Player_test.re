open Jest;

open Game;

open Player;

open Expect;

describe("Player", () => {
  test("opposite White -> Black", () =>
    expect(opposite(White)) |> toBe(Black)
  );
  test("opposite Black -> White", () =>
    expect(opposite(Black)) |> toBe(White)
  );
});