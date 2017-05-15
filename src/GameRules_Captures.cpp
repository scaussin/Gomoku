#include "../includes/Gomoku.hpp"

/*
**	Check is the move is making a capture. If yes, it applies the capture
**	to the board.
*/

void		GameRules::doCaptures(Board &board, t_Color color, t_vec2 move)
{
	t_Color enemy = Tools::inverseColorPlayer(color);
	
	//top left
	if (board.getPoint(move.y + 1,  move.x - 1) == enemy
		&& board.getPoint(move.y + 2,  move.x - 2) == enemy
		&& board.getPoint(move.y + 3,  move.x - 3) == color)
	{
		applyCapture(board, color, move.x - 1, move.y + 1, move.x - 2, move.y + 2);
		// cout << "- Capture top left" << endl;
	}
	//top
	if (board.getPoint(move.y + 1,  move.x) == enemy
		&& board.getPoint(move.y + 2,  move.x) == enemy
		&& board.getPoint(move.y + 3,  move.x) == color)
	{
		applyCapture(board, color, move.x, move.y + 1, move.x, move.y + 2);
		// cout << "- Capture top" << endl;
	}
	//top right
	if (board.getPoint(move.y + 1,  move.x + 1) == enemy
		&& board.getPoint(move.y + 2,  move.x + 2) == enemy
		&& board.getPoint(move.y + 3,  move.x + 3) == color)
	{
		applyCapture(board, color, move.x + 1, move.y + 1, move.x + 2, move.y + 2);
		// cout << "- Capture top right" << endl;
	}
	// right
	if (board.getPoint(move.y,  move.x + 1) == enemy
		&& board.getPoint(move.y,  move.x + 2) == enemy
		&& board.getPoint(move.y,  move.x + 3) == color)
	{
		applyCapture(board, color, move.x + 1, move.y, move.x + 2, move.y);
		// cout << "- Capture right" << endl;
	}
	//bottom right
	if (board.getPoint(move.y - 1,  move.x + 1) == enemy
		&& board.getPoint(move.y - 2,  move.x + 2) == enemy
		&& board.getPoint(move.y - 3,  move.x + 3) == color)
	{
		applyCapture(board, color, move.x + 1, move.y - 1, move.x + 2, move.y - 2);
		// cout << "- Capture bottom right" << endl;
	}
	//bottom
	if (board.getPoint(move.y - 1,  move.x) == enemy
		&& board.getPoint(move.y - 2,  move.x) == enemy
		&& board.getPoint(move.y - 3,  move.x) == color)
	{
		applyCapture(board, color, move.x, move.y - 1, move.x, move.y - 2);
		// cout << "- Capture bottom" << endl;
	}
	//bottom left
	if (board.getPoint(move.y - 1,  move.x - 1) == enemy
		&& board.getPoint(move.y - 2,  move.x - 2) == enemy
		&& board.getPoint(move.y - 3,  move.x - 3) == color)
	{
		applyCapture(board, color, move.x - 1, move.y - 1, move.x - 2, move.y - 2);
		// cout << "- Capture bottom left" << endl;
	}
	//left
	if (board.getPoint(move.y,  move.x - 1) == enemy
		&& board.getPoint(move.y,  move.x - 2) == enemy
		&& board.getPoint(move.y,  move.x - 3) == color)
	{
		applyCapture(board, color, move.x - 1, move.y, move.x - 2, move.y);
		// cout << "- Capture left" << endl;
	}
}


void		GameRules::applyCapture(Board &board, t_Color color,
				int stone1_x, int stone1_y, int stone2_x, int stone2_y)
{
	board.setPoint(stone1_y,  stone1_x, NONE);
	board.setPoint(stone2_y,  stone2_x, NONE);
	if (color == BLACK)
	{
		board.BlackCaptures += 2;
	}
	else
	{
		board.WhiteCaptures += 2;
	}
	board.heuristic += CAPTURE_DONE;
	board.preheuristic += CAPTURE_DONE;
}

/*
**	Return true if the given move is making a capture.
*/

