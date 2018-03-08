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

let possibleSouthMoves =
    (coord: coord, board: board, player: player)
    : list(coord) => {
  let forward = coord |> next(South);
  let coords =
    switch (coord) {
    | Coord(_, 1) => [forward, forward |> next(South)]
    | _ => [forward]
    };
  let strikes =
    [forward, coord |> next(SouthEast), coord |> next(SouthWest)]
    |> List.filter(isStrikable(board, player));
  strikes @ coords;
};

let possibleNorthMoves =
    (coord: coord, board: board, player: player)
    : list(coord) => {
  let forward = coord |> next(North);
  let coords =
    switch (coord) {
    | Coord(_, 6) => [forward, forward |> next(North)]
    | _ => [forward]
    };
  let strikes =
    [forward, coord |> next(NorthEast), coord |> next(NorthWest)]
    |> List.filter(isStrikable(board, player));
  strikes @ coords;
};

let possibleMoves =
    (coord: coord, board: board, player: player)
    : list(coord) => {
  let moves =
    switch (player) {
    | Black => possibleSouthMoves(coord, board, Black)
    | White => possibleNorthMoves(coord, board, White)
    };
  moves |> List.filter(isValid);
};