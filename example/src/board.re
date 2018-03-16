open ReasonChess.Game;

open ReasonChess.Board;

open ReasonChess.Coord;

type moveCallback = move => unit;

type state = {
  possibleCoords: list(coord),
  selected: option(coord),
};

let moveToCoord = ({next, _}: move) : coord => next;

let initialState = () : state => {possibleCoords: [], selected: None};

let moveComplete = (onMove: moveCallback, move: move, _self) => onMove(move);

let highlight = (state: state, index: int) : Cell.highlight => {
  let coord = coordOfIndex(index);
  switch (state.selected) {
  | Some(coord') when coord' == coord => Selected
  | _ when List.mem(coord, state.possibleCoords) => Path
  | _ => None
  };
};

type action =
  | Select(coord, cell);

let reducer' =
    (
      board: board,
      onMove: moveCallback,
      player1: player,
      action: action,
      state: state,
    ) =>
  /* making a move requires two click - from and to */
  switch (action, state.selected) {
  /* click 1 */
  | (Select(coord, cell), None) =>
    let possibleCoords =
      switch (cell) {
      | Occupied(player, piece) when player == player1 =>
        possiblePieceMoves(coord, piece, player, board)
        |> List.map(moveToCoord)
      | _ => []
      };
    ReasonReact.Update({possibleCoords, selected: Some(coord)});
  /* click 2 */
  | (Select(next, _), Some(prev)) =>
    ReasonReact.UpdateWithSideEffects(
      initialState(),
      moveComplete(onMove, {prev, next}),
    )
  };

let component = ReasonReact.reducerComponent("Board");

let make = (~board: board, ~player1: player, ~onMove: moveCallback, _children) => {
  ...component,
  initialState,
  reducer: reducer'(board, onMove, player1),
  render: self =>
    <div className="board">
      (
        board
        |> iterate
        |> List.mapi((index, cell) =>
             <Cell
               cell
               highlight=(index |> highlight(self.state))
               key=(string_of_int(index))
               coord=(coordOfIndex(index))
               onClick=(coord => self.send(Select(coord, cell)))
             />
           )
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
    </div>,
};