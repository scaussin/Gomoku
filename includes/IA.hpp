#ifndef IA_HPP
# define IA_HPP

#include "Gomoku.hpp"

class IA
{
	public:
		IA();
		~IA();

		t_vec2		DecideMove(t_GameDatas &GameDatas);
};

#endif
