#ifndef GAMERULES_HPP
# define GAMERULES_HPP

#include "Gomoku.hpp"

class GameRules
{
	public:
		GameRules();
		~GameRules();

		static bool			IsMoveAuthorized(Board &board, t_Color color, t_vec2 move);
		void				CheckCaptures(Board &board, t_vec2 move);

		void				CheckVictory(t_GameDatas &GameDatas);

	private:
		static bool			hasDoubleThree(Board &board, t_Color color, t_vec2 move);
		static int			checkDoubleThreeBlackPatterns(Board &board, t_vec2 move, t_dir dir);
		static int			checkDoubleThreeWhitePatterns(Board &board, t_vec2 move, t_dir dir);
};

#endif