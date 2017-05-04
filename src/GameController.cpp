#include "../includes/Gomoku.hpp"

GameController::GameController()
{

}

GameController::~GameController()
{

}

void	GameController::ResetGame(t_GameDatas &GameDatas)
{
	GameDatas.TurnNumber = 0;
	GameDatas.BlackCaptures = 0;
	GameDatas.Board.BlackCaptures = 0;
	GameDatas.WhiteCaptures = 0;
	GameDatas.Board.WhiteCaptures = 0;
	GameDatas.IsGameOver = false;
	GameDatas.WinnerColor = NONE;

	GameDatas.BlackInCheck = false;
	GameDatas.WhiteInCheck = false;

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
	std::cout << std::endl << KBLU "------ " KYEL <<  " Move " << GameDatas.TurnNumber << KBLU " ------" KRESET << std::endl;
	std::cout << std::endl << KYEL << Tools::printColor(GameDatas.ActivePlayer) << KRESET << " tries to play move in " << KYEL << move.x << "x " << move.y << "y" KRESET << std::endl;
	if (GameRules.isMoveAuthorized(GameDatas.Board, GameDatas.ActivePlayer, move))
	{
		std::cout << KMAG "UNAUTHORIZED move for "
					<< Tools::printColor(GameDatas.ActivePlayer) << std::endl;

		UpdatePointValue(GameDatas, GameDatas.ActivePlayer, move);
		Goban.SetPointDisplay(move.x, move.y, GameDatas.ActivePlayer, SDLHandler);
		GameRules::doCaptures(GameDatas.Board, GameDatas.ActivePlayer, move);

		int boardVal = Heuristic::EvaluateBoard(GameDatas.Board, GameDatas.ActivePlayer);
		std::cout << "Current board value: " << boardVal << std::endl;
		GameDatas.TurnNumber += 1;
	}
	else
	{
		std::cout << KMAG "UNAUTHORIZED move for "
					<< Tools::printColor(GameDatas.ActivePlayer) << std::endl;
		return ;
	}
	// --------------------------------------------------------------------	//
	//	Response side -> IA or player2										//
	//																		//
	// --------------------------------------------------------------------	//
	t_vec2			IaMove;

	// Start IA decision timer.
	chrono_start = std::chrono::system_clock::now();

	IaMove = IA.decideMove(GameDatas); // the selected move is AUTHORIZED && CAPTURE APPLIED.

	// End timer.
	chrono_end = std::chrono::system_clock::now();
	GameDatas.LastTurnIATime = std::chrono::duration_cast<std::chrono::milliseconds>
		(chrono_end-chrono_start).count();

	if (GameDatas.SelectedGameMode == VS_IA)
	{
		std::cout << std::endl << KBLU "------ " KYEL <<  " Move " << GameDatas.TurnNumber << KBLU " ------" KRESET << std::endl;
		std::cout << std::endl << KYEL "IA - WHITE" KRESET << " tries to play move in " << KYEL << move.x << "x " << move.y << "y" KRESET << std::endl;
		GameDatas.Board.setPoint(IaMove, WHITE);
		GameRules::doCaptures(GameDatas.Board,GameDatas.ActivePlayer, IaMove);
		GameDatas.TurnNumber += 1;
	}
	else if (GameDatas.SelectedGameMode == VS_P2)
	{
		Goban.SetPointDisplay(IaMove.x, IaMove.y, SUGGESTION, SDLHandler);
		GameDatas.ActivePlayer = WHITE;
	}
	GameRules::CheckVictory(GameDatas);
	Goban.UpdateBoard(GameDatas, SDLHandler);
}

/*
**	Update point value on the Game's Board.
*/
void	GameController::UpdatePointValue(t_GameDatas &GameDatas, t_Color color, t_vec2 move)
{
	GameDatas.Board.map[move.y][move.x] = color;
}
