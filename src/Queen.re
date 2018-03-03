open Coord;

open Game;

let pieceWeight = 5.0;

let weight = (_coord: coord, _player: player) : float => pieceWeight;

let possibleMoves = (coord: coord, board: board, player: player) : list(coord) => {
  let allTheWay = Piece.allTheWay(board, player);
  let ne = coord |> allTheWay(NorthEast);
  let nw = coord |> allTheWay(NorthWest);
  let se = coord |> allTheWay(SouthEast);
  let sw = coord |> allTheWay(SouthWest);
  let north = coord |> allTheWay(North);
  let east = coord |> allTheWay(East);
  let south = coord |> allTheWay(South);
  let west = coord |> allTheWay(West);
  north @ ne @ east @ se @ south @ sw @ west @ nw;
};