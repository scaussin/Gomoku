#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

# include "Gomoku.hpp"

class Heuristic
{
	public:
		static int		EvaluateBoard(Board &board, t_Color playerColor);

	private:
		// VICTORY SEARCH: forms of victory. give a lot of points.
		static int		victorySearchPatterns(Board &board,
							t_vec2 point, t_Color playerColor, t_dir dir,
							std::string &line, std::string &backLine);
		static int		victorySearchPatternsBlack(Board &board,
							t_vec2 point, t_dir dir,
							std::string &line, std::string &backLine);
		static int		victorySearchPatternsWhite(Board &board,
							t_vec2 point, t_dir dir,
							std::string &line, std::string &backLine);
		static bool		isBlackStoneCapturable(Board &board,
							t_vec2 stone, t_dir dir,
							std::string &line, std::string &backLine);
		static bool		isWhiteStoneCapturable(Board &board,
							t_vec2 stone, t_dir dir,
							std::string &line, std::string &backLine);

		// SIMPLE SEARCH: form that give less points, but can tip the balance.
		static int		simpleSearchPatterns(Board &board,
							t_vec2 point, t_Color playerColor, t_dir dir,
							std::string &line, std::string &backLine);
		static int		simpleSearchPatternsBlack(Board &board,
							t_vec2 point, t_dir dir,
							std::string &line, std::string &backLine);
		static int		simpleSearchPatternsWhite(Board &board,
							t_vec2 point, t_dir dir,
							std::string &line, std::string &backLine);

		// THREAT SPACE SEARCH: forms that are going toward victory.
		static int		threatSpaceSearchPatterns(Board &board,
							t_vec2 point, t_Color playerColor, t_dir dir,
							std::string &line, std::string &backLine);
		static int		threatSpaceSearchPatternsBlack(Board &board,
							t_vec2 point, t_dir dir,
							std::string &line, std::string &backLine);
		static int		threatSpaceSearchPatternsWhite(Board &board,
							t_vec2 point, t_dir dir,
							std::string &line, std::string &backLine);
};

#endif
