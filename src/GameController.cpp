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
	//if (GameDatas.ActivePlayer == BLACK)
	{
		std::cout << "user tries to play move in " << move.x
		<< "x " << move.y << "y" << std::endl;
		if (GameRules.IsMoveAuthorized(GameDatas.Board, GameDatas.ActivePlayer, move))
		{
			UpdatePointValue(GameDatas, GameDatas.ActivePlayer, move);
			Goban.SetPointDisplay(move.x, move.y, GameDatas.ActivePlayer, SDLHandler);
			GameRules.CheckCaptures(GameDatas.Board, move);
			Goban.UpdateBoard(GameDatas, SDLHandler);
		}
		else
		{
			std::cout << "Unauthorized move" << std::endl;
		}
		if (GameDatas.SelectedGameMode == VS_IA)
		{
			t_vec2	IaMove;
			// Start timer.
			IaMove = IA.DecideMove(GameDatas);
			//IaMove = IA.DecideRandomMove();
			// End timer.
			//GameRules.IsMoveAuthorized(IaMove);
			GameRules.CheckCaptures(GameDatas.Board, IaMove);
			Goban.UpdateBoard(GameDatas, SDLHandler);
		}
		else if (GameDatas.SelectedGameMode == VS_P2)
		{
			t_vec2	IaMoveSuggestion;

			IaMoveSuggestion = IA.DecideMove(GameDatas);
			Goban.SetPointDisplay(IaMoveSuggestion.x, IaMoveSuggestion.y, SUGGESTION, SDLHandler);
			//GameDatas.ActivePlayer = WHITE;
		}
		GameRules.CheckVictory(GameDatas);
	}
}

/*
**	Update point value on the Game's Board of char[][]
*/
void	GameController::UpdatePointValue(t_GameDatas &GameDatas, t_Color color, t_vec2 move)
{
	GameDatas.Board[move.y][move.x] = color;
}
