/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**
*/

#include <vector>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <Core/Core.hpp>
#include "Core/Core.hpp"
#include "Pacman.hpp"

extern "C" Arcade::IGame *createGame()
{
	return new Arcade::Pacman();
}

extern "C" void destroyGame(Arcade::IGame *game)
{
	delete dynamic_cast<Arcade::Pacman *>(game);
}

Arcade::Pacman::Pacman()
{
	reset();
}

void Arcade::Pacman::sendInput(Arcade::Input input)
{
	if (input == LEFT_ARROW || input == RIGHT_ARROW ||
		input == UP_ARROW || input == DOWN_ARROW)
		_currentInput = input;
}

constexpr int calcPos(int x, int y)
{
	return x * 31 + y;
}

bool Arcade::Pacman::moveAlone(Input save)
{
	if (_direction == UP_ARROW)
		return goUp(save);
	if (_direction == DOWN_ARROW)
		return goDown(save);
	if (_direction == LEFT_ARROW)
		return goLeft(save);
	if (_direction == RIGHT_ARROW)
		return goRight(save);
	return true;
}

bool Arcade::Pacman::goUp(Input save)
{
	Color target;
	Color dark = {0, 0, 0, 255};

	target = _screen[calcPos(_player.y - 1, _player.x)].color;
	if (target.r == 0 && target.g == 0 && target.b == 139) {
		_direction = save;
		return false;
	} else {
		if (target.r == 255 && target.g == 255 && target.b == 255) {
			_score += 100;
			_currentSoundEffect = "games/pacman/eat.ogg";
		}
		if (target.r == 0 && target.g == 150 && target.b == 255) {
			_eating = true;
			_run = clock();
		}
		_screen[calcPos(_player.y, _player.x)].color = dark;
		_screen[calcPos(_player.y, _player.x)].pathSprite = "";
		_player.pathSprite = "games/pacman/assets/up.png";
		_player.y--;
	}
	return true;
}

bool Arcade::Pacman::goDown(Input save)
{
	Color target;
	Color dark = {0, 0, 0, 255};

	target = _screen[calcPos(_player.y + 1, _player.x)].color;
	if (target.r == 0 && target.g == 0 && target.b == 139) {
		_direction = save;
		return false;
	} else {
		if (target.r == 255 && target.g == 255 && target.b == 255) {
			_score += 100;
			_currentSoundEffect = "games/pacman/eat.ogg";
		}
		if (target.r == 0 && target.g == 150 && target.b == 255) {
			_eating = true;
			_run = clock();
		}
		_screen[calcPos(_player.y, _player.x)].color = dark;
		_screen[calcPos(_player.y, _player.x)].pathSprite = "";
		_player.pathSprite = "games/pacman/assets/down.png";
		_player.y++;
	}
	return true;
}

bool Arcade::Pacman::goLeft(Input save)
{
	Color target;
	Color dark = {0, 0, 0, 255};

	target = _screen[calcPos(_player.y, _player.x - 1)].color;
	if (target.r == 0 && target.g == 0 && target.b == 139) {
		_direction = save;
		return false;
	} else {
		if (target.r == 255 && target.g == 255 && target.b == 255) {
			_score += 100;
			_currentSoundEffect = "games/pacman/eat.ogg";
		}
		if (target.r == 0 && target.g == 150 && target.b == 255) {
			_eating = true;
			_run = clock();
		}
		_screen[calcPos(_player.y, _player.x)].color = dark;
		_screen[calcPos(_player.y, _player.x)].pathSprite = "";
		_player.pathSprite = "games/pacman/assets/left.png";
		_player.x--;
	}
	if (_player.y == 14 && _player.x - 1 == 0) {
		_player.x = 25;
	}
	return true;
}

bool Arcade::Pacman::goRight(Input save)
{
	Color target;
	Color dark = {0, 0, 0, 255};

	target = _screen[calcPos(_player.y, _player.x + 1)].color;
	if (target.r == 0 && target.g == 0 && target.b == 139) {
		_direction = save;
		return false;
	} else {
		if (target.r == 255 && target.g == 255 && target.b == 255) {
			_score += 100;
			_currentSoundEffect = "games/pacman/eat.ogg";
		}
		if (target.r == 0 && target.g == 150 && target.b == 255) {
			_eating = true;
			_run = clock();
		}
		_screen[calcPos(_player.y, _player.x)].color = dark;
		_screen[calcPos(_player.y, _player.x)].pathSprite = "";
		_player.pathSprite = "games/pacman/assets/right.png";
		_player.x++;
	}
	if (_player.y == 14 && _player.x + 1 == 27) {
		_player.x = 2;
	}
	return true;
}

