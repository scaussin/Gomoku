#include "../includes/Gomoku.hpp"

IA::IA()
{

}

IA::~IA()
{

}

t_vec2		IA::DecideMove(t_GameDatas &GameDatas)
{
	(void)GameDatas;
	t_vec2 decidedMove;

	decidedMove.x = 0;
	decidedMove.y = 0;
	GeneratePossibleBoards(GameDatas, GameDatas.Board);

	return (decidedMove);
}

void	IA::GeneratePossibleBoards(t_GameDatas &GameDatas, Board &curBoard)
{
	(void)GameDatas;
	(void)curBoard;
	//BoardTools::DisplayBoardChars(curBoard);
}
