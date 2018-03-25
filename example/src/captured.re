open ReasonChess.Game;

let playerToString = player =>
  switch (player) {
  | White => "white"
  | Black => "black"
  };

let pieceToString = piece =>
  switch (piece) {
  | Pawn => "pawn"
  | Rook => "rook"
  | Knight => "knight"
  | Bishop => "bishop"
  | Queen => "queen"
  | King => "king"
  };

let capToStr = ((player, piece)) =>
  playerToString(player) ++ " " ++ pieceToString(piece);

let component = ReasonReact.statelessComponent("Captured");

let make = (~captured: list((player, piece)), _children) => {
  ...component,
  render: _self =>
    <ul className="captures">
      (
        captured
        |> List.mapi((idx, cap) =>
             <li key=(string_of_int(idx))>
               (cap |> capToStr |> ReasonReact.stringToElement)
             </li>
           )
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
    </ul>,
};