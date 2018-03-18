open ReasonChess.Game;

open ReasonChess.Board;

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
      (self => self.send(Board(ReasonChess.Minimax.cpu(board', ())))),
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
    </div>;
  },
};