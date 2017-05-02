#include "../includes/Gomoku.hpp"

GameRules::GameRules()
{

}

GameRules::~GameRules()
{

}

bool	GameRules::isMoveAuthorized(Board &board, t_Color color, t_vec2 move)
{
	(void)move;

	if (board.map[move.y][move.x] == NONE || board.map[move.y][move.x] == SUGGESTION)
	{
		if (checkForbiddenPatterns(board, color, move) == true
			&& checkCaptures(board, color, move) == false) // a capture can create a double free three.
		{
			return (false);
		}
		return (true);
	}
	else
		return (false);
	return (true);
}

bool	GameRules::checkForbiddenPatterns(Board &board, t_Color color, t_vec2 move)
{
	int				nb_free_3;

	static int		dir;
	static char		line[5];
	static char		backLine[5];

	dir = 1;
	nb_free_3 = 0;
	// for the move, we look in all directions.
	while (dir != 9)
	{
		// for each direction, we extract a string.
		Tools::GetPatternPointsLine(line, board, move, (t_dir)dir, 5, color);
		Tools::GetPatternPointsLine(backLine, board, move, Tools::GetOppositeDir((t_dir)dir), 5, color);
		// patterns are different for each color.
		nb_free_3 += checkDoubleThreePatterns(board,
						move, (t_dir)dir, line, backLine);
		dir++;
	}
	// std::cout << "Created " << KYEL << nb_free_3 << KRESET << " free three(s) with this move." << std::endl;
	if (nb_free_3 >= 2)
	{
		return (true);
	}
	return (false);
}
