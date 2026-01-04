Chess programming.
---
Build using:
``` bash
cmake -S . -B build
cmake --build build
```

# Development log
## Data

Every piece type will have their own 64 bit number. Since the board is 8x8, we can put the position data of every piece into one 64 bit number. For example, the black pawns will have an initial value of:
``` bash
00000000
11111111
00000000
00000000
00000000
00000000
00000000
00000000
```
, which is, of course, equal to:
``` bash
00000000 11111111 00000000 00000000 00000000 00000000 00000000 00000000 = 71776119061217280
```
The "empty" tiles will have a 64 bit number aswell with an initial value of:
``` bash
00000000 00000000 11111111 11111111 11111111 11111111 00000000 00000000
```

## Input
### Basic Idea

The first problem I need to tackle is figuring out how I want the program to handle input. I will try to implement a system that takes in 4 characters as input, and it will be converted to a move. After that, the program will decide if that move is legal or not, and the move will be done.

### Implementation

The user will input four characters, for example: "e2e4", meaning the piece on e2 will move to e4; "f7g8", the piece on f7 will move to g8, etc.


