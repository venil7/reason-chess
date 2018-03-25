open Coord;

open Game;

let isStrikable =
    (board: Game.board, player: Game.player, coord: Game.coord)
    : bool =>
  isValid(coord)
  && (
    switch (board |> at(coord)) {
    | Occupied(p, _) => p != player
    | _ => false
    }
  );

let sideAttacks = (player: player) : (direction, direction) =>
  switch (player) {
  | White => (NorthEast, NorthWest)
  | Black => (SouthEast, SouthWest)
  };

let possibleMoves' =
    (coord: coord, board: board, player: player, direction: direction)
    : list(coord) => {
  let coords =
    (
      switch (coord) {
      | Coord(_, 1 | 6) =>
        Piece.allTheWay(
          ~count=2,
          ~attack=false,
          board,
          player,
          direction,
          coord,
        )
      | _ =>
        Piece.allTheWay(
          ~count=1,
          ~attack=false,
          board,
          player,
          direction,
          coord,
        )
      }
    )
    |> List.filter(isValid);
  let (dir1, dir2) = sideAttacks(player);
  let strikes =
    [coord |> next(dir1), coord |> next(dir2)]
    |> List.filter(isStrikable(board, player));
  strikes @ coords;
};

let possibleMoves =
    (coord: coord, board: board, player: player)
    : list(coord) => {
  let moves =
    switch (player) {
    | Black => possibleMoves'(coord, board, Black, South)
    | White => possibleMoves'(coord, board, White, North)
    };
  moves |> List.filter(isValid);
};