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
# include <chrono>
# include <map>
# include <ctime>
# include <thread>

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

using namespace std;
# define PERROR(msg, level) (Tools::printError(__FILE__, __LINE__, __func__, msg, level))


# define DEBUG_MODE 0
# define IA_ON_BLACK

/*
**	SDL engine defines
*/

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define SCREEN_RATIO_X 16
# define SCREEN_RATIO_Y 9
# define SCREEN_RATIO 1.7

/*
**	Alpaha-Bata defines
*/

# define DEFAULT_IA_DEEP 3
# define MIN_DEPTH 1
# define MAX_DEPTH 10

# define ALPHA -100000
# define BETA 100000


/*
**	print debug defines
*/

# define ERR 0  //Error
# define WARN 1 //Warning
# define INFO 2 //Info

/*
**	Game defines
*/

typedef enum 		e_GameScene
{
	MAIN_MENU,
	IN_GAME
}					t_GameScene;

typedef enum		e_GameMode
{
	VS_IA,
	VS_P2
}					t_GameMode;

typedef enum		e_Color
{
	NONE,
	BLACK,
	WHITE,
	SUGGESTION,
	WINNING
}					t_Color;

typedef struct		s_vec2
{
	int				x;
	int				y;
}					t_vec2;

typedef enum		e_dir
{
	CURRENT,
	TOP_LEFT,
	TOP,
	TOP_RIGHT,
	RIGHT,
	BOTTOM_RIGHT,
	BOTTOM,
	BOTTOM_LEFT,
	LEFT,

}					t_dir;

typedef struct		s_VictorySequence
{
	t_Color					Color;
	std::vector<t_vec2> 	Stones;
	std::vector<t_vec2>		CapturePoints;
}					t_VictorySequence;

/*
**	Heuristic defines
*/

// victory search values
# define SURE_VICTORY 3000
# define VICTORY_CAPTURABLE 1000

// simple search values
# define FREE_ONE 3
# define ONE 1
# define STRAIGHT_TWO 4
# define TWO 2

// threat value defines

# define THREE 20
# define STRAIGHT_THREE 16
# define BROKEN_THREE 20
# define FOUR 20
# define STRAIGHT_FOUR 200
# define BROKEN_FOUR 150

// capture search defines

# define ATTACK_CAPTURE_FORM 10
# define CAPTURE_DONE 200
# define VICTORY_CAPTURE_FORM 3000

/*
**	Gomoku structures
*/

class				Board;
# include "Board.hpp"


typedef	struct		s_GameDatas
{
	t_GameScene		SelectedScene;
	t_GameMode		SelectedGameMode;

	Board			Board;

	bool			CanClick; // prevent multi click.

	t_Color			ActivePlayer;
	int				TurnNumber;
	int				MoveNumber;
	int				LastTurnIATime;

	bool			WhiteInCheck;
	bool			BlackInCheck;

	int				IA_Depth;

	bool			IsGameOver;
	t_Color			WinnerColor;

	t_vec2			LastSuggestion;

	std::vector<class Board> BoardStates;

}					t_GameDatas;


// class forward declarations.

class				GameImage;
class				GameUI;
class				GameText;
class				SDLHandler;
class				MainMenuController;
class				InGameController;
class				GobanController;
class				MainController;
class				GameRules;
class				IA;
class				Heuristic;
class				GameController;
class				BoardTools;
class				Tools;


# include "GameImage.hpp"
# include "GameUI.hpp"
# include "GameText.hpp"
# include "SDLHandler.hpp"
# include "MainMenuController.hpp"
# include "GobanController.hpp"
# include "GameRules.hpp"
# include "IA.hpp"
# include "Heuristic.hpp"
# include "GameController.hpp"
# include "InGameController.hpp"
# include "MainController.hpp"
# include "BoardTools.hpp"
# include "Tools.hpp"

#endif
