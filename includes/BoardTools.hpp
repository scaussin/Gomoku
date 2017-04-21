#ifndef BOARDTOOLS_HPP
# define BOARDTOOLS_HPP

class BoardTools
{
	public:
		static t_Color		GetPointValue(Board &board, t_vec2 coord);
		static t_Color		GetPointValue(Board &board, int x, int y);
		static void			SetPointValue(Board &board, t_vec2 coord, t_Color newVal);
		static void			SetPointValue(Board &board, int x, int y, t_Color newVal);

		static bool			IsPointIn(const t_vec2 point);

		static void			DisplayBoardChars(Board &board);

		static bool			IsIdentical(const Board &board_a, const Board &board_b);
		static bool			IsInList(const Board &board, std::vector<Board> &boardList);
		
};

#endif
