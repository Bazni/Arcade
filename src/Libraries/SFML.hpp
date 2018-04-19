/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SFML
*/

#ifndef CPP_ARCADE_SFML_HPP
#define CPP_ARCADE_SFML_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "Libraries/ILibrary.hpp"
#include "IMusic.hpp"

namespace Arcade {
	class SFML : public ILibrary, public IMusic {
	public:
		SFML();
		~SFML();

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

		void playSound(const std::string &path, bool loop, float volume);
		void cleanSounds();
	private:
		void cleanUnusedSounds();

		sf::RenderWindow _window;
		sf::Font _font;
		sf::Texture _bgTexture;
		sf::Sprite _bgSprite;
		unsigned int _score;
		std::string _gameName;

		std::unordered_map<std::string, sf::SoundBuffer> _soundBuffer;
		std::vector<std::unique_ptr<sf::Sound>> _soundQueue;
	};
}

extern "C" Arcade::ILibrary *createLibrary();
extern "C" void destroyLibrary(Arcade::ILibrary *library);
extern "C" Arcade::IMusic *createMusic();
extern "C" void destroyMusic(Arcade::IMusic *library);

#endif
