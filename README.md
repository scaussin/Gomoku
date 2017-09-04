# Gomoku
By [aleung-c](https://github.com/aleung-c) and [scaussin](https://github.com/scaussin).

This two-man project is an implementation of a game of Gomoku.

The gomoku is a variant of the go game, an oriental chess-like game where two players put stones on a wood board.
In the original go game, players have to occupate the biggest area on the board by capturing adverse stones and placing stones.

In the gomoku variant, the board and the stones are the same, but the goal is to align 5 stones. ("go" meaning "5" in japanese)
This game is also known as "pente" or "darpion".

Our project recreate a fully functional gomoku game. We implemented the whole game with C++, with the SDL2 framework for
displaying the game, and with an intensive use of the min-max algorithm.

The core of this project is the IA. By using the min-max algorithm, the IA analyses the board, and "search" for the most interesting
move to make, thanks to our game heuristic. Then, the IA analyzes the move that the players might make at the next turn, and then
its own next-next move, and this as much as its "depth" of intelligence asks it.

You get it, the IA does not just analyse the most interesting move. It searches the best move for the next projected possibilities.
That is the core of min-max: searching for the move that give the maximum of point (best outcome), for the minimum of loss.

This makes a program that looks alive in its play-style, by trying to create forms on several turns.

Aside from its algorithm, the IA also have an advanced heuristic, that is a means of evaluating the board. For this, we used theories
about gomoku, especially the threat-space search devised by L. V. Allis and M. P. H. Huntjens. This theory defines "forms" that leads
to victory. Our program search for these forms on several turns, which makes it very agile in its play style, as there are several
threat forms, that can be combined.

For more on threat-space search, see [this documentation](http://www.renju.nu/wp-content/uploads/sites/46/2016/09/Go-Moku.pdf).

Video of the game:

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/A97sY5tTSNk/0.jpg)](https://www.youtube.com/watch?v=A97sY5tTSNk)
