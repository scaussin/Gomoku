#include "../includes/Gomoku.hpp"

extern double time_IsPointIn;
extern double time_isMoveAuthorized;
extern double time_newBoard;
extern double time_delBoard;
extern double time_doCaptures;
extern double time_EvaluateBoard;
extern double time_IsInList;
extern double time_alphaBeta;
extern double time_generatePossibleBoards;
extern double time_generateBoardsFromPoint;

extern double time_victorySearchPatterns;
extern double time_simpleSearchPatterns;
extern double time_threatSpaceSearchPatterns;
extern double time_captureSearchPatterns;
extern double time_GetPatternPointsLine;



extern int n_newBoard;
extern int n_EvaluateBoard;


GameController::GameController()
{

}

GameController::~GameController()
{

}

void	GameController::RevertLastMove(t_GameDatas &GameDatas,
			SDLHandler &SDLHandler, GobanController &Goban)
{
	if (GameDatas.IsGameOver == false
		&& GameDatas.BoardStates.size() != 0)
	{
		GameDatas.Board = GameDatas.BoardStates.back();
		Goban.UpdateBoard(GameDatas, SDLHandler);
		GameDatas.BoardStates.pop_back();
		GameDatas.BlackInCheck = false;
		GameDatas.WhiteInCheck = false;
		if (GameDatas.SelectedGameMode == VS_IA)
		{
			if (GameDatas.TurnNumber > 0)
				GameDatas.TurnNumber -= 1;
			if (GameDatas.MoveNumber > 0)
				GameDatas.MoveNumber -= 2;
		}
		else if (GameDatas.SelectedGameMode == VS_P2)
		{
			// erase last suggestion if not followed.
			if (GameDatas.Board.getPoint(GameDatas.LastSuggestion) == SUGGESTION)
			{
				GameDatas.Board.setPoint(GameDatas.LastSuggestion, NONE);
				Goban.UpdateBoard(GameDatas, SDLHandler);
			}
			// Set turn counter
			// white plays = turn + 1;
			// so white reverse = turn - 1;
			// white reverse means actual player is black.
			if (GameDatas.TurnNumber > 0 && GameDatas.ActivePlayer == BLACK)
				GameDatas.TurnNumber -= 1;
			if (GameDatas.MoveNumber > 0)
				GameDatas.MoveNumber -= 1;

			// set active turn player.
			if (GameDatas.ActivePlayer == WHITE)
			{
				GameDatas.ActivePlayer = BLACK;
			}
			else if (GameDatas.ActivePlayer == BLACK)
			{
				GameDatas.ActivePlayer = WHITE;
			}
		}
	}
	else
	{
		std::cout << "No board state to revert to!" << std::endl;
	}
}

void	GameController::ResetGame(t_GameDatas &GameDatas)
{
	GameDatas.TurnNumber = 0;
	GameDatas.MoveNumber = 0;
	GameDatas.Board.BlackCaptures = 0;
	GameDatas.Board.WhiteCaptures = 0;
	GameDatas.Board.isVictory = false;
	GameDatas.IsGameOver = false;
	GameDatas.WinnerColor = NONE;
	GameDatas.ActivePlayer = BLACK;
	GameDatas.LastTurnIATime = 0;
	GameDatas.BlackInCheck = false;
	GameDatas.WhiteInCheck = false;
	GameDatas.BoardStates.clear();

	// clean current board values.
	for (int y = 0; y < 19; ++y)
	{
		for (int x = 0; x < 19; ++x)
		{
			GameDatas.Board.setPoint(y, x, NONE);
		}
	}
}

