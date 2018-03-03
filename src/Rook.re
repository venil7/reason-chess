open Coord;

open Game;

let pieceWeight = 2.0;

let weight = (_coord: coord, _player: player) : float => pieceWeight;

let possibleMoves = (coord: coord, board: board, player: player) : list(coord) => {
  let allTheWay = Piece.allTheWay(board, player);
  let north = coord |> allTheWay(North);
  let east = coord |> allTheWay(East);
  let south = coord |> allTheWay(South);
  let west = coord |> allTheWay(West);
  north @ east @ south @ west;
};