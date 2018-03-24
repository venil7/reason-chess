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

let oppositePlayers = (coord1: coord, coord2: coord, board: board) : bool =>
  switch (board |> at(coord1), board |> at(coord2)) {
  | (Occupied(p1, _), Occupied(p2, _)) when p1 != p2 => true
  | _ => false
  };

let highlight = (state: state, board: board, index: int) : Cell.highlight => {
  let coord = coordOfIndex(index);
  switch (state.selected) {
  | Some(coord') when coord' == coord => Selected
  | Some(coord')
      when
        oppositePlayers(coord', coord, board)
        && List.mem(coord, state.possibleCoords) =>
    Attack
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
  /* making a move requires two clicks - from and to */
  switch (action, state.selected) {
  /* click 1 from*/
  | (Select(coord, cell), None) =>
    let state' =
      switch (cell) {
      | Occupied(player, piece) when player == player1 =>
        let possibleCoords =
          possiblePieceMoves(coord, piece, player, board)
          |> List.map(moveToCoord);
        {possibleCoords, selected: Some(coord)};
      | _ => initialState()
      };
    ReasonReact.Update(state');
  /* click 2 to*/
  | (Select(next, _), Some(prev)) =>
    let validMove = List.mem(next, state.possibleCoords);
    if (validMove) {
      ReasonReact.UpdateWithSideEffects(
        initialState(),
        moveComplete(onMove, {prev, next}),
      );
    } else {
      ReasonReact.UpdateWithSideEffects(
        initialState(),
        (self => self.send(action)),
      );
    };
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
               highlight=(index |> highlight(self.state, board))
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