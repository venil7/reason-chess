open ReasonChess.Game;

open ReasonChess.Board;

open ReasonChess.Minimax;

open ReasonChess.Player;

type state = {
  turn: player,
  cpu: player,
  board,
};

type action =
  | SetCpuPlayer(player) /*set CPU player */
  | HumanMove(move) /*Human player makes move */
  | CpuMove; /*CPU replaces the board */

let initialState = () : state => {
  cpu: Black,
  turn: White,
  board: empty() |> default,
};

let reducer = (action: action, state: state) =>
  switch (action) {
  | HumanMove(move) =>
    let board' = makeMove(move, state.board);
    ReasonReact.UpdateWithSideEffects(
      {...state, board: board', turn: opposite(state.turn)},
      (self => Js.Global.setTimeout(() => self.send(CpuMove), 1) |> ignore),
    );
  | CpuMove =>
    let board = state.board |> cpu(~player=state.cpu);
    ReasonReact.Update({...state, board, turn: opposite(state.turn)});
  | SetCpuPlayer(player) =>
    ReasonReact.UpdateWithSideEffects(
      {...state, cpu: player},
      (self => player == state.turn ? self.send(CpuMove) : ()),
    )
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self => {
    let {board, cpu, turn} = self.state;
    <div className="App">
      <Board
        board
        onMove=(move => self.send(HumanMove(move)))
        player1=(opposite(cpu))
      />
      <PlayerSelect
        turn
        cpu
        onSelect=(player => self.send(SetCpuPlayer(player)))
      />
      <History moves=board.moves />
      <Captured captured=board.captured />
    </div>;
  },
};