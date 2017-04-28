#include "../includes/Gomoku.hpp"

GameController::GameController()
{

}

GameController::~GameController()
{

}

void	GameController::Play(t_GameDatas &GameDatas, GobanController &Goban,
							SDLHandler &SDLHandler, t_vec2 move)
{
	//if (GameDatas.ActivePlayer == BLACK) // debug mode for now.
	{
		std::cout << std::endl << KBLU "------ " KYEL <<  " Move "
			<< GameDatas.TurnNumber << KBLU " ------" KRESET
			<< std::endl;
		// debug playing printing;
		if (GameDatas.ActivePlayer == BLACK)
			std::cout << std::endl << KYEL "BLACK" KRESET;
		else
			std::cout << std::endl << KYEL "WHITE" KRESET;
		std::cout << " tries to play move in " << KYEL << move.x
		<< "x " << move.y << "y" KRESET << std::endl;
		if (GameRules.IsMoveAuthorized(GameDatas.Board, GameDatas.ActivePlayer, move))
		{
			std::cout << KGRN "AUTHORIZED move for ";
			if (GameDatas.ActivePlayer == BLACK)
				std::cout << "BLACK" KRESET << std::endl;
			else
				std::cout << "WHITE" KRESET << std::endl;

			UpdatePointValue(GameDatas, GameDatas.ActivePlayer, move);
			Goban.SetPointDisplay(move.x, move.y, GameDatas.ActivePlayer, SDLHandler);
			GameRules::doCaptures(GameDatas.Board, GameDatas.ActivePlayer, move);
			Goban.UpdateBoard(GameDatas, SDLHandler);
			std::cout << KYEL "Evaluating current board" KRESET << std::endl
				<< "Patterns found during evaluation: " << std::endl;
			int boardVal = Heuristic::EvaluateBoard(GameDatas.Board, GameDatas.ActivePlayer);
			std::cout << "Current board value: " << boardVal << std::endl;
			GameDatas.TurnNumber += 1;
		}
		else
		{
			// more debug playing print
			std::cout << KMAG "UNAUTHORIZED move for ";
			if (GameDatas.ActivePlayer == BLACK)
				std::cout << "BLACK" KRESET << std::endl;
			else
				std::cout << "WHITE" KRESET << std::endl;
		}
		// handle IA or player just after the user clicked on a stone.
		if (GameDatas.SelectedGameMode == VS_IA)
		{
			t_vec2	IaMove;
			// Start timer.
			IaMove = IA.DecideMove(GameDatas);
			// End timer.
			//GameRules.IsMoveAuthorized(IaMove);
			GameRules::doCaptures(GameDatas.Board,GameDatas.ActivePlayer, IaMove);
			Goban.UpdateBoard(GameDatas, SDLHandler);
		}
		else if (GameDatas.SelectedGameMode == VS_P2)
		{
			t_vec2	IaMoveSuggestion;

			IaMoveSuggestion = IA.DecideMove(GameDatas);
			Goban.SetPointDisplay(IaMoveSuggestion.x, IaMoveSuggestion.y, SUGGESTION, SDLHandler);
			//GameDatas.ActivePlayer = WHITE;
		}
		GameRules::CheckVictory(GameDatas);
	}
}

/*
**	Update point value on the Game's Board.
*/
void	GameController::UpdatePointValue(t_GameDatas &GameDatas, t_Color color, t_vec2 move)
{
	GameDatas.Board.Map[move.y][move.x] = color;
}
