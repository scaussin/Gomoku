#include "../includes/Gomoku.hpp"

extern double time_IsPointIn;
extern double time_isMoveAuthorized;
extern double time_newBoard;
extern double time_doCaptures;
extern double time_EvaluateBoard;
extern double time_IsInList;
extern double time_alphaBeta;

extern double time_generatePossibleBoards;
extern double time_generateBoardsFromPoint;

extern int n_newBoard;
extern int n_EvaluateBoard;


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
		std::cout << KGRN "AUTHORIZED move for "
					<< Tools::printColor(GameDatas.ActivePlayer) << KRESET << std::endl;

		UpdatePointValue(GameDatas, GameDatas.ActivePlayer, move);
		Goban.SetPointDisplay(move.x, move.y, GameDatas.ActivePlayer, SDLHandler);
		GameRules::doCaptures(GameDatas.Board, GameDatas.ActivePlayer, move);

		int boardVal = Heuristic::EvaluateBoard(GameDatas.Board, GameDatas.ActivePlayer);
		std::cout << "Current board value: " << boardVal << std::endl;
		GameDatas.TurnNumber += 1;
		Goban.UpdateBoard(GameDatas, SDLHandler);
	}
	else
	{
		std::cout << KMAG "UNAUTHORIZED move for "
					<< Tools::printColor(GameDatas.ActivePlayer) << KRESET << std::endl;
		return ;
	}
	GameRules::CheckVictory(GameDatas);
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

	if (GameDatas.SelectedGameMode == VS_IA)
	{
		std::cout << std::endl << KBLU "------ " KYEL <<  " Move " << GameDatas.TurnNumber << KBLU " ------" KRESET << std::endl;
		std::cout << std::endl << KYEL "IA - WHITE" KRESET << " plays move in " << KYEL << IaMove.x << "x " << IaMove.y << "y" KRESET << std::endl;

		cout << "n_newBoard: " << n_newBoard << endl;
		cout << "n_EvaluateBoard visited: " << n_EvaluateBoard << endl;
		cout << "time alphaBeta: " << time_alphaBeta << " ms" << endl;
		cout << "  time EvaluateBoard: " << time_EvaluateBoard<< " ms" << endl;
		cout << "  time generatePossibleBoards: " << time_generatePossibleBoards << " ms" << endl;
		cout << "    time time_generateBoardsFromPoint: " << time_generateBoardsFromPoint  << " ms" << endl;
		cout << "      time IsPointIn: " << time_IsPointIn<< " ms" << endl;
		cout << "      time isMoveAuthorized: " << time_isMoveAuthorized<< " ms" << endl;
		cout << "      time newBoard: " << time_newBoard<< " ms" << endl;
		cout << "      time doCaptures: " << time_doCaptures<< " ms" << endl;
		cout << "      time IsInList: " << time_IsInList << " ms" << endl;
		time_alphaBeta = 0;
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

		GameDatas.Board.setPoint(IaMove, WHITE);
		GameRules::doCaptures(GameDatas.Board, WHITE, IaMove);
		GameDatas.TurnNumber += 1;
	}
	else if (GameDatas.SelectedGameMode == VS_P2)
	{
		Goban.SetPointDisplay(IaMove.x, IaMove.y, SUGGESTION, SDLHandler);
		GameDatas.ActivePlayer = WHITE;
	}
	
	Goban.UpdateBoard(GameDatas, SDLHandler);
	GameRules::CheckVictory(GameDatas);
}

/*
**	Update point value on the Game's Board.
*/
void	GameController::UpdatePointValue(t_GameDatas &GameDatas, t_Color color, t_vec2 move)
{
	GameDatas.Board.map[move.y][move.x] = color;
}
