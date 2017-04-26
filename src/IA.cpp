#include "../includes/Gomoku.hpp"

IA::IA()
{

}

IA::~IA()
{

}

// ------------------------------------------------------------------ //
//	The main method for the IA Class. This will send back the		  //
//	ia's decided move.												  //
//																	  //
// ------------------------------------------------------------------ //

t_vec2		IA::DecideMove(t_GameDatas &GameDatas)
{
	(void)GameDatas;
	t_vec2 decidedMove;

	decidedMove.x = 0;
	decidedMove.y = 0;
	// GeneratePossibleBoards(GameDatas, GameDatas.Board);
	// StateExpanding.clear();
	return (decidedMove);
}

void	IA::GeneratePossibleBoards(t_GameDatas &GameDatas, Board &curBoard)
{
	(void)GameDatas;
	(void)curBoard;

	t_vec2		move_tmp;
	int			x = 0;
	int			y = 0;
	for (; y < 19; y++)
	{
		for (x = 0; x < 19; x++)
		{
			if (curBoard.Map[y][x] == BLACK || curBoard.Map[y][x] == WHITE)
			{
				move_tmp.x = x;
				move_tmp.y = y;
				GenerateBoardsForPoint(curBoard, move_tmp, StateExpanding);
			}
		}
	}
	std::cout << "nb of possible boards for current board: " << StateExpanding.size() << std::endl;
}

/*
**	Generate all the boards for the given point into the given boardList, from the curBoard.
**	We know the board's point is either BLACK or WHITE.
**	We check the adjacent points, and create boards for them.
*/

void	IA::GenerateBoardsForPoint(Board &curBoard, t_vec2 point, std::vector<Board> &boardList)
{
	int		i = 8;
	Board	newBoard_cpy;
	t_vec2	search_point;

	search_point.x = point.x - 1;
	search_point.y = point.y + 1;
	while (i != -1)
	{
		if (BoardTools::IsPointIn(search_point)
			&& curBoard.Map[search_point.y][search_point.x] == NONE)
		{
			if (GameRules::IsMoveAuthorized(curBoard, WHITE, search_point))
			{
				newBoard_cpy = curBoard;
				BoardTools::SetPointValue(newBoard_cpy, search_point.x, search_point.y, WHITE);
				// we only add it if it is not already in our list.
				if (BoardTools::IsInList(newBoard_cpy, boardList) == false)
				{
					// BoardTools::DisplayBoardChars(newBoard_cpy);
					// printf("\n");
					boardList.push_back(newBoard_cpy);
				}
			}
		}
		search_point.x += 1;
		if (i % 3 == 0)
		{
			search_point.x -= 3;
			search_point.y -= 1;
		}
		i--;
	}
}
