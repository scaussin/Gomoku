#include "../includes/Gomoku.hpp"

double time_IsPointIn = 0;
double time_isMoveAuthorized = 0;
double time_newBoard = 0;
double time_delBoard = 0;
double time_doCaptures = 0;
double time_EvaluateBoard = 0;

double time_IsInList = 0;
double time_alphaBeta = 0;
double time_generatePossibleBoards = 0;
double time_generateBoardsFromPoint = 0;

int n_newBoard = 0;
int n_EvaluateBoard = 0;


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

t_vec2		IA::decideMove(t_GameDatas &gameDatas)
{
	t_vec2		decidedMove;
	Board		*finalMove = NULL;
	t_Color		enemyColor;

	decidedMove.x = 0;
	decidedMove.y = 0;
	enemyColor = Tools::inverseColorPlayer(gameDatas.ActivePlayer);

	double start_alphaBeta = clock(); //time
	generatePossibleBoards(&gameDatas.Board, gameDatas.ActivePlayer, enemyColor);
	for (vector<Board *>::iterator it = gameDatas.Board.next.begin() ; it != gameDatas.Board.next.end() ; ++it)
	{
		(*it)->heuristic += Heuristic::EvaluateBoard(**it, enemyColor);
		if ((*it)->isVictory)
		{
			finalMove = *it;
			break;
		}
	}
	if (finalMove == NULL)
	{
		sort(gameDatas.Board.next.begin(), gameDatas.Board.next.end(), sortNextMoveRev);
		finalMove = alphaBeta(&gameDatas.Board, gameDatas.IA_Depth, ALPHA, BETA, gameDatas.ActivePlayer, enemyColor);
	}
	time_alphaBeta += (clock() - start_alphaBeta) / double(CLOCKS_PER_SEC) * 1000; //time

	BoardTools::printParents(finalMove);
	decidedMove = BoardTools::getFistMove(finalMove);
	for (vector<Board *>::iterator it = gameDatas.Board.next.begin() ; it != gameDatas.Board.next.end() ; ++it)
	{
		delete *it;
	}
	gameDatas.Board.next.clear();
	return (decidedMove);
}

bool sortNextMove (Board* a, Board* b)
{ 
	return (a->heuristic < b->heuristic);
}

bool sortPreHeur (Board* a, Board* b)
{ 
	return (a->preHeuristic < b->preHeuristic);
}
bool sortPreHeurRev (Board* a, Board* b)
{ 
	return (a->preHeuristic > b->preHeuristic);
}

