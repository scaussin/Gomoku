#ifndef GAMERULES_HPP
# define GAMERULES_HPP

#include "Gomoku.hpp"

class GameRules
{
	public:
		GameRules();
		~GameRules();

		static bool			IsMoveAuthorized(Board &Board, t_Color color, t_vec2 move);
		static void			doCaptures(Board &board, t_Color color, t_vec2 move);
		void				CheckVictory(t_GameDatas &GameDatas);

	private:
		static bool			HasDoubleThree(Board &Board, t_Color color, t_vec2 move);
		
};


#endif