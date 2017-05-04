#include "../includes/Gomoku.hpp"

 
double time_decideMove = 0;
double time_AlphaBeta = 0;
double time_generateBoardsFromPoint = 0;
double time_generatePossibleBoards = 0;

double time_IsPointIn = 0;
double time_isMoveAuthorized = 0;
double time_newBoard = 0;
double time_doCaptures = 0;
double time_EvaluateBoard = 0;

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
	int start = clock();

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

	time_decideMove += (clock() - start) / double(CLOCKS_PER_SEC) * 1000;
	//time_EvaluateBoard = 0;

	return (decidedMove);
}

Board	*IA::alphaBeta(Board *board, int deep, int alpha, int beta, t_Color player, t_Color decideMoveFor)
{
	int start = clock();
	Board	*valBoard = NULL;
	Board	*bestBoard = NULL;

	if (deep == 0 || board->isVictory)
	{
		if (player == decideMoveFor)
		{
			time_AlphaBeta += (clock() - start) / double(CLOCKS_PER_SEC) * 1000;
			return (board);
		}
		else
		{
			board->heuristic = -board->heuristic;
			time_AlphaBeta += (clock() - start) / double(CLOCKS_PER_SEC) * 1000;
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
			time_AlphaBeta += (clock() - start) / double(CLOCKS_PER_SEC) * 1000;
			valBoard = alphaBeta(*it, deep - 1, -beta, -alpha, Tools::inverseColorPlayer(player), decideMoveFor);
			start = clock();
			valBoard->heuristic = -valBoard->heuristic;
			if (valBoard->heuristic > bestBoard->heuristic)
			{
				bestBoard = valBoard;
				if (bestBoard->heuristic > alpha)
				{
					alpha = bestBoard->heuristic;
					if (alpha >= beta)
					{
						time_AlphaBeta += (clock() - start) / double(CLOCKS_PER_SEC) * 1000;
						return (bestBoard);
					}
				}
			}
		}
		time_AlphaBeta += (clock() - start) / double(CLOCKS_PER_SEC) * 1000;
		return (bestBoard);
	}
}

void	IA::generatePossibleBoards(Board *board, t_Color player, t_Color decideMoveFor)
{
	int start = clock();
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
	time_generatePossibleBoards += (clock() - start) / double(CLOCKS_PER_SEC) * 1000;
	//std::cout << "nb of possible boards for current board: " << board.next.size() << std::endl;
}

/*
**	Generate all the boards for the given point into the given possibleBoards, from the curBoard.
**	We know the board's point is either BLACK or WHITE.
**	We check the adjacent points, and create boards for them.
*/

void	IA::generateBoardsFromPoint(Board *curBoard, t_vec2 point, vector<Board*> &possibleBoards, t_Color player, t_Color decideMoveFor)
{
	int start = clock();
	int		i = 8;
	Board*	newBoard;
	t_vec2	nextMove;
	bool b_isPointIn;
	bool b_isMoveAuthorized;

	nextMove.x = point.x - 1;
	nextMove.y = point.y + 1;
	while (i != -1)
	{
		int start_IsPointIn = clock();
		b_isPointIn = BoardTools::IsPointIn(nextMove);
		time_IsPointIn += (clock() - start_IsPointIn) / double(CLOCKS_PER_SEC) * 1000;

		if (b_isPointIn && curBoard->map[nextMove.y][nextMove.x] == NONE)
		{
			int start_isMoveAuthorized = clock();
			b_isMoveAuthorized = GameRules::isMoveAuthorized(*curBoard, player, nextMove);
			time_isMoveAuthorized += (clock() - start_isMoveAuthorized) / double(CLOCKS_PER_SEC) * 1000;

			if (b_isMoveAuthorized)
			{
				int start_newBoard = clock();
				newBoard = new Board(*curBoard, curBoard, nextMove, player);
				time_newBoard += (clock() - start_newBoard) / double(CLOCKS_PER_SEC) * 1000;

				int start_doCapture = clock();
				GameRules::doCaptures(*newBoard, player, nextMove);
				time_doCaptures += (clock() - start_doCapture) / double(CLOCKS_PER_SEC) * 1000;

				int start_EvaluateBoard = clock();
				newBoard->heuristic = Heuristic::EvaluateBoard(*newBoard, decideMoveFor);
				time_EvaluateBoard += (clock() - start_EvaluateBoard) / double(CLOCKS_PER_SEC) * 1000;
				

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
	time_generateBoardsFromPoint += (clock() - start) / double(CLOCKS_PER_SEC) * 1000;
}
