#ifndef BOARDTOOLS_HPP
# define BOARDTOOLS_HPP

class BoardTools
{
	public:
		static t_Color		GetPointValue(Board &Board, t_vec2 coord);
		static t_Color		GetPointValue(Board &Board, int x, int y);

		static	void		DisplayBoardChars(Board &Board);
};

#endif
