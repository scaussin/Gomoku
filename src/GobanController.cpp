#include "../includes/Gomoku.hpp"

/*
**	Note: a stone is 56 x 56. the board is 1080 x 1080
*/

// ------------------------------------------------------------	//
//																//
//	Init Methods the goban.										//
//																//
// ------------------------------------------------------------	//

void	GobanController::InitBoard(SDLHandler &SDLHandler)
{
	// point zero setting;
	_pointZeroX = 428;
	_pointZeroY = 1015;
	// distance between each stone;
	_stoneXStep = 56;
	_stoneYStep = 56;
	// max number of stone : 19 x 19 = 361
	_max_stones = 361;

	// load and place images;
	LoadImages(SDLHandler);
	PlaceImagesOnStart(SDLHandler);
	LoadStones(SDLHandler);
	PlaceStones(SDLHandler);
}

void	GobanController::LoadImages(SDLHandler &SDLHandler)
{
	GobanImg = new GameImage(SDLHandler, "./ressources/img/in_game/goban.bmp");
	WhiteStoneSurface = SDL_LoadBMP("./ressources/img/in_game/go_stone_white.bmp");
	BlackStoneSurface = SDL_LoadBMP("./ressources/img/in_game/go_stone_black.bmp");
	SuggestStoneSurface = SDL_LoadBMP("./ressources/img/in_game/go_stone_suggest.bmp");
	NoStoneSurface = SDL_LoadBMP("./ressources/img/in_game/go_stone_none.bmp");
}

void	GobanController::PlaceImagesOnStart(SDLHandler &SDLHandler)
{
	GobanImg->SetImgPos(420, 0);
	GobanImg->SetImgSize(1080, 1080);
	GobanImg->SetAlpha(0);
	GobanImg->PutImage(SDLHandler);
}

void	GobanController::LoadStones(SDLHandler	&SDLHandler)
{
	int				i;
	GameImage		*newStone;

	i = 0;
	while (i != _max_stones)
	{
		newStone = new GameImage(SDLHandler, "./ressources/img/in_game/go_stone_none.bmp");
		newStone->SetImgSize(56, 56);
		newStone->SetAlpha(255);
		StonesImgList.push_back(newStone);
		i++;
	}
}

void	GobanController::PlaceStones(SDLHandler	&SDLHandler)
{
	int				i;
	int				x;
	int 			y;

	i = 0;
	x = 0;
	y = 0;
	while (i != _max_stones)
	{
		StonesImgList[i]->SetImgPos(_pointZeroX + _stoneXStep * x,
									_pointZeroY - _stoneYStep * y);
		StonesImgList[i]->PutImage(SDLHandler);
		i++;
		x++;
		if (i % 19 == 0)
		{
			y += 1;
			x = 0;
		}
	}
}

// ------------------------------------------------------------	//
//																//
//	Event handling methods. -> interactions between user and	//
//	the goban.													//
//																//
// ------------------------------------------------------------	//

int		GobanController::HandleClickEvents(t_GameDatas &GameDatas, SDL_Event &event,
							SDLHandler &SDLHandler, t_vec2 &move)
{
	(void)SDLHandler;
	(void)GameDatas;
	int		it_index;

	for (std::vector<GameImage *>::iterator	it = StonesImgList.begin();
		it != StonesImgList.end(); it++)
	{
		if ((*it)->IsColliding(event.button.x, event.button.y))
		{
			it_index = it - StonesImgList.begin();
			move.x = it_index % 19;
			move.y = it_index / 19;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				return (1);
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				return (2);
			}

			// to put any color.
			// if (event.button.button == SDL_BUTTON_LEFT)
			// {
			// 	(*it)->SetTexture(BlackStoneTexture);
			// }
			// else if (event.button.button == SDL_BUTTON_RIGHT)
			// {
			// 	(*it)->SetTexture(WhiteStoneTexture);
			// }
			// else if (event.button.button == SDL_BUTTON_MIDDLE)
			// {
			// 	(*it)->SetTexture(SuggestStoneTexture);
			// }
		}
	}
	return (0);
}

// ------------------------------------------------------------	//
//																//
//	Display the goban elements.									//
//																//
// ------------------------------------------------------------	//

// note that this also decides the z index of the images
// -> the last img put on will be the most close to the camera.
void	GobanController::PutDisplay(t_GameDatas &Game, SDLHandler &SDLHandler)
{
	int i;

	(void)Game;
	if (GobanImg->GetAlpha() < 255)
		GobanImg->FadeIn();
	GobanImg->PutImage(SDLHandler);
	i = 0;
	while (i != _max_stones)
	{
		StonesImgList[i]->PutImage(SDLHandler);
		i++;
	}
}

void	GobanController::TransitionOut(SDLHandler &SDLHandler)
{
	if (GobanImg->GetAlpha() > 0)
		GobanImg->FadeOut();
	GobanImg->PutImage(SDLHandler);
}

// This will update the board display from the modifications made in game.
void	GobanController::UpdateBoard(t_GameDatas &Game, SDLHandler &SDLHandler)
{
	(void)Game;
	(void)SDLHandler;
	
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19 ; j++)
		{
			SetPointDisplay(i, j, (t_Color)Game.Board.getPoint(j, i), SDLHandler);
		}
	}
}

/*
** For a given board case and color, change the visual to the desired one.
*/

void	GobanController::SetPointDisplay(int x, int y, t_Color color, SDLHandler &SDLHandler)
{
	SDL_Surface		*new_surface;

	if (color == NONE)
		new_surface = NoStoneSurface;
	else if (color == BLACK)
		new_surface = BlackStoneSurface;
	else if (color == WHITE)
		new_surface = WhiteStoneSurface;
	else if (color == SUGGESTION)
		new_surface = SuggestStoneSurface;
	else
		new_surface = NoStoneSurface;
	_index_tmp = y * 19 + x;
	StonesImgList[_index_tmp]->SetSurface(SDLHandler, new_surface);
	if (color == SUGGESTION)
		StonesImgList[_index_tmp]->SetAlpha(150);
	else
		StonesImgList[_index_tmp]->SetAlpha(255);
	StonesImgList[_index_tmp]->PutImage(SDLHandler);
}

// clean the board to full NONE color.
void	GobanController::ResetBoardVisuals(SDLHandler &SDLHandler)
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19 ; j++)
		{
			SetPointDisplay(i, j, NONE, SDLHandler);
		}
	}
}
