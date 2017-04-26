#ifndef IA_HPP
# define IA_HPP

#include "Gomoku.hpp"

class IA
{
	public:
		IA();
		~IA();

		std::vector<Board>	StateExpanding;

		t_vec2		DecideMove(t_GameDatas &GameDatas);

		void		GeneratePossibleBoards(t_GameDatas &GameDatas, Board &curBoard);
		void		GenerateBoardsForPoint(Board &curBoard, t_vec2 point,
											std::vector<Board> &boardList);
};

#endif
