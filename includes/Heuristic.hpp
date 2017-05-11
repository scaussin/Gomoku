#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

# include "Gomoku.hpp"

class Heuristic
{
	public:
		// static ThreadPool	g_ThreadPool;

		static int			EvaluateBoard(Board &board, t_Color &playerColor);


		static void			EvaluateOneDir(Board *board,
								t_Color *playerColor, t_vec2 *curPoint,
								int *dir, int *retval);
		static void			EvaluateAllDir(Board *board,
								t_Color *playerColor, t_vec2 *curPoint,
								int *retval);

	private:
		// static void			EvaluateOneDir(Board *board,
		// 					t_Color *playerColor, t_vec2 *curPoint,
		// 					t_dir dir, int *retval);


		// VICTORY SEARCH: forms of victory. give a lot of points.
		static int		victorySearchPatterns(Board &board,
							t_vec2 point, t_Color playerColor, t_dir dir,
							char *line, char *backLine);
		static bool		isBlackStoneCapturable(Board &board,
							t_vec2 stone, t_dir dir,
							char *line, char *backLine);
		static bool		isWhiteStoneCapturable(Board &board,
							t_vec2 stone, t_dir dir,
							char *line, char *backLine);

		// SIMPLE SEARCH: form that give less points, but can tip the balance.
		static int		simpleSearchPatterns(Board &board,
							t_vec2 point, t_Color playerColor, t_dir dir,
							char *line, char *backLine);

		// THREAT SPACE SEARCH: forms that are going toward victory.
		static int		threatSpaceSearchPatterns(Board &board,
							t_vec2 point, t_Color playerColor, t_dir dir,
							char *line, char *backLine);

		// CAPTURE SEARCH: forms that make captures. Am I in danger ? can I get a quick victory ?
		static int		captureSearchPatterns(Board &board,
							t_vec2 point, t_Color playerColor, t_dir dir,
							char *line, char *backLine);
};

#endif
