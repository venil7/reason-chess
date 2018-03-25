open ReasonChess.Game;

let coordToStr = (Coord(x, y)) =>
  string_of_int(x) ++ "," ++ string_of_int(y);

let moveToStr = ({prev, next}: move) =>
  coordToStr(prev) ++ "-->" ++ coordToStr(next);

let component = ReasonReact.statelessComponent("History");

let make = (~moves: list(move), _children) => {
  ...component,
  render: _self =>
    <div className="history">
      <strong> ("Move history:" |> ReasonReact.stringToElement) </strong>
      <ul>
        (
          moves
          |> List.mapi((idx, move) =>
               <li key=(string_of_int(idx))>
                 (move |> moveToStr |> ReasonReact.stringToElement)
               </li>
             )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
      </ul>
    </div>,
};