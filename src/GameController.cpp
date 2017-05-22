#include "../includes/Gomoku.hpp"

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
	// Printing turn count.
	GameDatas.BoardStates.push_back(GameDatas.Board);
	std::cout << std::endl << KBLU "------ " KYEL <<  "TURN " << GameDatas.TurnNumber
			<< " - Move " << GameDatas.MoveNumber << KBLU " ------" KRESET << std::endl;
	std::cout << std::endl << KYEL << Tools::printColor(GameDatas.ActivePlayer) << KRESET
			<< " tries to play move in " << KYEL << move.x << "x " << move.y << "y" KRESET << std::endl;
	// Erase last suggestion if not followed.
	if (GameDatas.Board.getPoint(GameDatas.LastSuggestion) == SUGGESTION)
	{
		GameDatas.Board.setPoint(GameDatas.LastSuggestion, NONE);
	}
	// ----- Processing user click.
	if (GameRules.isMoveAuthorized(GameDatas.Board, GameDatas.ActivePlayer, move))
	{
		std::cout << KGRN "AUTHORIZED move for "
					<< Tools::printColor(GameDatas.ActivePlayer) << KRESET << std::endl;

		// ----- Apply current user move.
		GameDatas.Board.setPoint(move, GameDatas.ActivePlayer);
		Goban.SetPointDisplay(move.x, move.y, GameDatas.ActivePlayer, SDLHandler);
		GameRules::doCaptures(GameDatas.Board, GameDatas.ActivePlayer, move);

		// int boardVal = Heuristic::EvaluateBoard(GameDatas.Board, GameDatas.ActivePlayer);
		// std::cout << "Current board value: " << boardVal << std::endl;
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

	if (GameDatas.SelectedGameMode == VS_IA)
	{
		GameDatas.ActivePlayer = WHITE;
	}
	else if (GameDatas.SelectedGameMode == VS_P2)
	{
		GameDatas.ActivePlayer = Tools::inverseColorPlayer(GameDatas.ActivePlayer);
	}

	// ----- Start IA decision timer.
	chrono_start = std::chrono::system_clock::now();

	IaMove = IA.decideMove(GameDatas); // the selected move is AUTHORIZED && CAPTURE APPLIED.

	// ----- End IA timer.
	chrono_end = std::chrono::system_clock::now();
	GameDatas.LastTurnIATime = std::chrono::duration_cast<std::chrono::milliseconds>
		(chrono_end-chrono_start).count();

	// ----- IA(white) plays its move.
	if (GameDatas.SelectedGameMode == VS_IA)
	{
		// Printing turn count.
		std::cout << std::endl << KBLU "------ " KYEL <<  "TURN " << GameDatas.TurnNumber
			<< " - Move " << GameDatas.MoveNumber << KBLU " ------" KRESET << std::endl;
		std::cout << std::endl << KYEL "IA - WHITE" KRESET << " plays move in "
			<< KYEL << IaMove.x << "x " << IaMove.y << "y" KRESET << std::endl;

		GameDatas.Board.setPoint(IaMove, WHITE);
		GameRules::doCaptures(GameDatas.Board, WHITE, IaMove);
		GameDatas.MoveNumber += 1;
		GameRules::CheckVictory(GameDatas);
		GameDatas.TurnNumber += 1;
		GameDatas.ActivePlayer = BLACK;
	}
	// ------ Two player mode: set the next player color.
	else if (GameDatas.SelectedGameMode == VS_P2)
	{
		if (GameDatas.ActivePlayer == WHITE) // if white just played.
			GameDatas.TurnNumber += 1;
		GameDatas.Board.setPoint(IaMove, SUGGESTION);
		// needed to clear the board.
		GameDatas.LastSuggestion.x = IaMove.x;
		GameDatas.LastSuggestion.y = IaMove.y;
	}
	Goban.UpdateBoard(GameDatas, SDLHandler);
}
