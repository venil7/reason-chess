open ReasonChess.Game;

open ReasonChess.Board;

let player1 = White;

let component = ReasonReact.statelessComponent("App");

let board = empty() |> default;

let onMove = (move: move) => Js.log(move);

let make = _children => {
  ...component,
  render: _self => <div className="App"> <Board board onMove player1 /> </div>,
};