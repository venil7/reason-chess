open ReasonChess.Game;

open ReasonChess.Board;

open ReasonChess.Minimax;

type state = {
  player,
  board,
};

type action =
  | Move(move)
  | Board(board);

let initialState = () : state => {player: White, board: empty() |> default};

let reducer = (action: action, state: state) =>
  switch (action) {
  | Move(move) =>
    let board' = makeMove(move, state.board);
    ReasonReact.UpdateWithSideEffects(
      {...state, board: board'},
      (
        self =>
          Js.Global.setTimeout(() => self.send(Board(board' |> cpu)), 1)
          |> ignore
      ),
    );
  | Board(board) => ReasonReact.Update({...state, board})
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self => {
    let {board, player} = self.state;
    <div className="App">
      <Board board onMove=(move => self.send(Move(move))) player1=player />
      <History moves=board.moves />
      <Captured captured=board.captured />
    </div>;
  },
};