#ifndef GAMERULES_HPP
# define GAMERULES_HPP

#include "Gomoku.hpp"

class GameRules
{
	public:
		GameRules();
		~GameRules();

		static bool			isMoveAuthorized(Board &board, t_Color color, t_vec2 move);
		static void			doCaptures(Board &board, t_Color color, t_vec2 move);


		static void			CheckVictory(t_GameDatas &GameDatas);

	private:

		// ----- Captures
		static void			applyCapture(Board &board, t_Color color,
								int stone1_x, int stone1_y, int stone2_x, int stone2_y);
		static bool			checkCaptures(Board &board, t_Color color, t_vec2 move);
		static bool			checkBlackMovingIntoCapture(Board &board,
								t_vec2 move, t_dir dir,
								char *line, char *backLine);
		static bool			checkWhiteMovingIntoCapture(Board &board,
								t_vec2 move, t_dir dir,
								char *line, char *backLine);
		static bool			IsBlackStoneCapturable(Board &board,
								t_vec2 stone, t_dir dir,
								char *line, char *backLine);
		static bool			IsWhiteStoneCapturable(Board &board,
								t_vec2 stone, t_dir dir,
								char *line, char *backLine);


		// ------ Forbidden move patterns.
		static bool			checkForbiddenPatterns(Board &board, t_Color color, t_vec2 move);

		static int			checkDoubleThreePatterns(Board &board,
								t_vec2 move, t_dir dir,
								char *line, char *backLine);

		// ------ Victory Checking.
		static void			checkVictoryPatterns(Board &board,
								t_vec2 curPoint, t_dir dir,
								char *line, std::vector<t_VictorySequence> &victorySequences);
		static t_Color		areVictorySequencesValid(t_GameDatas &GameDatas,
								Board &board,
								std::vector<t_VictorySequence> &victorySequences);
		static bool			GetCaptureMove(Board &board, t_vec2 curPoint, t_dir dir,
										char *line, char *backLine,
										t_vec2 &retMove);
};

#endif
