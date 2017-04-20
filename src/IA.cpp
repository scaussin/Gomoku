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
	return (decidedMove);
}
