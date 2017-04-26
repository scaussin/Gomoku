#include "../includes/Gomoku.hpp"

// --------------------------------------------------------	//
//															//
//	Main Heuristic Function.								//
//	Returns a int heuristic value.							//
//															//
// --------------------------------------------------------	//

int		Heuristic::EvaluateBoard(Board &board, t_Color player)
{
	int		boardValue;

	boardValue = 0;
	boardValue += Heuristic::Simple(board, player);

	return (boardValue);
}

/*
**	A simple heuristic to start our IA.
*/

int		Heuristic::Simple(Board &board, t_Color player)
{
	int			boardValue;
	t_Color		enemyColor;

	(void)board;
	// set enemy color, the stones we will first look at.
	if (player == BLACK)
		enemyColor = WHITE;
	else
		enemyColor = BLACK;

	boardValue = 0;
	return (boardValue);
}
