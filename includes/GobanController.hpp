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

		GameImage					*BlackStoneImg;
		GameImage					*WhiteStoneImg;
		GameImage					*SuggestStoneImg;
		SDL_Texture					*BlackStoneTexture;
		SDL_Texture					*WhiteStoneTexture;
		SDL_Texture					*SuggestStoneTexture;

		// class methods.
		void			InitBoard(SDLHandler &SDLHandler);
		void			LoadImages(SDLHandler &SDLHandler);
		void			PlaceImagesOnStart(SDLHandler &SDLHandler);
		void			UpdateDisplay(t_GameDatas &Game, SDLHandler &SDLHandler);
		void			LoadStones(SDLHandler &SDLHandler);
		void			PlaceStones(SDLHandler &SDLHandler);
		void			HandleEvents(t_GameDatas &GameDatas, SDL_Event &event,
							SDLHandler &SDLHandler);

	private:
		int				_pointZeroX;
		int				_pointZeroY;
		int				_stoneXStep;
		int				_stoneYStep;
		int				_max_stones;
};

#endif
