open Jest;

open Game;

open Board;

open Piece;

open Expect;

describe("Piece", () => {
  let board = empty() |> default;
  describe("All the way", () => {
    test("North", () => {
      let path =
        Coord(0, 6) |> allTheWay(board, White, North) |> Array.of_list;
      expect(path)
      |> toBeSupersetOf([|
           Coord(0, 1),
           Coord(0, 2),
           Coord(0, 3),
           Coord(0, 4),
           Coord(0, 5),
         |]);
    });
    test("NorthWest", () => {
      let path =
        Coord(6, 2) |> allTheWay(board, Black, SouthWest) |> Array.of_list;
      expect(path)
      |> toBeSupersetOf([|
           Coord(2, 6),
           Coord(3, 5),
           Coord(4, 4),
           Coord(5, 3),
         |]);
    });
    test("cornercase", () => {
      let path = Coord(0, 0) |> allTheWay(board, Black, NorthWest);
      expect(path) |> toEqual([]);
    });
    test("friendly fire", () => {
      let path =
        Coord(7, 2) |> allTheWay(board, White, South) |> Array.of_list;
      expect(path)
      |> toBeSupersetOf([|Coord(7, 5), Coord(7, 4), Coord(7, 3)|]);
    });
  });
});