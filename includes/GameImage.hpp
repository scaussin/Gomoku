#ifndef GAMEIMAGE_HPP
# define GAMEIMAGE_HPP

# include "Gomoku.hpp"

/*
**	Overlay class for handling images, between the game and the engine.
*/

class GameImage
{
	public:


		GameImage(SDLHandler &SDLHandler, std::string imgPath);
		~GameImage();
		
		void			SetImgPos(int x, int y);
		void			SetImgSize(int width, int height);

		void			PutImage(SDLHandler &SDLHandler);

		void			SetBlendMode(SDL_BlendMode blending);
		void			SetAlpha(Uint8 alpha);

		Uint8			GetAlpha();
		void			FadeIn();
		void			FadeOut();


	private:

		SDL_Surface		*_imgSurface;
		SDL_Texture		*_imgTexture;
		SDL_Rect		_imgRect;
		Uint8			_alpha;
	
};

#endif
