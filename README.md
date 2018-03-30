# reason-chess

## Build
[![Build Status](https://travis-ci.org/venil7/reason-chess.svg?branch=master)](https://travis-ci.org/venil7/reason-chess)

`reason-chess` is a chess engine for `ReasonML`. Use it for game development, chess analysis tools, etc in the browser, nodejs, native or in the mobile application. Engine features include:
 - minimax algorithm with variable depth tree evaluation
 - alphabeta pruning for faster evaluation
 - hints for possible moves
 - switching sides
 - full move history
 - full capture history
 - time travel and undo
 - almost 100% unit test converage

Browse [Example source](./example/) or try it in the [browser](http://darkruby.co.uk/reason-chess/)

*example gameplay*

![chess-gameplay](https://user-images.githubusercontent.com/508022/38139938-8d1b91ec-3429-11e8-8959-f3159714ea11.gif)


## build locally
```
npm run build
```

## Install
```
npm install reason-chess --save
```
### Update `bsconfig.json`
```
...
"bs-dependencies": [
    "reason-chess"
]
...
```

## Run [Example](./example/)
```
cd example
npm install
npm start
```


## Run Tests

```
npm run test
```