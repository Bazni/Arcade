/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#ifndef CPP_ARCADE_ALLEGRO_HPP
#define CPP_ARCADE_ALLEGRO_HPP

#define ALLEGRO_UNSTABLE 1

#include "ILibrary.hpp"
#include "SFML.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

namespace Arcade {
	class Allegro : public ILibrary {
	public:
		Allegro();
		~Allegro();

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
		ALLEGRO_DISPLAY *_display;
		ALLEGRO_EVENT_QUEUE *_eventKeyboardQueue;
		ALLEGRO_EVENT_QUEUE *_eventWindowQueue;
		ALLEGRO_BITMAP *_background;
		ALLEGRO_FONT *_font;
		unsigned int _score;
		std::string _gameName;

		Arcade::Input getRawInput();
	};
}

extern "C" Arcade::ILibrary * createLibrary();
extern "C" void destroyLibrary(Arcade::ILibrary *library);

#endif //CPP_ARCADE_ALLEGRO_HPP