Board	*IA::alphaBeta(Board *board, int deep, int alpha, int beta, t_Color player, t_Color decideMoveFor)
{
	Board	*valBoard = NULL;
	Board	*bestBoard = NULL;

	board->heuristic += Heuristic::EvaluateBoard(*board, decideMoveFor);
	n_EvaluateBoard++; //time

	// /**/time_EvaluateBoard += (clock() - start_EvaluateBoard) / double(CLOCKS_PER_SEC) * 1000;
	if (deep == 0 || board->isVictory)
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
			generatePossibleBoards(board, player, decideMoveFor);
		for (vector<Board *>::iterator it = board->next.begin() ; it != board->next.end() ; ++it)
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

Board *IA::maxBoard(Board *a, Board *b)
{
	return ((a->heuristic > b->heuristic)? a : b);
}

Board *IA::minBoard(Board *a, Board *b)
{
	return ((a->heuristic < b->heuristic)? a : b);
}

Board	*IA::alphaBeta2(Board *board, int depth, int alpha, int beta, t_Color player, t_Color decideMoveFor)
{
	Board *v = NULL;

	board->heuristic += Heuristic::EvaluateBoard(*board, decideMoveFor);
	n_EvaluateBoard++; //time

	if (depth == 0 || board->isVictory)
		return (board);
	if (board->next.size() == 0)
		generatePossibleBoards(board, player, decideMoveFor);
	if (player == decideMoveFor) //max
	{
		v = new Board();
		v->heuristic = ALPHA;
		for (vector<Board *>::iterator it = board->next.begin() ; it != board->next.end() ; ++it)
		{
			v = maxBoard(v, alphaBeta2(*it, depth - 1, alpha, beta, Tools::inverseColorPlayer(player), decideMoveFor));
			alpha = max(alpha, v->heuristic);
			if (beta <= alpha)
				break ;
		}
		return v;
	}
	else //min
	{
		v = new Board();
		v->heuristic = BETA;
		for (vector<Board *>::iterator it = board->next.begin() ; it != board->next.end() ; ++it)
		{
			v = minBoard(v, alphaBeta2(*it, depth - 1, alpha, beta, Tools::inverseColorPlayer(player), decideMoveFor));
			beta = min(beta, v->heuristic);
			if (beta <= alpha)
				break ;
		}
		return v;
	}

}

void	IA::generatePossibleBoards(Board *board, t_Color player, t_Color decideMoveFor)
{
	int start_generatePossibleBoards = clock(); //time

	for (vector<t_vec2>::iterator it = board->points.begin() ; it != board->points.end() ; ++it)
	{
		generateBoardsFromPoint(board, *it, board->next, player, decideMoveFor);
	}
	sort(board->next.begin(), board->next.end(), sortPreHeurRev);
	time_generatePossibleBoards += (clock() - start_generatePossibleBoards) / double(CLOCKS_PER_SEC) * 1000; //time
}


/*
**	Generate all the boards for the given point into the given possibleBoards, from the curBoard.
**	We know the board's point is either BLACK or WHITE.
**	We check the adjacent points, and create boards for them.
*/

void	IA::generateBoardsFromPoint(Board *curBoard, t_vec2 point, vector<Board*> &possibleBoards, t_Color player, t_Color decideMoveFor)
{
	int start_generateBoardsFromPoint = clock(); //time
	int		i = 8;
	Board*	newBoard;
	t_vec2	nextMove;
	bool b_isPointIn; //time
	bool b_isMoveAuthorized; //time
	bool b_IsInList; //time

	nextMove.x = point.x - 1;
	nextMove.y = point.y + 1;
	while (i != -1)
	{
		int start_IsPointIn = clock(); //time
		b_isPointIn = BoardTools::IsPointIn(nextMove);
		time_IsPointIn += (clock() - start_IsPointIn) / double(CLOCKS_PER_SEC) * 1000; //time

		if (b_isPointIn && curBoard->map[nextMove.y][nextMove.x] == NONE)
		{
			int start_isMoveAuthorized = clock(); //time
			b_isMoveAuthorized = GameRules::isMoveAuthorized(*curBoard, player, nextMove);
			time_isMoveAuthorized += (clock() - start_isMoveAuthorized) / double(CLOCKS_PER_SEC) * 1000; //time

			if (b_isMoveAuthorized)
			{
				int start_newBoard = clock(); //time
				newBoard = new Board(*curBoard, curBoard, nextMove, player);
				time_newBoard += (clock() - start_newBoard) / double(CLOCKS_PER_SEC) * 1000; //time
				
				int start_IsInList = clock(); //time
				b_IsInList = BoardTools::IsInList(*newBoard, possibleBoards);
				time_IsInList += (clock() - start_IsInList) / double(CLOCKS_PER_SEC) * 1000; //time

				if (b_IsInList == false)
				{
					/**/int start_doCapture = clock();
					GameRules::doCaptures(*newBoard, player, nextMove);
					newBoard->preHeuristic += Heuristic::PreEvaluateBoard(*newBoard, player);
					possibleBoards.push_back(newBoard);
					n_newBoard++;
					time_doCaptures += (clock() - start_doCapture) / double(CLOCKS_PER_SEC) * 1000; //time
				}
				else
				{
					int start_delBoard = clock(); //time
					delete newBoard;
					time_delBoard += (clock() - start_delBoard) / double(CLOCKS_PER_SEC) * 1000; //time
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
	time_generateBoardsFromPoint += (clock() - start_generateBoardsFromPoint) / double(CLOCKS_PER_SEC) * 1000; //time
}
