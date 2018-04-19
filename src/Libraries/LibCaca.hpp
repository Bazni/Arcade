/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#ifndef CPP_ARCADE_LIBCACA_HPP
#define CPP_ARCADE_LIBCACA_HPP

#include <caca.h>
#include "ILibrary.hpp"
#include "SFML.hpp"

namespace Arcade {
	class LibCaca : public ILibrary {
	public:
		LibCaca();
		~LibCaca();

		void createWindow();
		void destroyWindow();

		Arcade::Input getInput();
		void putPixel(Arcade::Pixel pixel);
		void putText(const Arcade::Text &text);
		void drawBackground(const std::string &backgroundPath)
		{ (void)backgroundPath; }
		void sendScore(unsigned int score);
		void drawUserInterface();
		void sendName(const std::string &name);
		void clear();
		void update();
		std::string getLibraryName();
	private:
		caca_canvas_t *_canvas;
		caca_display_t *_display;
		unsigned int _score;
		std::string _gameName;
	};
}

extern "C" Arcade::ILibrary * createLibrary();
extern "C" void destroyLibrary(Arcade::ILibrary *library);

#endif //CPP_ARCADE_LIBCACA_HPP
