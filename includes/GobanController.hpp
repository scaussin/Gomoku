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

		SDL_Surface					*BlackStoneSurface;
		SDL_Surface					*WhiteStoneSurface;
		SDL_Surface					*SuggestStoneSurface;
		SDL_Surface					*NoStoneSurface;

		// class init methods.
		void			InitBoard(SDLHandler &SDLHandler);
		void			LoadImages(SDLHandler &SDLHandler);
		void			PlaceImagesOnStart(SDLHandler &SDLHandler);
		void			LoadStones(SDLHandler &SDLHandler);
		void			PlaceStones(SDLHandler &SDLHandler);
		// class event methods.
		int				HandleClickEvents(t_GameDatas &GameDatas,
										SDL_Event &event,
										SDLHandler &SDLHandler, t_vec2 &move);
		// class display methods
		void			PutDisplay(t_GameDatas &Game,
										SDLHandler &SDLHandler);
		void			UpdateBoard(t_GameDatas &GameDatas, SDLHandler &SDLHandler);
		void			SetPointDisplay(int x, int y, t_Color color,
										SDLHandler &SDLHandler);

	private:
		int				_pointZeroX;
		int				_pointZeroY;
		int				_stoneXStep;
		int				_stoneYStep;
		int				_max_stones;

		int				_index_tmp;
};

#endif
