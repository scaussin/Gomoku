#ifndef TOOLS_HPP
# define TOOLS_HPP

# include "Gomoku.hpp"

class Tools
{
	public:
		static bool				RectCollision(int x, int y, SDL_Rect Rect);
		static int				Clamp(int n, int lower, int upper);
		static std::string		GetPointsLine(Board &board, t_vec2 point, t_dir dir, int nb_points);
		static void				SetMoveModifiers(int &mod_x, int &mod_y, t_dir dir);
		static t_Color			GetNextPoint(Board &board, t_vec2 point, t_dir dir);
		static t_dir			GetOppositeDir(t_dir dir);
		static t_Color			inverseColorPlayer(t_Color player);
		static void				printError(string file, int line, string sfunction, string msg, int errorLevel);
		static void				GetPointsLine(char *line, Board &board, t_vec2 &point,
									t_dir dir, int nb_points);
		static void				GetPatternPointsLine(char *line, Board &board, t_vec2 &point,
									t_dir dir, int nb_points, t_Color color);
		static void				GetDualPatternPointsLine(char *line, char *backLine, Board &board, t_vec2 &point,
									t_dir dir, int nb_points, t_Color color);
		static void				ReversePatternColors(char *line, char *backLine, int nb_points);
		static std::string		printColor(t_Color color);
};

#endif
