open Game;

let opposite = (player: Game.player) : Game.player =>
  switch (player) {
  | White => Black
  | Black => White
  };