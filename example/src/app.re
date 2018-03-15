open ReasonChess.Game;

open ReasonChess.Board;

let component = ReasonReact.statelessComponent("App");

let board = empty() |> default;

let onMove = (move: move) => Js.log(move);

let make = _children => {
  ...component,
  render: _self => <div className="App"> <Board board onMove /> </div>,
};