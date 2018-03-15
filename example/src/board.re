open ReasonChess.Game;

open ReasonChess.Board;

open ReasonChess.Coord;

type moveCallback = move => unit;

type state = {
  possibleMoves: list(move),
  selected: option(coord),
};

let initialState = () : state => {possibleMoves: [], selected: None};

let moveComplete = (onMove: moveCallback, move: move, _self) => onMove(move);

type action =
  | Select(coord);

let reducer' = (onMove: moveCallback, action: action, state: state) =>
  switch (action, state.selected) {
  | (Select(coord), None) =>
    ReasonReact.Update({...state, selected: Some(coord)})
  | (Select(prev), Some(next)) =>
    ReasonReact.UpdateWithSideEffects(
      initialState(),
      moveComplete(onMove, {prev, next}),
    )
  };

let component = ReasonReact.reducerComponent("Board");

let make = (~board: board, ~onMove: moveCallback, _children) => {
  ...component,
  initialState,
  reducer: reducer'(onMove),
  render: self =>
    <div className="board">
      (
        board
        |> iterate
        |> List.mapi((index, cell) =>
             <Cell
               cell
               highlight=None
               key=(string_of_int(index))
               coord=(coordOfIndex(index))
               onClick=(coord => self.send(Select(coord)))
             />
           )
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
    </div>,
};