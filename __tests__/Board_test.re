open Jest;

open Game;

open Board;

open Coord;

open Expect;

describe("Board", () => {
  test("length", () =>
    expect(List.length(empty().cells)) |> toEqual(64)
  );
  test("empty", () =>
    expect(List.for_all(c => c == Empty, empty().cells)) |> toBe(true)
  );
  test("default", () => {
    let board = empty() |> default;
    expect(board.cells |> List.filter(cell => cell != Empty) |> List.length)
    |> toBe(32);
  });
  test("makeMove", () => {
    let board = empty() |> default;
    let board' = board |> makeMove({prev: Coord(0, 1), next: Coord(0, 2)});
    let prev = board' |> at(Coord(0, 1));
    let next = board' |> at(Coord(0, 2));
    expect((prev, next)) |> toEqual((Empty, Occupied(Black, Pawn)));
  });
  test("makeMove - winner", () => {
    let board = empty() |> default;
    let board' = board |> makeMove({prev: Coord(3, 7), next: Coord(4, 0)});
    expect(board'.winner) |> toEqual(Some(White));
  });
  test("makeMove - captured", () => {
    let board = empty() |> default;
    let board' = board |> makeMove({prev: Coord(3, 7), next: Coord(4, 0)});
    expect(board'.captured) |> toEqual([(Black, King)]);
  });
  describe("Possible moves", () =>
    test("White", () => {
      let moves = () |> empty |> default |> possibleMoves(White);
      expect(moves |> Array.of_list)
      |> toBeSupersetOf([|
           {prev: Coord(0, 6), next: Coord(0, 4)},
           {prev: Coord(0, 6), next: Coord(0, 5)},
           {prev: Coord(1, 6), next: Coord(1, 4)},
           {prev: Coord(1, 6), next: Coord(1, 5)},
           {prev: Coord(2, 6), next: Coord(2, 4)},
           {prev: Coord(2, 6), next: Coord(2, 5)},
           {prev: Coord(3, 6), next: Coord(3, 4)},
           {prev: Coord(3, 6), next: Coord(3, 5)},
           {prev: Coord(4, 6), next: Coord(4, 4)},
           {prev: Coord(4, 6), next: Coord(4, 5)},
           {prev: Coord(5, 6), next: Coord(5, 4)},
           {prev: Coord(5, 6), next: Coord(5, 5)},
           {prev: Coord(6, 6), next: Coord(6, 4)},
           {prev: Coord(6, 6), next: Coord(6, 5)},
           {prev: Coord(7, 6), next: Coord(7, 4)},
           {prev: Coord(7, 6), next: Coord(7, 5)},
           {prev: Coord(1, 7), next: Coord(0, 5)},
           {prev: Coord(1, 7), next: Coord(2, 5)},
           {prev: Coord(6, 7), next: Coord(5, 5)},
           {prev: Coord(6, 7), next: Coord(7, 5)},
         |]);
    })
  );
});