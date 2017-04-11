/*
**	Global Gomoku hpp
*/

#ifndef GOMOKU_HPP
# define GOMOKU_HPP

// General includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <iterator>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <sstream>
# include <fcntl.h>
# include <list>
# include <vector>
# include <string>
# include <queue> 
# include <regex>
# include <random>
# include <algorithm>
# include <math.h>

# include "../Frameworks/SDL2.framework/Headers/SDL.h"
# include "../Frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"

// color in text;
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define KRESET "\x1B[0m"

/*
**	SDL engine defines
*/

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define SCREEN_RATIO_X 16
# define SCREEN_RATIO_Y 9
# define SCREEN_RATIO 1.7

/*
**	Game defines
*/

typedef enum 		e_GameStage
{
	MAIN_MENU,
	IN_GAME
}					t_GameStage;

typedef enum		e_GameMode
{
	VS_IA,
	VS_P2
}					t_GameMode;

/*
**	Gomoku structures
*/

typedef	struct		s_GameDatas
{
	t_GameMode		SelectedGameMode;
}					t_GameDatas;


// class forward declarations.

class				GameImage;
class				SDLHandler;
class				MainMenuController;
class				MainController;
class				Tools;

# include "GameImage.hpp"
# include "SDLHandler.hpp"
# include "MainMenuController.hpp"
# include "MainController.hpp"
# include "Tools.hpp"

#endif
