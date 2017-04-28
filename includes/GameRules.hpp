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


		static void			CheckVictory(t_GameDatas &GameDatas);

	private:

		// ----- Captures
		static bool			checkCaptures(Board &board, t_Color color, t_vec2 move);
		static bool			checkBlackMovingIntoCapture(Board &board,
								t_vec2 move, t_dir dir,
								std::string &line, std::string &backLine);
		static bool			checkWhiteMovingIntoCapture(Board &board,
								t_vec2 move, t_dir dir,
								std::string &line, std::string &backLine);
		static bool			IsBlackStoneCapturable(Board &board,
								t_vec2 stone, t_dir dir,
								std::string &line, std::string &backLine);
		static bool			IsWhiteStoneCapturable(Board &board,
								t_vec2 stone, t_dir dir,
								std::string &line, std::string &backLine);


		// ------ Forbidden move patterns.
		static bool			checkForbiddenPatterns(Board &board, t_Color color, t_vec2 move);

		static int			checkDoubleThreeBlackPatterns(Board &board,
								t_vec2 move, t_dir dir,
								std::string &line, std::string &backLine);
		static int			checkDoubleThreeWhitePatterns(Board &board,
								t_vec2 move, t_dir dir,
								std::string &line, std::string &backLine);

		// ------ Victory Checking.
		static void			checkVictoryPatterns(Board &board,
								t_vec2 curPoint, t_dir dir,
								std::string &line, std::vector<t_VictorySequence> &victorySequences);
		static t_Color		areVictorySequencesValid(Board &board,
								std::vector<t_VictorySequence> &victorySequences);
};

#endif
