#include "../includes/Gomoku.hpp"

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