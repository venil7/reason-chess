open Jest;

open Game;

open Board;

open Coord;

open Expect;

describe("Pawn", () => {
  describe("Black", () => {
    test("possible moves (no attack), frontline", () => {
      let coord = Coord(4, 1);
      let board = empty() |> setAt(Pawn, Black, coord); /*piece under test*/
      let coords = Pawn.possibleMoves(coord, board, Black) |> Array.of_list;
      expect(coords)
      |> toEqual([|coord |> next(South), coord |> next(South) |> next(South)|]);
    });
    test("possible moves (2 attack), frontline", () => {
      let coord = Coord(4, 1);
      let board =
        empty()
        |> setAt(Pawn, Black, coord) /*piece under test*/
        |> setAt(Pawn, White, Coord(3, 2))
        |> setAt(Pawn, White, Coord(5, 2));
      let coords = Pawn.possibleMoves(coord, board, Black) |> Array.of_list;
      expect(coords)
      |> toBeSupersetOf([|Coord(4, 2), Coord(4, 3), Coord(3, 2), Coord(5, 2)|]);
    });
    test("possible moves (1 attack), frontline", () => {
      let coord = Coord(4, 1);
      let board =
        empty()
        |> setAt(Pawn, Black, coord) /*piece under test*/
        |> setAt(Pawn, White, Coord(5, 2));
      let coords = Pawn.possibleMoves(coord, board, Black) |> Array.of_list;
      expect(coords)
      |> toBeSupersetOf([|Coord(4, 2), Coord(4, 3), Coord(5, 2)|]);
    });
    test("possible moves (1 attack, no friendly attack), frontline", () => {
      let coord = Coord(4, 1);
      let board =
        empty()
        |> setAt(Pawn, Black, coord) /*piece under test*/
        |> setAt(Pawn, Black, Coord(3, 2))
        |> setAt(Pawn, White, Coord(5, 2));
      let coords = Pawn.possibleMoves(coord, board, Black) |> Array.of_list;
      expect(coords)
      |> toBeSupersetOf([|Coord(4, 2), Coord(4, 3), Coord(5, 2)|]);
    });
    test("possible moves (2 attacks), not a frontline", () => {
      let coord = Coord(4, 2);
      let board =
        empty()
        |> setAt(Pawn, Black, coord) /*piece under test*/
        |> setAt(Pawn, White, Coord(3, 3))
        |> setAt(Pawn, White, Coord(5, 3));
      let coords = Pawn.possibleMoves(coord, board, Black) |> Array.of_list;
      expect(coords)
      |> toBeSupersetOf([|Coord(3, 3), Coord(4, 3), Coord(5, 3)|]);
    });
    test("possible moves (0), corner case", () => {
      let coord = Coord(7, 7);
      let board = empty() |> setAt(Pawn, Black, coord) /*piece under test*/;
      let coords = Pawn.possibleMoves(coord, board, Black) |> Array.of_list;
      expect(coords) |> toBeSupersetOf([||]);
    });
  });
  describe("White", () => {
    test("possible moves (no attack), frontline", () => {
      let coord = Coord(3, 6);
      let board = empty() |> setAt(Pawn, White, coord); /*piece under test*/
      let coords = Pawn.possibleMoves(coord, board, White) |> Array.of_list;
      expect(coords) |> toEqual([|Coord(3, 5), Coord(3, 4)|]);
    });
    test("possible moves (2 attack), frontline", () => {
      let coord = Coord(3, 6);
      let board =
        empty()
        |> setAt(Pawn, White, coord) /*piece under test*/
        |> setAt(Pawn, Black, Coord(2, 5))
        |> setAt(Pawn, Black, Coord(4, 5));
      let coords = Pawn.possibleMoves(coord, board, White) |> Array.of_list;
      expect(coords)
      |> toBeSupersetOf([|Coord(2, 5), Coord(3, 5), Coord(4, 5), Coord(3, 4)|]);
    });
    test("possible moves (1 attack), frontline", () => {
      let coord = Coord(4, 6);
      let board =
        empty()
        |> setAt(Pawn, White, coord) /*piece under test*/
        |> setAt(Pawn, Black, Coord(5, 5));
      let coords = Pawn.possibleMoves(coord, board, White) |> Array.of_list;
      expect(coords)
      |> toBeSupersetOf([|Coord(4, 4), Coord(4, 5), Coord(5, 5)|]);
    });
    test("possible moves (1 attack, no friendly attack), frontline", () => {
      let coord = Coord(4, 6);
      let board =
        empty()
        |> setAt(Pawn, White, coord) /*piece under test*/
        |> setAt(Pawn, Black, Coord(3, 5))
        |> setAt(Pawn, White, Coord(5, 5));
      let coords = Pawn.possibleMoves(coord, board, White) |> Array.of_list;
      expect(coords)
      |> toBeSupersetOf([|Coord(3, 5), Coord(4, 5), Coord(4, 4)|]);
    });
    test("possible moves (2 attacks), not a frontline", () => {
      let coord = Coord(4, 5);
      let board =
        empty()
        |> setAt(Pawn, White, coord) /*piece under test*/
        |> setAt(Pawn, Black, Coord(3, 4))
        |> setAt(Pawn, Black, Coord(5, 4));
      let coords = Pawn.possibleMoves(coord, board, White) |> Array.of_list;
      expect(coords)
      |> toBeSupersetOf([|Coord(3, 4), Coord(4, 4), Coord(5, 4)|]);
    });
    test("possible moves (0), corner case", () => {
      let coord = Coord(7, 0);
      let board = empty() |> setAt(Pawn, White, coord) /*piece under test*/;
      let coords = Pawn.possibleMoves(coord, board, White) |> Array.of_list;
      expect(coords) |> toBeSupersetOf([||]);
    });
  });
});