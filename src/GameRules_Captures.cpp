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
		board.setPoint(move.y + 1,  move.x - 1, NONE);
		board.setPoint(move.y + 2,  move.x - 2, NONE);
		cout << "capture top left" << endl;
	}
	//top
	if (board.getPoint(move.y + 1,  move.x) == enemy
		&& board.getPoint(move.y + 2,  move.x) == enemy
		&& board.getPoint(move.y + 3,  move.x) == color)
	{
		board.setPoint(move.y + 1,  move.x, NONE);
		board.setPoint(move.y + 2,  move.x, NONE);
		cout << "capture top" << endl;
	}
	//top right
	if (board.getPoint(move.y + 1,  move.x + 1) == enemy
		&& board.getPoint(move.y + 2,  move.x + 2) == enemy
		&& board.getPoint(move.y + 3,  move.x + 3) == color)
	{
		board.setPoint(move.y + 1,  move.x + 1, NONE);
		board.setPoint(move.y + 2,  move.x + 2, NONE);
		cout << "capture top right" << endl;
	}
	// right
	if (board.getPoint(move.y,  move.x + 1) == enemy
		&& board.getPoint(move.y,  move.x + 2) == enemy
		&& board.getPoint(move.y,  move.x + 3) == color)
	{
		board.setPoint(move.y,  move.x + 1, NONE);
		board.setPoint(move.y,  move.x + 2, NONE);
		cout << "capture right" << endl;
	}
	//bottom right
	if (board.getPoint(move.y - 1,  move.x + 1) == enemy
		&& board.getPoint(move.y - 2,  move.x + 2) == enemy
		&& board.getPoint(move.y - 3,  move.x + 3) == color)
	{
		board.setPoint(move.y - 1,  move.x + 1, NONE);
		board.setPoint(move.y - 2,  move.x + 2, NONE);
		cout << "capture bottom right" << endl;
	}
	//bottom
	if (board.getPoint(move.y - 1,  move.x) == enemy
		&& board.getPoint(move.y - 2,  move.x) == enemy
		&& board.getPoint(move.y - 3,  move.x) == color)
	{
		board.setPoint(move.y - 1,  move.x, NONE);
		board.setPoint(move.y - 2,  move.x, NONE);
		cout << "capture bottom" << endl;
	}
	//bottom left
	if (board.getPoint(move.y - 1,  move.x - 1) == enemy
		&& board.getPoint(move.y - 2,  move.x - 2) == enemy
		&& board.getPoint(move.y - 3,  move.x - 3) == color)
	{
		board.setPoint(move.y - 1,  move.x - 1, NONE);
		board.setPoint(move.y - 2,  move.x - 2, NONE);
		cout << "capture bottom left" << endl;
	}
	//left
	if (board.getPoint(move.y,  move.x - 1) == enemy
		&& board.getPoint(move.y,  move.x - 2) == enemy
		&& board.getPoint(move.y,  move.x - 3) == color)
	{
		board.setPoint(move.y,  move.x - 1, NONE);
		board.setPoint(move.y,  move.x - 2, NONE);
		cout << "capture left" << endl;
	}
}

/*
**	Return true if the given move is making a capture.
*/

bool		GameRules::checkCaptures(Board &board, t_Color color, t_vec2 move)
{
	t_Color enemy;

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
						std::string &line, std::string &backLine)
{
	if (strncmp(line.c_str(), "012", 3) == 0
		&& strncmp(backLine.c_str(), "02", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line.c_str(), "02", 2) == 0
		&& strncmp(backLine.c_str(), "012", 3) == 0)
	{
		return (true);
	}
	return (false);
}

bool			GameRules::checkWhiteMovingIntoCapture(Board &board,
						t_vec2 move, t_dir dir,
						std::string &line, std::string &backLine)
{
	if (strncmp(line.c_str(), "021", 3) == 0
		&& strncmp(backLine.c_str(), "01", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line.c_str(), "01", 2) == 0
		&& strncmp(backLine.c_str(), "021", 3) == 0)
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
						std::string &line, std::string &backLine)
{
	if (strncmp(line.c_str(), "112", 3) == 0
		&& strncmp(backLine.c_str(), "10", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line.c_str(), "110", 3) == 0
		&& strncmp(backLine.c_str(), "12", 2) == 0)
	{
		return (true);
	}
	return (false);
}

bool			GameRules::IsWhiteStoneCapturable(Board &board,
						t_vec2 stone, t_dir dir,
						std::string &line, std::string &backLine)
{
	if (strncmp(line.c_str(), "221", 3) == 0
		&& strncmp(backLine.c_str(), "20", 2) == 0)
	{
		return (true);
	}
	else if (strncmp(line.c_str(), "220", 3) == 0
		&& strncmp(backLine.c_str(), "21", 2) == 0)
	{
		return (true);
	}
	return (false);
}