bool		GameRules::checkCaptures(Board &board, t_Color color, t_vec2 move)
{
	static t_Color enemy;

	if (color == BLACK)
		enemy = WHITE;
	else
		enemy = BLACK;
	
	// top left
	if (board.getPoint(move.y + 1,  move.x - 1) == enemy
		&& board.getPoint(move.y + 2,  move.x - 2) == enemy
		&& board.getPoint(move.y + 3,  move.x - 3) == color)
	{
		return (true);
	}
	// top
	if (board.getPoint(move.y + 1,  move.x) == enemy
		&& board.getPoint(move.y + 2,  move.x) == enemy
		&& board.getPoint(move.y + 3,  move.x) == color)
	{
		return (true);
	}
	// top right
	if (board.getPoint(move.y + 1,  move.x + 1) == enemy
		&& board.getPoint(move.y + 2,  move.x + 2) == enemy
		&& board.getPoint(move.y + 3,  move.x + 3) == color)
	{
		return (true);
	}
	// right
	if (board.getPoint(move.y,  move.x + 1) == enemy
		&& board.getPoint(move.y,  move.x + 2) == enemy
		&& board.getPoint(move.y,  move.x + 3) == color)
	{
		return (true);
	}
	// bottom right
	if (board.getPoint(move.y - 1,  move.x + 1) == enemy
		&& board.getPoint(move.y - 2,  move.x + 2) == enemy
		&& board.getPoint(move.y - 3,  move.x + 3) == color)
	{
		return (true);
	}
	// bottom
	if (board.getPoint(move.y - 1,  move.x) == enemy
		&& board.getPoint(move.y - 2,  move.x) == enemy
		&& board.getPoint(move.y - 3,  move.x) == color)
	{
		return (true);
	}
	// bottom left
	if (board.getPoint(move.y - 1,  move.x - 1) == enemy
		&& board.getPoint(move.y - 2,  move.x - 2) == enemy
		&& board.getPoint(move.y - 3,  move.x - 3) == color)
	{
		return (true);
	}
	// left
	if (board.getPoint(move.y,  move.x - 1) == enemy
		&& board.getPoint(move.y,  move.x - 2) == enemy
		&& board.getPoint(move.y,  move.x - 3) == color)
	{
		return (true);
	}
	return (false);
}

/*
**	UNUSED -> seems like a subject's error. the rules says we can do that.
**	Return true if the given move is into a capture,
**	checked for a given direction, with pattern checks.
*/

bool			GameRules::checkBlackMovingIntoCapture(Board &board,
						t_vec2 move, t_dir dir,
						char *line, char *backLine)
{
	if (strncmp(line, "012", 3) == 0
		&& strncmp(backLine, "02", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line, "02", 2) == 0
		&& strncmp(backLine, "012", 3) == 0)
	{
		return (true);
	}
	return (false);
}

bool			GameRules::checkWhiteMovingIntoCapture(Board &board,
						t_vec2 move, t_dir dir,
						char *line, char *backLine)
{
	if (strncmp(line, "021", 3) == 0
		&& strncmp(backLine, "01", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line, "01", 2) == 0
		&& strncmp(backLine, "021", 3) == 0)
	{
		return (true);
	}
	return (false);
}

/*
**	Could the given stone be captured in one move ?
*/

bool			GameRules::IsBlackStoneCapturable(Board &board,
						t_vec2 stone, t_dir dir,
						char *line, char *backLine)
{
	if (strncmp(line, "112", 3) == 0
		&& strncmp(backLine, "10", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line, "110", 3) == 0
		&& strncmp(backLine, "12", 2) == 0)
	{
		return (true);
	}
	return (false);
}

bool			GameRules::IsWhiteStoneCapturable(Board &board,
						t_vec2 stone, t_dir dir,
						char *line, char *backLine)
{
	if (strncmp(line, "221", 3) == 0
		&& strncmp(backLine, "20", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line, "220", 3) == 0
		&& strncmp(backLine, "21", 2) == 0)
	{
		return (true);
	}
	return (false);
}