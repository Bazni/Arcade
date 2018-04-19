/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#pragma once

#include "Games/IGame.hpp"
#include "AIGhost.hpp"

namespace Arcade {
	class Pacman : public IGame {
	public:
		Pacman();
		virtual ~Pacman();

		std::string getName();
		std::vector<std::vector<Arcade::Pixel>>
		getScreenLayers() override;
		void sendInput(Arcade::Input input) override;
		void update() override;
		std::pair<unsigned int, unsigned int> getRes();
		unsigned int getScore();
		std::string getBackground();
		bool isEating() const;
		void reset() override;
		std::string getSoundEffect() override;
		bool isGameOver() override;
	private:
		std::vector<Arcade::Pixel> _screen;
		Input _currentInput;
		Input _direction;
		Arcade::Pixel _player;
		Arcade::IAGhost _ia[4];
		clock_t _run;
		bool _eating;
		unsigned int _score;
		bool _animation;
		bool _gameOver;
		std::string _currentSoundEffect;
		bool moveAlone(Input save);
		bool goUp(Input save);
		bool goDown(Input save);
		bool goLeft(Input save);
		bool goRight(Input save);
	};
}

extern "C" void destroyGame(Arcade::IGame *game);
extern "C" Arcade::IGame *createGame();