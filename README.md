# Tic-Tac-Toe-Solver

The program implements a basic game engine, which is able to generate new game states and detect the end of the game by showing the winner or a tie. Moreover, the program contains a solver based on the implementation of the min-max algorithm.

## Min-max algorithm

The algorithm returns a proper value for the ended game, but if it did not end, it generates new game states, which are added to a list. Next, each game state in the list is checked again by this algorithm. The algorithm should choose the game state, which will cause the fastest win, the slowest tie, or the slowest loss.

## What could be done better?

- functions should be described in detail in the comments
- the evaluation for the ended game in the min-max algorithm should be specified by the const variable instead of the exact value written in the code
- saving game states in the list might be unnecessary, they could be just evaluated in a loop in the recursive function
