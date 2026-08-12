Chess Project written in C. Can be played in the terminal.

# Installing
---
Build using:

```bash
cmake -S . -B build
cmake --build build
```

Run using:

```bash
./build/program
```

# How to play
---
The game will ask you to make a move, for example: move the e2 pawn to e4.
You can make a move by typing the tile you want to pick up the piece, and typing the tile you want to put it down.
For example:
``` bash
e2e4, a1a7, etc...
```
You can exit the program by inputting 'q' as your move.

# What's next?
---
- implement the movement rules correctly for every piece
- think about castling move input
- make_move() function!!!
- do the legality masking stuff (inside the switch statement)
- make more abstractions!
- one BIG loop, two smaller loops (whites move, blacks move)

Do these!
Do these!
- finish the legal move generating function
- abstract the main function down, several more functions
- correct the while loop (one big while loop, two smaller ones inside (white move --> black move --> beginning))
