#include "../includes/Gomoku.hpp"

/*
**	Note: a stone is 56 x 56. the board is 1080 x 1080
*/

void	GobanController::InitBoard(SDLHandler &SDLHandler)
{
	// point zero setting;
	_pointZeroX = 428;
	_pointZeroY = 1015;
	// distance between each stone;
	_stoneXStep = 56;
	_stoneYStep = 56;
	// max number of stone : 19 x 19
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
}

void	GobanController::PlaceImagesOnStart(SDLHandler &SDLHandler)
{
	GobanImg->SetImgPos(420, 0);
	GobanImg->SetImgSize(1080, 1080);
	GobanImg->SetAlpha(0);
	GobanImg->PutImage(SDLHandler);
}

void	GobanController::UpdateDisplay(t_GameDatas &Game, SDLHandler &SDLHandler)
{
	int i;

	(void)Game;
	GobanImg->FadeIn();
	GobanImg->PutImage(SDLHandler);
	i = 0;
	while (i != _max_stones)
	{
		StonesImgList[i]->FadeIn();
		StonesImgList[i]->PutImage(SDLHandler);
		i++;
	}
}

void	GobanController::LoadStones(SDLHandler	&SDLHandler)
{
	int				i;
	GameImage		*newStone;

	i = 0;
	while (i != _max_stones)
	{
		newStone = new GameImage(SDLHandler, "./ressources/img/in_game/go_stone_black.bmp");
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
		StonesImgList[i]->SetImgPos(_pointZeroX + _stoneXStep * x, _pointZeroY - _stoneYStep * y);
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
