#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

# include "Gomoku.hpp"

class Heuristic
{
	public:
		static int		EvaluateBoard(Board &board, t_Color playerColor);

	private:
		static int		simpleSearchPatterns(Board &board,
							t_vec2 point, t_Color playerColor, t_dir dir,
							std::string &line, std::string &backLine);
		static int		threatSpaceSearchPatterns(Board &board,
							t_vec2 point, t_Color playerColor, t_dir dir,
							std::string &line, std::string &backLine);
};

#endif
