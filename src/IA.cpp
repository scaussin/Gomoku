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
	Board	*finalMove;
	srand (time(NULL));

	decidedMove.x = 0;
	decidedMove.y = 0;

	finalMove = alphaBeta(&gameDatas.Board, IA_DEEP, ALPHA, BETA, WHITE, WHITE);
	// BoardTools::printParents(finalMove);
	decidedMove = BoardTools::getFistMove(finalMove);
	//cout << "final move: " << BoardTools::countChild(&gameDatas.Board) << " | heuristic to find: " << heuristic << endl << endl;
	for (std::vector<Board *>::iterator it = gameDatas.Board.next.begin() ; it != gameDatas.Board.next.end() ; ++it)
	{
		delete *it;
	}
	gameDatas.Board.next.clear();

	//cout << "child: " << BoardTools::countChild(&gameDatas.Board) << endl;
	//PERROR("move not found in child");
	return (decidedMove);
}

Board	*IA::alphaBeta(Board *board, int deep, int alpha, int beta, t_Color player, t_Color decideMoveFor)
{
	Board	*valBoard = NULL;
	Board	*bestBoard = NULL;

	if (deep == 0 || board->isVictory)
	{
		if (player == decideMoveFor)
			return (board);
		else
		{
			board->heuristic = -board->heuristic;
			return (board);
		}	
	}
	else
	{
		bestBoard = new Board();
		bestBoard->heuristic = ALPHA;

		generatePossibleBoards(board, player, decideMoveFor);
		for (std::vector<Board *>::iterator it = board->next.begin() ; it != board->next.end() ; ++it)
		{
			valBoard = alphaBeta(*it, deep - 1, -beta, -alpha, Tools::inverseColorPlayer(player), decideMoveFor);
			valBoard->heuristic = -valBoard->heuristic;
			if (valBoard->heuristic > bestBoard->heuristic)
			{
				bestBoard = valBoard;
				if (bestBoard->heuristic > alpha)
				{
					alpha = bestBoard->heuristic;
					if (alpha >= beta)
						return (bestBoard);
				}
			}
		}
		return (bestBoard);
	}
}

void	IA::generatePossibleBoards(Board *board, t_Color player, t_Color decideMoveFor)
{
	static t_vec2	move_tmp;
	static int		x;
	static int		y;

	for (y = 0; y < 19; y++)
	{
		for (x = 0; x < 19; x++)
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
				newBoard->heuristic = Heuristic::EvaluateBoard(*newBoard, decideMoveFor);
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
