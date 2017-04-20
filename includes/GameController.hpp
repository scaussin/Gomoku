#ifndef GAMECONTROLLER
# define GAMECONTROLLER

# include "Gomoku.hpp"

class GameController
{
	public:
		GameController();
		~GameController();

		IA					IA;
		GameRules			GameRules;


		void	Play(t_GameDatas &GameDatas, GobanController &Goban, SDLHandler &SDLHandler, t_vec2 move);


		void	UpdatePointValue(t_GameDatas &GameDatas, t_Color color, t_vec2 move);
};

#endif
