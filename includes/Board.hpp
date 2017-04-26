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

		// methods
		// copy overload
		Board			&operator=(const Board& other);
};

#endif
