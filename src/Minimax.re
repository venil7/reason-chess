open Game;

open Board;

open Player;

open Eval;

let defaultDepth = 4;

let maxScore = 100.0;

let rec minimax =
        (
          board: board,
          player: player,
          depth: int,
          ~move: option(move)=?,
          ~maximizer=player,
          (),
        )
        : eval => {
  let depth' = float_of_int(depth);
  let winner = winner(board);
  switch (winner, move, depth) {
  /* when human player got to a winnig state   */
  | (Some(player), Some(move), _) when player != maximizer =>
    Eval(move, maxScore -. depth')
  /* when CPU player got to a winnig state */
  | (Some(player), Some(move), _) when player == maximizer =>
    Eval(move, depth' -. maxScore)
  /* when depth level has been reached */
  | (_, Some(move), depth) when depth <= 0 =>
    Eval(move, score(board, player, depth))
  /* when depth level hasn't been reached yet */
  | (_, _, depth) =>
    let sorting = player == maximizer ? maximize : minimize;
    let opponent = player |> opposite;
    let makeMove' = makeMove(_, board);
    let nextDepth = depth - 1;
    board
    |> possibleMoves(player)
    |> List.map(move' => {
         let Eval(_, score) =
           minimax(
             makeMove'(move'),
             opponent,
             nextDepth,
             ~move=move',
             ~maximizer,
             (),
           );
         Eval(move', score);
       })
    |> List.sort(sorting)
    |> List.hd;
  };
};

let cpu = (board: board, ~player=Black, ~depth: int=defaultDepth, ()) : board => {
  let Eval(move, _) = minimax(board, player, depth, ());
  board |> makeMove(move);
};