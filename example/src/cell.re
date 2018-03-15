open ReasonChess.Game;

type highlight =
  | Selected
  | Attack
  | Path
  | None;

let toClassName = (lst: list(string)) : string =>
  lst |> List.fold_left((acc, c) => acc ++ " " ++ c, "") |> String.trim;

let playerToClass = (player: player) =>
  switch (player) {
  | Black => "black"
  | White => "white"
  };

let hlToClass = (highlight: highlight) : string =>
  switch (highlight) {
  | Selected => "selected"
  | Attack => "attack"
  | Path => "path"
  | _ => ""
  };

let pieceToClass = (piece: piece) =>
  switch (piece) {
  | Pawn => "pawn"
  | Rook => "rook"
  | Knight => "knight"
  | Bishop => "bishop"
  | Queen => "queen"
  | King => "king"
  };

let rec toClassNames = (highlight: highlight, cell: cell) : list(string) =>
  switch (cell) {
  | Occupied(player, piece) =>
    toClassNames(highlight, Empty)
    @ [pieceToClass(piece), playerToClass(player)]
  | Empty => ["cell", hlToClass(highlight)]
  };

let component = ReasonReact.statelessComponent("Cell");

let make =
    (
      ~cell: cell,
      ~coord: coord,
      ~highlight: highlight,
      ~onClick: coord => unit,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div
      onClick=(_evt => onClick(coord))
      className=(cell |> toClassNames(highlight) |> toClassName)
    />,
};