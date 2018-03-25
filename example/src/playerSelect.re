open ReasonChess.Game;

let component = ReasonReact.statelessComponent("PlayerSelect");

let playerToString = Captured.playerToString;

let className = (player, selected) => player == selected ? "selected" : "";

let make = (~turn: player, ~cpu: player, ~onSelect: player => unit, _children) => {
  ...component,
  render: _self =>
    <div className="player-select">
      ("Turn: " ++ playerToString(turn) |> ReasonReact.stringToElement)
      <p> ("CPU plays:" |> ReasonReact.stringToElement) </p>
      <button
        className=(className(Black, cpu)) onClick=(_evt => onSelect(Black))>
        (playerToString(Black) |> ReasonReact.stringToElement)
      </button>
      <button
        className=(className(White, cpu)) onClick=(_evt => onSelect(White))>
        (playerToString(White) |> ReasonReact.stringToElement)
      </button>
    </div>,
};