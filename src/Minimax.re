open Game;

open Board;

open Player;

open Eval;

let defaultDepth = 4;

let maxScore = 100.0;

let cpuPlayer = Black;

let rec minimax =
        (board: board, player: player, depth: int, ~move: option(move)=?, ())
        : eval => {
  let depth' = float_of_int(depth);
  let winner = winner(board);
  switch (winner, move, depth) {
  | (Some(player), Some(move), _) when player != cpuPlayer =>
    Eval(move, maxScore -. depth')
  | (Some(player), Some(move), _) when player == cpuPlayer =>
    Eval(move, depth' -. maxScore)
  | (_, Some(move), depth) when depth <= 0 =>
    Eval(move, score(board, player, depth))
  | (_, _, depth) =>
    let sorting = player == cpuPlayer ? maximizer : minimizer;
    let opponent = player |> opposite;
    let makeMove' = makeMove(_, board);
    let nextDepth = depth - 1;
    board
    |> possibleMoves(player)
    |> List.map(move =>
         minimax(makeMove'(move), opponent, nextDepth, ~move, ())
       )
    |> List.sort(sorting)
    |> List.hd;
  };
};

let cpu =
    (board: board, ~player: player=Black, ~depth: int=defaultDepth, ())
    : board => {
  let Eval(move, _) = minimax(board, player, depth, ());
  board |> makeMove(move);
};