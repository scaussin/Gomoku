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

bool sortNextMoveRev (Board* a, Board* b)
{ 
	return (a->heuristic > b->heuristic);
}
bool sortNextMove (Board* a, Board* b)
{ 
	return (a->heuristic < b->heuristic);
}


t_vec2		IA::decideMove(t_GameDatas &gameDatas)
{
	t_vec2		decidedMove;
	Board		*finalMove = NULL;

	decidedMove.x = 0;
	decidedMove.y = 0;
	// ----- Quick win search.
	generatePossibleBoards(&gameDatas.Board, gameDatas.ActivePlayer, gameDatas.ActivePlayer, true);
	for (vector<Board *>::iterator it = gameDatas.Board.next.begin() ; it != gameDatas.Board.next.end() ; ++it)
	{
		(*it)->heuristic += Heuristic::EvaluateBoard(**it, gameDatas.ActivePlayer);
		if ((*it)->isVictory)
		{
			finalMove = *it;
			break;
		}
	}
	// ------ if no quick win available.
	if (finalMove == NULL)
	{
		sort(gameDatas.Board.next.begin(), gameDatas.Board.next.end(), sortNextMoveRev);
		finalMove = alphaBeta(&gameDatas.Board, gameDatas.IA_Depth, ALPHA, BETA, gameDatas.ActivePlayer, gameDatas.ActivePlayer);
	}
	//cout << "---------PREVISION-----------" << endl;
	BoardTools::printParents(finalMove);
	decidedMove = BoardTools::getFistMove(finalMove);
	for (vector<Board *>::iterator it = gameDatas.Board.next.begin() ; it != gameDatas.Board.next.end() ; ++it)
	{
		delete *it;
	}
	gameDatas.Board.next.clear();
	return (decidedMove);
}

/*x = 11
y = 8*/

bool sortPreHeur (Board* a, Board* b)
{ 
	return (a->preHeuristic < b->preHeuristic);
}
bool sortPreHeurRev (Board* a, Board* b)
{ 
	return (a->preHeuristic > b->preHeuristic);
}

Board	*IA::alphaBeta(Board *board, int depth, int alpha, int beta, t_Color player, t_Color decideMoveFor)
{
	Board	*valBoard = NULL;
	Board	*bestBoard = NULL;
	bool	toDelete = true;
	
	if (board->next.size() == 0) // Quick win double evaluation protection.
	{
		board->heuristic += Heuristic::EvaluateBoard(*board, decideMoveFor);
	}
	if (depth == 0 || board->isVictory)
	{
		if (player != decideMoveFor)
			board->heuristic = -board->heuristic;
		return (board);
	}
	else
	{	
		bestBoard = new Board();
		bestBoard->heuristic = ALPHA;
		if (board->next.size() == 0)
		{
			generatePossibleBoards(board, player, decideMoveFor, false);
		}
		for (vector<Board *>::iterator it = board->next.begin() ; it != board->next.end() ; ++it)
		{
			valBoard = alphaBeta(*it, depth - 1, -beta, -alpha, Tools::inverseColorPlayer(player), decideMoveFor);
			valBoard->heuristic = -valBoard->heuristic;
			if (valBoard->heuristic > bestBoard->heuristic)
			{
				if (toDelete)
				{
					delete bestBoard;
					toDelete = false;
				}
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

Board *IA::maxBoard(Board *a, Board *b)
{
	return ((a->heuristic > b->heuristic)? a : b);
}

Board *IA::minBoard(Board *a, Board *b)
{
	return ((a->heuristic < b->heuristic)? a : b);
}

void	IA::generatePossibleBoards(Board *board, t_Color player, t_Color decideMoveFor, bool isFirstDepth)
{
	for (vector<t_vec2>::iterator it = board->points.begin() ; it != board->points.end() ; ++it)
	{
		generateBoardsFromPoint(board, *it, board->next, player, decideMoveFor, isFirstDepth);
	}
	if (isFirstDepth == false)
	{
		sort(board->next.begin(), board->next.end(), sortPreHeurRev);
	}
}

/*
**	Generate all the boards for the given point into the given possibleBoards, from the curBoard.
**	We know the board's point is either BLACK or WHITE.
**	We check the adjacent points, and create boards for them.
*/

void	IA::generateBoardsFromPoint(Board *curBoard, t_vec2 point, vector<Board*> &possibleBoards, t_Color player, t_Color decideMoveFor, bool isFirstDepth)
{
	int		i = 8;
	Board*	newBoard;
	t_vec2	nextMove;

	nextMove.x = point.x - 1;
	nextMove.y = point.y + 1;
	while (i != -1)
	{
		if (BoardTools::IsPointIn(nextMove) && curBoard->map[nextMove.y][nextMove.x] == NONE)
		{
			if (GameRules::isMoveAuthorized(*curBoard, player, nextMove))
			{
				newBoard = new Board(*curBoard, curBoard, nextMove, player);
				if (BoardTools::IsInList(*newBoard, possibleBoards) == false)
				{
					GameRules::doCaptures(*newBoard, player, nextMove);
					if (isFirstDepth == false)
					{
						newBoard->preHeuristic += Heuristic::PreEvaluateBoard(*newBoard, player);
					}
					possibleBoards.push_back(newBoard);
				}
				else
				{
					delete newBoard;
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
