open Coord;

let opposite = (player: Game.player) : Game.player =>
  switch player {
  | White => Black
  | Black => White
  };

let enemyOf = (player: Game.player, cell: Game.cell) : bool =>
  switch cell {
  | Game.Occupied(p, _) => opposite(p) == player
  | _ => false
  };

let isStrikable =
    (board: Game.board, player: Game.player, coord: Game.coord)
    : bool =>
  isValid(coord) && enemyOf(player, board |> at(coord));

let allTheWay =
    (
      board: Game.board,
      player: Game.player,
      direction: Game.direction,
      coord: Game.coord
    )
    : list(Game.coord) => {
  let rec allTheWay' =
          (
            board: Game.board,
            player: Game.player,
            direction: Game.direction,
            coord: Game.coord,
            steps: list(Game.coord)
          )
          : list(Game.coord) => {
    let step = coord |> next(direction);
    if (isValid(step)) {
      switch (board |> at(step)) {
      | Game.Occupied(plyr, _) when plyr == player => steps
      | Game.Occupied(_, _) => [step, ...steps]
      | Game.Empty =>
        allTheWay'(board, player, direction, step, [step, ...steps])
      };
    } else {
      steps;
    };
  };
  allTheWay'(board, player, direction, coord, []);
};

let allTheWays =
    (
      board: Game.board,
      player: Game.player,
      directions: list(Game.direction),
      coord: Game.coord
    )
    : list(Game.coord) => {
  let atw = allTheWay(board, player);
  directions |> List.fold_left((acc, dir) => acc @ atw(dir, coord), []);
};

module type PieceParam = {
  let weight: (Game.coord, Game.player) => float;
  let possibleMoves: (Game.coord, Game.board, Game.player) => list(Game.coord);
};

module type PieceImpl = {
  let weight: (Game.coord, Game.player) => float;
  let possibleMoves: (Game.coord, Game.board, Game.player) => list(Game.move);
};

module Make = (PP: PieceParam) : PieceImpl => {
  let weight = PP.weight;
  let possibleMoves =
      (coord: Game.coord, board: Game.board, player: Game.player)
      : list(Game.move) => {
    let coords = PP.possibleMoves(coord, board, player);
    coords |> List.map(next => ({prev: coord, next}: Game.move));
  };
};