#ifndef IA_HPP
# define IA_HPP

#include "Gomoku.hpp"

class IA
{
	public:
		IA();
		~IA();

		//std::vector<Board>	stateExpanding;

		t_vec2			decideMove(t_GameDatas &gameDatas);

		void			generatePossibleBoards(Board *board, t_Color player,
							t_Color decideMoveFor);
		void			generateBoardsFromPoint(Board *curBoard, t_vec2 point,
							vector<Board*> &possibleBoards, t_Color player, t_Color decideMoveFor);
		BoardMove		*alphaBeta(Board *board, BoardMove *curMove, int deep, int alpha, int beta, t_Color player,
							t_Color decideMoveFor);

		void			generatePossibleBoardsNoCopy(Board *curBoard, BoardMove *curMove,
							t_Color player, t_Color decideMoveFor);
		void			generateBoardsFromPointNoCopy(Board *curBoard, BoardMove *curMove,
							t_vec2 point, std::vector<BoardMove*> &possibleMoves,
							t_Color player, t_Color decideMoveFor);
		void			UndoMove(Board &board, BoardMove &curMove, t_Color decideMoveFor);
};

#endif
