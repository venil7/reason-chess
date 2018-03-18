open Game;

open Board;

open Player;

open Eval;

let defaultDepth = 4;

let maxScore = 100.0;

let minScore = 0.0 -. maxScore;

type abPair = {
  alpha: float,
  beta: float,
};

type abAcc = {
  v: float,
  ab: abPair,
  evals: list(eval),
  cutOff: bool,
};

let defaultAlphaBeta: abPair = {alpha: minScore, beta: maxScore};

let extract = ({evals, _}: abAcc) => evals;

let defaultAcc = (isMaximizer: bool, alphaBeta: abPair) : abAcc => {
  v: isMaximizer ? minScore : maxScore,
  ab: alphaBeta,
  evals: [],
  cutOff: false,
};

let nextDepth = (depth: int) => depth - 1;

let rec minimax =
        (
          board: board,
          player: player,
          depth: int,
          ~alphaBeta=defaultAlphaBeta,
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
    let {alpha, beta} = alphaBeta;
    let isMaximizer = player == maximizer;
    let sorting = isMaximizer ? maximize : minimize;
    let compare = isMaximizer ? max : min;
    let opponent = player |> opposite;
    let makeMove' = makeMove(_, board);
    board
    |> possibleMoves(player)
    |> List.fold_left(
         (acc: abAcc, move': move) =>
           if (acc.cutOff) {
             acc;
           } else {
             let Eval(_, score) =
               minimax(
                 makeMove'(move'),
                 opponent,
                 nextDepth(depth),
                 ~alphaBeta=acc.ab,
                 ~move=move',
                 ~maximizer,
                 (),
               );
             let v' = compare(acc.v, score);
             let alpha' = compare(alpha, v');
             let beta' = compare(v', beta);
             let ab =
               isMaximizer ?
                 {...acc.ab, alpha: alpha'} : {...acc.ab, beta: beta'};
             beta <= alpha' ?
               /* cut off */
               {ab, v: v', evals: [Eval(move', v')], cutOff: true} :
               /* carry on */
               {
                 ab,
                 v: v',
                 evals: [Eval(move', score), ...acc.evals],
                 cutOff: false,
               };
           },
         defaultAcc(isMaximizer, alphaBeta),
       )
    |> extract
    |> List.sort(sorting)
    |> List.hd;
  };
};

let cpu = (board: board, ~player=Black, ~depth: int=defaultDepth, ()) : board => {
  let Eval(move, _) = minimax(board, player, depth, ());
  board |> makeMove(move);
};