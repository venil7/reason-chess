open Coord;

open Game;

let pieceWeight = 2.0;

let weight = (_coord: coord, _player: player) : float => pieceWeight;

let possibleMoves = (coord: coord, board: board, player: player) : list(coord) => {
  let allTheWay = Piece.allTheWay(board, player);
  let ne = coord |> allTheWay(NorthEast);
  let nw = coord |> allTheWay(NorthWest);
  let se = coord |> allTheWay(SouthEast);
  let sw = coord |> allTheWay(SouthWest);
  ne @ nw @ se @ sw;
};