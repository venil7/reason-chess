let opposite = (player: Game.player): Game.player => switch player {
| White => Black
| Black => White
};

let enemyOf = (player:Game.player, cell: Game.cell): bool => {
  switch cell {
  | Game.Occupied(p, _) => opposite(p) == player;
  | _ => false;
  };
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
    coords |> List.map(next => ({prev: coord, next}:Game.move));
  };
};