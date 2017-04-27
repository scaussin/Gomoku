#ifndef GAMERULES_HPP
# define GAMERULES_HPP

#include "Gomoku.hpp"

class GameRules
{
	public:
		GameRules();
		~GameRules();

		static bool			IsMoveAuthorized(Board &board, t_Color color, t_vec2 move);
		static void			doCaptures(Board &board, t_Color color, t_vec2 move);


		void				CheckVictory(t_GameDatas &GameDatas);

	private:
		static bool			checkCaptures(Board &board, t_Color color, t_vec2 move);
		
		static bool			checkForbiddenPatterns(Board &board, t_Color color, t_vec2 move);

		static int			checkDoubleThreeBlackPatterns(Board &board,
								t_vec2 move, t_dir dir,
								std::string &line, std::string &backLine);
		static int			checkDoubleThreeWhitePatterns(Board &board,
								t_vec2 move, t_dir dir,
								std::string &line, std::string &backLine);

		static bool			checkBlackMovingIntoCapture(Board &board,
								t_vec2 move, t_dir dir,
								std::string &line, std::string &backLine);
		static bool			checkWhiteMovingIntoCapture(Board &board,
								t_vec2 move, t_dir dir,
								std::string &line, std::string &backLine);
};


#endif