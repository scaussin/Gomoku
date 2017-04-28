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

t_vec2		IA::decideMove(t_GameDatas &gameDatas)
{
	t_vec2 decidedMove;
	srand (time(NULL));

	decidedMove.x = 0;
	decidedMove.y = 0;

	alphaBeta(&gameDatas.Board, IA_DEEP, ALPHA, BETA, gameDatas.ActivePlayer, gameDatas.ActivePlayer);
	// for (int i = 0; i < IA_DEEP ; i++)
	// {
	// 	generatePossibleBoards(gameDatas.Board, gameDatas.ActivePlayer);
	// }
	//GeneratePossibleBoards(GameDatas, GameDatas.Board);
	//StateExpanding.clear();
	return (decidedMove);
}

int		IA::alphaBeta(Board *board, int deep, int alpha, int beta, t_Color player, t_Color decideMoveFor)
{
	int val;
	int best;

	if (deep == 0 || board->isVictory)
	{
		return (board->heuristic);
	}
	else
	{
		best = ALPHA;
		generatePossibleBoards(board, player, decideMoveFor);
		for (auto it = board->next.begin() ; it != board->next.end() ; ++it)
		{
			val = -alphaBeta(*it, deep - 1, -beta, -alpha, Tools::inverseColorPlayer(player), decideMoveFor);
			if (val > best)
			{
				best = val;
				if (best > alpha)
				{
					alpha = best;
					if (alpha >= beta)
						return (best);
				}
			}
		}
		return (best);
	}
}

void	IA::generatePossibleBoards(Board *board, t_Color player, t_Color decideMoveFor)
{
	t_vec2			move_tmp;

	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			if (board->map[y][x] == WHITE || board->map[y][x] == BLACK)
			{
				move_tmp.x = x;
				move_tmp.y = y;
				generateBoardsFromPoint(board, move_tmp, board->next, player, decideMoveFor);
			}
		}
	}
	//std::cout << "nb of possible boards for current board: " << board.next.size() << std::endl;
}

/*
**	Generate all the boards for the given point into the given possibleBoards, from the curBoard.
**	We know the board's point is either BLACK or WHITE.
**	We check the adjacent points, and create boards for them.
*/

void	IA::generateBoardsFromPoint(Board *curBoard, t_vec2 point, vector<Board*> &possibleBoards, t_Color player, t_Color decideMoveFor)
{
	int		i = 8;
	Board*	newBoard;
	t_vec2	nextMove;

	nextMove.x = point.x - 1;
	nextMove.y = point.y + 1;
	while (i != -1)
	{
		if (BoardTools::IsPointIn(nextMove)
			&& curBoard->map[nextMove.y][nextMove.x] == NONE)
		{
			if (GameRules::isMoveAuthorized(*curBoard, player, nextMove))
			{
				newBoard = new Board(*curBoard, curBoard, nextMove, player);
				GameRules::doCaptures(*newBoard, player, nextMove);
				newBoard->heuristic = rand() % 10 + 1;
				newBoard->heuristic = Heuristic::EvaluateBoard(*newBoard, decideMoveFor) - Heuristic::EvaluateBoard(*newBoard, Tools::inverseColorPlayer(decideMoveFor));
				// we only add it if it is not already in our list.
				if (BoardTools::IsInList(*newBoard, possibleBoards) == false)
				{
					// BoardTools::DisplayBoardChars(newBoard_cpy);
					// printf("\n");
					possibleBoards.push_back(newBoard);
				}
			}
		}
		nextMove.x += 1;
		if (i % 3 == 0)
		{
			nextMove.x -= 3;
			nextMove.y -= 1;
		}
		i--;
	}
}
