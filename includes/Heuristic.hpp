#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

# include "Gomoku.hpp"

class Heuristic
{
	public:
		static int		EvaluateBoard(Board &board, t_Color player);

		static int		Simple(Board &board, t_Color player);
};

#endif