void Arcade::Pacman::update()
{
	static clock_t t = clock();
	Input save;

	clock_t now = clock();
	float delta = now - t;
	if (delta / CLOCKS_PER_SEC > 0.20f) {
		t = clock();
		save = _direction;
		_direction = _currentInput;
		if (!moveAlone(save))
			moveAlone(save);
		if (!_animation) {
			_player.pathSprite = "games/pacman/assets/round.png";
			_animation = true;
		} else
			_animation = false;
		for (auto &ia : _ia) {
			ia.update(_player, _screen, _eating);
			if (ia.isPlayerDead()) {
				reset();
				_gameOver = true;
			}
		}
	}
	if (_eating) {
		for (auto &i : _ia)
			i.setSprite("games/pacman/assets/fearblue.png");
		float delta = now - _run;
		if (delta / CLOCKS_PER_SEC > 10.f)
			_eating = false;
	} else {
		_ia[0].setSprite("games/pacman/assets/ghostpink.png");
		_ia[1].setSprite("games/pacman/assets/ghostred.png");
		_ia[2].setSprite("games/pacman/assets/ghostblue.png");
		_ia[3].setSprite("games/pacman/assets/ghostorange.png");
	}
	if (_score == 29600)
		reset();
}

std::pair<unsigned int, unsigned int> Arcade::Pacman::getRes()
{
	return std::pair<unsigned int, unsigned int>{31, 28};
}

unsigned int Arcade::Pacman::getScore()
{
	return _score;
}

std::vector<std::vector<Arcade::Pixel>> Arcade::Pacman::getScreenLayers()
{
	std::vector<std::vector<Arcade::Pixel>> layers;
	std::vector<Arcade::Pixel> players;

	layers.push_back(_screen);
	players.push_back(_player);
	players.push_back(_ia[0].getGhost());
	players.push_back(_ia[1].getGhost());
	players.push_back(_ia[2].getGhost());
	players.push_back(_ia[3].getGhost());
	layers.push_back(players);
	return layers;
}

std::string Arcade::Pacman::getName()
{
	return std::string("Pacman");
}

std::string Arcade::Pacman::getBackground()
{
	return std::string("games/pacman/assets/maze.png");
}

bool Arcade::Pacman::isEating() const
{
	return _eating;
}

void Arcade::Pacman::reset()
{
	_currentInput = NO_INPUT;
	_direction = RIGHT_ARROW;
	_eating = false;
	_score = 0;
	_animation = true;
	_currentSoundEffect.clear();
	_gameOver = false;
	_screen.clear();
	Color pink = {199, 21, 133, 255};
	Color red = {255, 0, 0, 255};
	Color deepBlue = {0, 191, 255, 255};
	Color orange = {255, 140, 0, 255};
	std::ifstream map("games/pacman/pacman.map");
	std::string line;
	for (unsigned int y = 0; y < 31; y++) {
		std::getline(map, line);
		for (unsigned int x = 0; x < 29; x++) {
			if (line[x] == '#') {
				Pixel pixel = {x, y, {0, 0, 139, 0}, ""};
				_screen.push_back(pixel);
			} else if (line[x] == 'O') {
				Pixel pixel = {x, y, {0, 150, 255, 0},
					"games/pacman/assets/pacgum.png"};
				_screen.push_back(pixel);
			} else if (line[x] == 'P') {
				Pixel pixel = {x, y, {255, 255, 255, 0}, ""};
				_screen.push_back(pixel);
			} else {
				Pixel pixel = {x, y, {255, 255, 255, 255},
					"games/pacman/assets/tictac.png"};
				_screen.push_back(pixel);
			}
		}
		Pixel pixel = {29, y, {0, 0, 139, 0}, ""};
		_screen.push_back(pixel);
		Pixel pixel2 = {30, y, {0, 0, 139, 0}, ""};
		_screen.push_back(pixel);
	}
	_player = {11, 11, {255, 255, 0, 255}, "games/pacman/assets/left.png"};
	_ia[0] = IAGhost(pink, 1, 1, "games/pacman/assets/ghostpink.png");
	_ia[1] = IAGhost(red, 1, 29, "games/pacman/assets/ghostred.png");
	_ia[2] = IAGhost(deepBlue, 26, 29, "games/pacman/assets/ghostblue.png");
	_ia[3] = IAGhost(orange, 26, 1, "games/pacman/assets/ghostorange.png");
}

std::string Arcade::Pacman::getSoundEffect()
{
	std::string soundEffect = _currentSoundEffect;
	_currentSoundEffect.clear();
	return soundEffect;
}

bool Arcade::Pacman::isGameOver()
{
	bool gameOver = _gameOver;
	_gameOver = false;
	return gameOver;
}

Arcade::Pacman::~Pacman() = default;