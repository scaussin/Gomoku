#ifndef	GOBANCONTROLLER_HPP
# define GOBANCONTROLLER_HPP

// ----------------------------------------------------	//
//														//
//	Class controlling the goban (go board).				//
//	Used in the InGameController class scene.			//
//														//
// ----------------------------------------------------	//

class GobanController
{
	public:
		GameImage					*GobanImg;
		std::vector<GameImage *>	StonesImgList;

		SDL_Texture					*BlackStoneTexture;
		SDL_Texture					*WhiteStoneTexture;

		// class methods.
		void			InitBoard(SDLHandler &SDLHandler);
		void			LoadImages(SDLHandler &SDLHandler);
		void			PlaceImagesOnStart(SDLHandler &SDLHandler);
		void			UpdateDisplay(t_GameDatas &Game, SDLHandler &SDLHandler);
		void			LoadStones(SDLHandler &SDLHandler);
		void			PlaceStones(SDLHandler &SDLHandler);

	private:
		int				_pointZeroX;
		int				_pointZeroY;
		int				_stoneXStep;
		int				_stoneYStep;
		int				_max_stones;
};

#endif
