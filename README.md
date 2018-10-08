By [scaussin](https://github.com/scaussin) and [aleung-c](https://github.com/aleung-c)
field: Algorithms & AI 
# Gomoku
[Gomoku](https://en.wikipedia.org/wiki/Gomoku) is a strategy board game similar to [Go](https://en.wikipedia.org/wiki/Go_(game)) game.
The winner is the first player to form an unbroken chain of five stones (horizontally, vertically, or diagonally) or the first to capture 10 enemy's stones.

## Introduction
Playable in 1vs1 or against an AI. This program provides a graphical interface in [SDL2](https://www.libsdl.org/). The challenge of this two-man project is to develop an optimized AI and heuristic in order to respect the computation time constraints.

## AI
Artificial Intelligence uses a Min-Max algorithm with Alpha-Beta pruning.

Our project recreate a fully functional gomoku game. We implemented the whole game with C++, with the SDL2 framework for
displaying the game, and with an intensive use of the min-max algorithm.

The core of this project is the IA. By using the min-max algorithm, the IA analyses the board, and "search" for the most interesting
move to make, thanks to our game heuristic. Then, the IA analyzes the move that the players might make at the next turn, and then
its own next-next move, and this as much as its "depth" of intelligence asks it.

You get it, the IA does not just analyse the most interesting move. It searches the best move for the next projected possibilities.
That is the core of min-max: searching for the move that give the maximum of point (best outcome), for the minimum of loss.

This makes a program that looks alive in its play-style, by trying to create forms on several turns.

Aside from its algorithm, the IA also have an advanced heuristic, that is a means of evaluating the board. For this, we used theories
about gomoku, especially the threat-space search devised by L. V. Allis and M. P. H. Huntjens. This theory defines forms as "threats"
that leads to victory and must be seeked or countered. Our program search for these forms on several turns,
which makes it very agile in its play style, as there are several threat forms, that can be combined.

For more on threat-space search, see [this documentation](http://www.renju.nu/wp-content/uploads/sites/46/2016/09/Go-Moku.pdf).

Video of the game:

[![Gomoku running video link](https://img.youtube.com/vi/A97sY5tTSNk/0.jpg)](https://www.youtube.com/watch?v=A97sY5tTSNk)

Screenshots:

![Alt text](./screens/gomoku_1.png "Gomoku screenshot 1")
![Alt text](./screens/gomoku_2.png "Gomoku screenshot 2")
![Alt text](./screens/gomoku_3.png "Gomoku screenshot 3")
