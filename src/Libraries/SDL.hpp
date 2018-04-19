/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SDL
*/

#ifndef CPP_ARCADE_SDL_HPP
#define CPP_ARCADE_SDL_HPP

#include "ILibrary.hpp"
#include "SFML.hpp"

namespace Arcade {
	class SDL : public ILibrary {
	public:
		SDL();
		~SDL();

		void createWindow();
		void destroyWindow();

		Arcade::Input getInput();
		void putPixel(Arcade::Pixel pixel);
		void putText(const Arcade::Text &text);
		void drawBackground(const std::string &backgroundPath);
		void sendScore(unsigned int score);
		void drawUserInterface();
		void sendName(const std::string &name);
		void clear();
		void update();
		std::string getLibraryName();
	private:
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		TTF_Font *_font;
		SDL_Texture *_background;
		unsigned int _score;
		std::string _gameName;
	};
}

extern "C" Arcade::ILibrary * createLibrary();
extern "C" void destroyLibrary(Arcade::ILibrary *library);

#endif //CPP_ARCADE_SDL_HPP