void	GameController::Play(t_GameDatas &GameDatas, GobanController &Goban,
							SDLHandler &SDLHandler, t_vec2 move)
{
	// --------------------------------------------------------------------	//
	//	Input reception side												//
	//																		//
	// --------------------------------------------------------------------	//
	GameDatas.BoardStates.push_back(GameDatas.Board);
	std::cout << std::endl << KBLU "------ " KYEL <<  "TURN " << GameDatas.TurnNumber << " - Move " << GameDatas.MoveNumber << KBLU " ------" KRESET << std::endl;
	std::cout << std::endl << KYEL << Tools::printColor(GameDatas.ActivePlayer) << KRESET << " tries to play move in " << KYEL << move.x << "x " << move.y << "y" KRESET << std::endl;
	// erase last suggestion if not followed.
	if (GameDatas.Board.getPoint(GameDatas.LastSuggestion) == SUGGESTION)
	{
		GameDatas.Board.setPoint(GameDatas.LastSuggestion, NONE);
	}
	if (GameRules.isMoveAuthorized(GameDatas.Board, GameDatas.ActivePlayer, move))
	{
		std::cout << KGRN "AUTHORIZED move for "
					<< Tools::printColor(GameDatas.ActivePlayer) << KRESET << std::endl;

		UpdatePointValue(GameDatas, GameDatas.ActivePlayer, move);
		Goban.SetPointDisplay(move.x, move.y, GameDatas.ActivePlayer, SDLHandler);
		GameRules::doCaptures(GameDatas.Board, GameDatas.ActivePlayer, move);

		int boardVal = Heuristic::EvaluateBoard(GameDatas.Board, GameDatas.ActivePlayer);
		std::cout << "Current board value: " << boardVal << std::endl;
		GameDatas.MoveNumber += 1;
		Goban.UpdateBoard(GameDatas, SDLHandler);
		GameRules::CheckVictory(GameDatas);
	}
	else
	{
		std::cout << KMAG "UNAUTHORIZED move for "
					<< Tools::printColor(GameDatas.ActivePlayer) << KRESET << std::endl;
		return ;
	}
	
	if (GameDatas.IsGameOver)
		return ;
	// --------------------------------------------------------------------	//
	//	Response side -> IA or player2										//
	//																		//
	// --------------------------------------------------------------------	//
	t_vec2			IaMove;

	// Start IA decision timer.
	chrono_start = std::chrono::system_clock::now();

	IaMove = IA.decideMove(GameDatas); // the selected move is AUTHORIZED && CAPTURE APPLIED.

	// IaMove.x = 0;
	// IaMove.y = 0;

	// End timer.
	chrono_end = std::chrono::system_clock::now();
	GameDatas.LastTurnIATime = std::chrono::duration_cast<std::chrono::milliseconds>
		(chrono_end-chrono_start).count();

	// ----- Time debug printing
		cout << "n_newBoard: " << n_newBoard << endl;
		cout << "n_EvaluateBoard visited: " << n_EvaluateBoard << endl;
		cout << "time alphaBeta: " << time_alphaBeta << " ms" << endl;
		cout << "    time EvaluateBoard: " << time_EvaluateBoard<< " ms" << " (" << (time_EvaluateBoard / time_alphaBeta)*100<< "%) " << endl;
		cout << "        time GetPatternPointsLine: " << time_GetPatternPointsLine << " ms"<< " (" << (time_GetPatternPointsLine / time_EvaluateBoard)*100<< "%)" << endl;
		cout << "        time victorySearchPatterns: " << time_victorySearchPatterns << " ms"<< " (" << (time_victorySearchPatterns / time_EvaluateBoard)*100<< "%)" << endl;
		cout << "        time simpleSearchPatterns: " << time_simpleSearchPatterns << " ms"<< " (" << (time_simpleSearchPatterns / time_EvaluateBoard)*100<< "%)" << endl;
		cout << "        time threatSpaceSearchPatterns: " << time_threatSpaceSearchPatterns << " ms"<< " (" << (time_threatSpaceSearchPatterns / time_EvaluateBoard)*100<< "%)" << endl;
		cout << "        time captureSearchPatterns: " << time_captureSearchPatterns << " ms"<< " (" << (time_captureSearchPatterns / time_EvaluateBoard)*100<< "%)" << endl;
		cout << "    time generatePossibleBoards: " << time_generatePossibleBoards << " ms" << " (" << (time_generatePossibleBoards / time_alphaBeta)*100<< "%) " << endl;
		cout << "        time generateBoardsFromPoint: " << time_generateBoardsFromPoint<< " (" << (time_generateBoardsFromPoint / time_generatePossibleBoards)*100<< "%) " << " rest: " <<time_generateBoardsFromPoint - (time_IsPointIn+time_isMoveAuthorized+time_newBoard+time_IsInList+time_doCaptures+time_delBoard)  << " ms" << endl;
		cout << "            time IsPointIn: " << time_IsPointIn<< " ms" << " (" << (time_IsPointIn / time_generateBoardsFromPoint)*100<< "%)" << endl;
		cout << "            time isMoveAuthorized: " << time_isMoveAuthorized << " ms"<< " (" << (time_isMoveAuthorized / time_generateBoardsFromPoint)*100<< "%)" << endl;
		cout << "            time newBoard: " << time_newBoard << " ms"<< " (" << (time_newBoard / time_generateBoardsFromPoint)*100<< "%)" << endl;
		cout << "            time IsInList: " << time_IsInList << " ms"<< " (" << (time_IsInList / time_generateBoardsFromPoint)*100<< "%)" << endl;
		cout << "            time doCaptures & push_back(): " << time_doCaptures<< " ms"<< " (" << (time_doCaptures / time_generateBoardsFromPoint)*100<< "%)" << endl;
		cout << "            time delBoard: " << time_delBoard << " ms"<< " (" << (time_delBoard / time_generateBoardsFromPoint)*100<< "%)" << endl;
		time_alphaBeta = 0;
		time_delBoard = 0;
		time_generatePossibleBoards = 0;
		time_generateBoardsFromPoint = 0;
		time_IsInList = 0;
		time_IsPointIn = 0;
		time_isMoveAuthorized = 0;
		time_newBoard = 0;
		time_doCaptures = 0;
		time_EvaluateBoard = 0;
		n_newBoard = 0;
		n_EvaluateBoard = 0;

		time_victorySearchPatterns = 0;
		time_simpleSearchPatterns = 0;
		time_threatSpaceSearchPatterns = 0;
		time_captureSearchPatterns = 0;
		time_GetPatternPointsLine = 0;
	// ----- Time debug printing ----- END

	if (GameDatas.SelectedGameMode == VS_IA)
	{
		std::cout << std::endl << KBLU "------ " KYEL <<  "TURN " << GameDatas.TurnNumber << " - Move " << GameDatas.MoveNumber << KBLU " ------" KRESET << std::endl;
		std::cout << std::endl << KYEL "IA - WHITE" KRESET << " plays move in " << KYEL << IaMove.x << "x " << IaMove.y << "y" KRESET << std::endl;
		GameDatas.Board.setPoint(IaMove, WHITE);
		GameRules::doCaptures(GameDatas.Board, WHITE, IaMove);
		GameDatas.MoveNumber += 1;
		GameRules::CheckVictory(GameDatas);
		GameDatas.TurnNumber += 1;
	}
	else if (GameDatas.SelectedGameMode == VS_P2)
	{
		if (GameDatas.ActivePlayer == WHITE) // if white just played.
			GameDatas.TurnNumber += 1;
		//Goban.SetPointDisplay(IaMove.x, IaMove.y, BLACK, SDLHandler);
		GameDatas.Board.setPoint(IaMove, SUGGESTION);
		GameDatas.ActivePlayer = Tools::inverseColorPlayer(GameDatas.ActivePlayer);
		// needed to clear the board.
		GameDatas.LastSuggestion.x = IaMove.x;
		GameDatas.LastSuggestion.y = IaMove.y;

	}
	Goban.UpdateBoard(GameDatas, SDLHandler);
}

/*
**	Update point value on the Game's Board.
*/
void	GameController::UpdatePointValue(t_GameDatas &GameDatas, t_Color color, t_vec2 move)
{
	GameDatas.Board.setPoint(move, color);
}
