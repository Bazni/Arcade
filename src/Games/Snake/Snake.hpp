/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**
*/

#ifndef CPP_ARCADE_SNAKE_HPP
#define CPP_ARCADE_SNAKE_HPP

#include <Games/IGame.hpp>

namespace Arcade {

	constexpr Color fruit = {255, 0, 0, 0};
	constexpr Color wood = {126, 75, 31, 0};
	constexpr Color green = {87, 251, 87, 0};
	constexpr Color blue = {17, 49, 209, 0};

	constexpr int nbPixel = 868; // side * side
	constexpr int side = 31;

	constexpr double fastSpeed = 0.03f;
	constexpr double normalSpeed = 0.10f;

	class Snake : public IGame {
	public:
		Snake();
		virtual ~Snake();

		std::string getName() override;
		std::vector<std::vector<Arcade::Pixel>>
		getScreenLayers() override;
		std::string getBackground() override;
		void sendInput(Arcade::Input input) override;
		void update() override;
		std::pair<unsigned int, unsigned int> getRes() override;
		unsigned int getScore() override;
		void popFruit();
		bool checkSnake(Arcade::Pixel target);
		void place_player(unsigned int numPlayer);
		void reset() override;
		void resetTwo();
		std::string getSoundEffect() override;
		bool isGameOver() override;
	private:
		std::vector<Arcade::Pixel> _screen;
		std::vector<std::vector<Arcade::Pixel>> _players;
		Arcade::Pixel _fruit;
		std::string _currentSoundEffect;
		std::vector<Input> _currentInput;
		std::vector<Input> _up;
		std::vector<Input> _down;
		std::vector<Input> _left;
		std::vector<Input> _right;
		std::vector<Input> _direction;
		bool _speed;
		unsigned int _maxScore;
		unsigned int _level;
		unsigned int _score;
		unsigned int _nbPlayers;
		bool _gameOver;
		void moveAlone(unsigned int numPlayer);
		void goUp(unsigned int numPlayer);
		void goDown(unsigned int numPlayer);
		void goLeft(unsigned int numPlayer);
		void goRight(unsigned int numPlayer);
	};
}

extern "C" void destroyGame(Arcade::IGame *game);
extern "C" Arcade::IGame *createGame();

#endif //CPP_ARCADE_SNAKE_HPP
