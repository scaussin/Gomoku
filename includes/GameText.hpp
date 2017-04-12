#ifndef GAMETEXT_HPP
# define GAMETEXT_HPP

class GameText
{
	public:
		GameText(SDLHandler &SDLHandler, std::string text, int size);
		~GameText();

		void			SetTextPos(int x, int y);
		void			SetTextSize(int width, int height);
		void			PutText(SDLHandler &SDLHandler);
		void			SetBlendMode(SDL_BlendMode blending);
		void			SetAlpha(Uint8 alpha);
		Uint8			GetAlpha();
		void			FadeIn();
		void			FadeOut();
		bool			IsColliding(int x, int y);
		SDL_Rect		GetRect();
		SDL_Texture		*GetTexture();
		void			SetTexture(SDL_Texture *texture);

	private:
		TTF_Font		*_font;
		int				_fontSize;
		int				_alpha;
		SDL_Color		_fontColor;

		SDL_Surface		*_textSurface;
		SDL_Texture		*_textTexture;
		SDL_Rect		_textRect;
};

#endif