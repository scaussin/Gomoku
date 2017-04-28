#ifndef BOARD_HPP
# define BOARD_HPP

#include "Gomoku.hpp"

class Board
{
	public:
		Board();
		~Board();

		// attributes
		char			Map[19][19];
		int				HeuristicValue;

		bool			isVictory;

		int				BlackCaptures;
		int				WhiteCaptures;

		// methods
		// copy overload
		Board			&operator=(const Board& other);
		char			getPoint(t_vec2 at);
		char			getPoint(int y, int x);
		bool			setPoint(t_vec2 at, t_Color color);
		bool 			setPoint(int y, int x, t_Color color);
};

#endif
