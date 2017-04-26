#include "../includes/Gomoku.hpp"

GameRules::GameRules()
{

}

GameRules::~GameRules()
{

}

bool	GameRules::IsMoveAuthorized(Board &Board, t_Color color, t_vec2 move)
{
	(void)move;

	if (Board.Map[move.y][move.x] == NONE || Board.Map[move.y][move.x] == SUGGESTION)
	{
		if (HasDoubleThree(Board, color, move) == 1)
		{
			return (false);
		}
		return (true);
	}
	else
		return (false);
	return (true);
}

void		GameRules::doCaptures(Board &board, t_Color color, t_vec2 move)
{
	t_Color enemy;

	if (color == BLACK)
		enemy = WHITE;
	else
		enemy = BLACK;
	
	//top left
	if (board.getPoint(move.y + 1,  move.x - 1) == enemy && board.getPoint(move.y + 2,  move.x - 2) == enemy && board.getPoint(move.y + 3,  move.x - 3) == color)
	{
		board.setPoint(move.y + 1,  move.x - 1, NONE);
		board.setPoint(move.y + 2,  move.x - 2, NONE);
		cout << "capture top left" << endl;
	}
	//top
	if (board.getPoint(move.y + 1,  move.x) == enemy && board.getPoint(move.y + 2,  move.x) == enemy && board.getPoint(move.y + 3,  move.x) == color)
	{
		board.setPoint(move.y + 1,  move.x, NONE);
		board.setPoint(move.y + 2,  move.x, NONE);
		cout << "capture top" << endl;
	}
	//top right
	if (board.getPoint(move.y + 1,  move.x + 1) == enemy && board.getPoint(move.y + 2,  move.x + 2) == enemy && board.getPoint(move.y + 3,  move.x + 3) == color)
	{
		board.setPoint(move.y + 1,  move.x + 1, NONE);
		board.setPoint(move.y + 2,  move.x + 2, NONE);
		cout << "capture top right" << endl;
	}
	// right
	if (board.getPoint(move.y,  move.x + 1) == enemy && board.getPoint(move.y,  move.x + 2) == enemy && board.getPoint(move.y,  move.x + 3) == color)
	{
		board.setPoint(move.y,  move.x + 1, NONE);
		board.setPoint(move.y,  move.x + 2, NONE);
		cout << "capture right" << endl;
	}
	//bottom right
	if (board.getPoint(move.y - 1,  move.x + 1) == enemy && board.getPoint(move.y - 2,  move.x + 2) == enemy && board.getPoint(move.y - 3,  move.x + 3) == color)
	{
		board.setPoint(move.y - 1,  move.x + 1, NONE);
		board.setPoint(move.y - 2,  move.x + 2, NONE);
		cout << "capture bottom right" << endl;
	}
	//bottom
	if (board.getPoint(move.y - 1,  move.x) == enemy && board.getPoint(move.y - 2,  move.x) == enemy && board.getPoint(move.y - 3,  move.x) == color)
	{
		board.setPoint(move.y - 1,  move.x, NONE);
		board.setPoint(move.y - 2,  move.x, NONE);
		cout << "capture bottom" << endl;
	}
	//bottom left
	if (board.getPoint(move.y - 1,  move.x - 1) == enemy && board.getPoint(move.y - 2,  move.x - 2) == enemy && board.getPoint(move.y - 3,  move.x - 3) == color)
	{
		board.setPoint(move.y - 1,  move.x - 1, NONE);
		board.setPoint(move.y - 2,  move.x - 2, NONE);
		cout << "capture bottom left" << endl;
	}
	//left
	if (board.getPoint(move.y,  move.x - 1) == enemy && board.getPoint(move.y,  move.x - 2) == enemy && board.getPoint(move.y,  move.x - 3) == color)
	{
		board.setPoint(move.y,  move.x - 1, NONE);
		board.setPoint(move.y,  move.x - 2, NONE);
		cout << "capture left" << endl;
	}
}

bool	GameRules::HasDoubleThree(Board &Board, t_Color color, t_vec2 move)
{
	(void)Board;
	(void)color;
	(void)move;
	return (false);
}

void	GameRules::CheckVictory(t_GameDatas &GameDatas)
{
	(void)GameDatas;
}
