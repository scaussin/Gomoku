#ifndef BOARDTOOLS_HPP
# define BOARDTOOLS_HPP

class BoardTools
{
	public:
		static t_Color		GetPointValue(char *Board[][19], t_vec2 coord);
		static t_Color		GetPointValue(char *Board[][19], int x, int y);
};

#endif
