/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**
*/

#include <fstream>
#include <Core/Core.hpp>
#include <iostream>
#include "Snake.hpp"

extern "C" Arcade::IGame *createGame()
{
	return new Arcade::Snake();
}

extern "C" void destroyGame(Arcade::IGame *game)
{
	delete dynamic_cast<Arcade::Snake *>(game);
}

static int calcPos(int x, int y)
{
	return x * 31 + y;
}

void Arcade::Snake::place_player(unsigned int numPlayer)
{
	std::vector<Arcade::Pixel> player;
	Arcade::Pixel pixel;

	pixel = {13, 16 + numPlayer, blue, "games/snake/assets/head_left.png"};
	player.emplace_back(pixel);
	pixel = {14, 16 + numPlayer, blue, "games/snake/assets/skin.png"};
	player.emplace_back(pixel);
	pixel = {15, 16 + numPlayer, blue, "games/snake/assets/skin.png"};
	player.emplace_back(pixel);
	pixel = {16, 16 + numPlayer, blue, "games/snake/assets/skin.png"};
	player.emplace_back(pixel);
	_players.emplace_back(player);
}

bool	Arcade::Snake::checkSnake(Arcade::Pixel target)
{
	unsigned int i = 0;
	unsigned int p = 0;

	while (p < _players.size()) {
		while (i < _players[p].size()) {
			if (_players[p][i].x == target.x &&
				_players[p][i].y == target.y)
				return true;
			i++;
		}
		i = 0;
		p++;
	}
	return false;
}

void	Arcade::Snake::popFruit()
{
	int tmp = rand() % nbPixel;
	Arcade::Pixel target = _screen[tmp];

	if (_score != 0)
		_currentSoundEffect = "games/snake/eat.ogg";
	while (checkSnake(target) || wood == _screen[tmp].color) {
		tmp = rand() % nbPixel;
		target = _screen[tmp];
	}
	_fruit = {_screen[tmp].x, _screen[tmp].y, fruit,
		"games/snake/assets/fruit.png"};
	_screen[tmp].color = fruit;
}

Arcade::Snake::Snake()
{
	unsigned int i = 0;

	_gameOver = false;
	_nbPlayers = 1;
	_score = 0;
	while (i < _nbPlayers) {
		_direction.emplace_back(LEFT_ARROW);
		_up.emplace_back(LEFT_ARROW);
		_down.emplace_back(LEFT_ARROW);
		_left.emplace_back(LEFT_ARROW);
		_right.emplace_back(LEFT_ARROW);
		_currentInput.emplace_back(LEFT_ARROW);
		i++;
	}
	if (_nbPlayers == 1)
		reset();
	else
		resetTwo();
}

std::vector<std::vector<Arcade::Pixel>> Arcade::Snake::getScreenLayers()
{
	std::vector<std::vector<Arcade::Pixel>> screens;
	std::vector<Arcade::Pixel> tmp;
	unsigned int p = 0;

	tmp.emplace_back(_fruit);
	screens.emplace_back(_screen);
	while (p < _players.size()) {
		screens.emplace_back(_players[p]);
		p++;
	}
	screens.emplace_back(tmp);
	return screens;
}

void Arcade::Snake::sendInput(Arcade::Input input)
{
	if (input == _left[0] && _direction[0] != _right[0])
		_currentInput[0] = input;
	if (input == _right[0] && _direction[0] != _left[0] &&
		_direction[0] != NO_INPUT)
		_currentInput[0] = input;
	if (input == _up[0] && _direction[0] != _down[0])
		_currentInput[0] = input;
	if (input == _down[0] && _direction[0] != _up[0])
		_currentInput[0] = input;
	if (input == _left[1] && _direction[1] != _right[1])
		_currentInput[1] = input;
	if (input == _right[1] && _direction[1] != _left[1] &&
		_direction[1] != NO_INPUT)
		_currentInput[1] = input;
	if (input == _up[1] && _direction[1] != _down[1])
		_currentInput[1] = input;
	if (input == _down[1] && _direction[1] != _up[1])
		_currentInput[1] = input;
	_speed = input == SPACE;
	_nbPlayers = (input == J_KEY && _nbPlayers == 1) ? 2 : (input == J_KEY && _nbPlayers == 2) ? 1: 2;
}

void Arcade::Snake::moveAlone(unsigned int numPlayer)
{
	if (_direction[numPlayer] == _up[numPlayer])
		goUp(numPlayer);
	if (_direction[numPlayer] == _down[numPlayer])
		goDown(numPlayer);
	if (_direction[numPlayer] == _left[numPlayer])
		goLeft(numPlayer);
	if (_direction[numPlayer] == _right[numPlayer])
		goRight(numPlayer);
}

void Arcade::Snake::goUp(unsigned int numPlayer)
{
	Color target;

	Arcade::Pixel play = _players[numPlayer][0];
	play.pathSprite = "games/snake/assets/skin.png";
	target = _screen[calcPos(play.y - 1, play.x)].color;
	if (target == wood ||
		checkSnake({play.x, play.y - 1, blue,
			"games/snake/assets/skin.png"})) {
		_gameOver = true;
		if (_nbPlayers == 1)
			reset();
		else
			resetTwo();
		return;
	} else if (target == fruit) {
		_score += 100;
		_screen[calcPos(play.y - 1, play.x)].color = green;
		play.y--;
		popFruit();
		_direction[numPlayer] = _up[numPlayer];
	} else {
		play.y--;
		_players[numPlayer].erase(_players[numPlayer].end() - 1);
		_direction[numPlayer] = _up[numPlayer];
	}
	_players[numPlayer].insert(_players[numPlayer].begin(), play);
	_players[numPlayer][0].pathSprite = "games/snake/assets/head_up.png";
	if (_players[numPlayer].size() > 1)
		_players[numPlayer][1].pathSprite = "games/snake/assets/skin.png";
}

void Arcade::Snake::goDown(unsigned int numPlayer)
{
	Color target;

	Arcade::Pixel play = _players[numPlayer][0];
	play.pathSprite = "games/snake/assets/skin.png";
	target = _screen[calcPos(play.y + 1, play.x)].color;
	if (target == wood ||
		checkSnake({play.x, play.y + 1, blue,
			"games/snake/assets/skin.png"})) {
		_gameOver = true;
		if (_nbPlayers == 1)
			reset();
		else
			resetTwo();
		return;
	} else if (target == fruit) {
		_score += 100;
		_screen[calcPos(play.y + 1, play.x)].color = green;
		play.y++;
		popFruit();
		_direction[numPlayer] = _down[numPlayer];
	} else {
		play.y++;
		_players[numPlayer].erase(_players[numPlayer].end() - 1);
		_direction[numPlayer] = _down[numPlayer];
	}
	_players[numPlayer].insert(_players[numPlayer].begin(), play);
	_players[numPlayer][0].pathSprite = "games/snake/assets/head_down.png";
	if (_players[numPlayer].size() > 1)
		_players[numPlayer][1].pathSprite = "games/snake/assets/skin.png";
}

void Arcade::Snake::goLeft(unsigned int numPlayer)
{
	Color target;

	Arcade::Pixel play = _players[numPlayer][0];
	play.pathSprite = "games/snake/assets/skin.png";
	target = _screen[calcPos(play.y, play.x - 1)].color;
	if (target == wood ||
		checkSnake({play.x - 1, play.y, blue,
			"games/snake/assets/skin.png"})) {
		_gameOver = true;
		if (_nbPlayers == 1)
			reset();
		else
			resetTwo();
		return;
	} else if (target == fruit) {
		_score += 100;
		_screen[calcPos(play.y, play.x - 1)].color = green;
		play.x--;
		popFruit();
		_direction[numPlayer] = _left[numPlayer];
	} else {
		play.x--;
		_players[numPlayer].erase(_players[numPlayer].end() - 1);
		_direction[numPlayer] = _left[numPlayer];
	}
	_players[numPlayer].insert(_players[numPlayer].begin(), play);
	_players[numPlayer][0].pathSprite = "games/snake/assets/head_left.png";
	if (_players[numPlayer].size() > 1)
		_players[numPlayer][1].pathSprite = "games/snake/assets/skin.png";
}

void Arcade::Snake::goRight(unsigned  int numPlayer)
{
	Color target;

	Arcade::Pixel play = _players[numPlayer][0];
	play.pathSprite = "games/snake/assets/skin.png";
	target = _screen[calcPos(play.y, play.x + 1)].color;
	if (target == wood ||
		checkSnake({play.x + 1, play.y, blue,
			"games/snake/assets/skin.png"})) {
		_gameOver = true;
		if (_nbPlayers == 1)
			reset();
		else
			resetTwo();
		return;
	} else if (target == fruit) {
		_score += 100;
		_screen[calcPos(play.y, play.x + 1)].color = green;
		play.x++;
		popFruit();
		_direction[numPlayer] = _right[numPlayer];
	} else {
		play.x++;
		_players[numPlayer].erase(_players[numPlayer].end() - 1);
		_direction[numPlayer] = _right[numPlayer];
	}
	_players[numPlayer].insert(_players[numPlayer].begin(), play);
	_players[numPlayer][0].pathSprite = "games/snake/assets/head_right.png";
	if (_players[numPlayer].size() > 1)
		_players[numPlayer][1].pathSprite = "games/snake/assets/skin.png";
}

unsigned int Arcade::Snake::getScore()
{
	return _score;
}

std::pair<unsigned int, unsigned int> Arcade::Snake::getRes()
{
	return std::pair<unsigned int, unsigned int>{side, side};
}

void Arcade::Snake::update()
{	static clock_t t = clock();
	clock_t now = clock();
	float delta = now - t;
	double speed;
	unsigned int p = 0;

	if (_speed)
		speed = fastSpeed;
	else
		speed = normalSpeed;
	if (delta / CLOCKS_PER_SEC > speed) {
		t = clock();
		while (p < _players.size()) {
			_direction[p] = _currentInput[p];
			moveAlone(p);
			p++;
		}
	}
}

std::string Arcade::Snake::getName()
{
	return std::string("Snake");
}

std::string Arcade::Snake::getBackground()
{
	return "games/snake/assets/background.png";
}

void Arcade::Snake::reset()
{
	_currentInput[0] = NO_INPUT;
	_direction[0] = LEFT_ARROW;
	_up[0] = UP_ARROW;
	_down[0] = DOWN_ARROW;
	_left[0] = LEFT_ARROW;
	_right[0] = RIGHT_ARROW;
	_speed = false;
	_gameOver = false;
	_level = 1;
	_score = 0;
	_maxScore = 0;
	_screen.clear();
	_currentSoundEffect = "";

	std::ifstream map("games/snake/snake.map");
	std::string line;

	srand(time(NULL));
	for (unsigned int y = 0; y < side; y++) {
		std::getline(map, line);
		for (unsigned int x = 0; x < side; x++) {
			if (line[x] == '#')
				_screen.push_back({x, y, wood, "games/snake/assets/wall.png"});
			else {
				_screen.push_back({x, y, green, ""});
				_maxScore += 100;
			}
		}
	}
	_players.clear();
	place_player(1);
	popFruit();
}

void Arcade::Snake::resetTwo()
{
	_speed = false;
	_gameOver = false;
	_level = 1;
	_score = 0;
	_maxScore = 0;
	_screen.clear();
	_currentSoundEffect = "";

	std::ifstream map("games/snake/snake.map");
	std::string line;
	unsigned int i = 0;

	srand(time(NULL));
	for (unsigned int y = 0; y < side; y++) {
		std::getline(map, line);
		for (unsigned int x = 0; x < side; x++) {
			if (line[x] == '#')
				_screen.push_back({x, y, wood, "games/snake/assets/wall.png"});
			else {
				_screen.push_back({x, y, green, ""});
				_maxScore += 100;
			}
		}
	}
	_players.clear();
	while (i < _nbPlayers) {
		place_player(i);
		_direction[i] = LEFT_ARROW;
		_currentInput[i++] = NO_INPUT;
	}
	_up[0] = UP_ARROW;
	_down[0] = DOWN_ARROW;
	_left[0] = LEFT_ARROW;
	_right[0] = RIGHT_ARROW;
	_up[1] = Z_KEY;
	_down[1] = S_KEY;
	_left[1] = Q_KEY;
	_right[1] = D_KEY;
	popFruit();
}

std::string Arcade::Snake::getSoundEffect()
{
	std::string soundEffect = _currentSoundEffect;
	_currentSoundEffect.clear();
	return soundEffect;}

bool Arcade::Snake::isGameOver()
{
	bool gameOver;

	if (_score * _level >= _maxScore * _level)
		_gameOver = true;
	gameOver = _gameOver;
	_gameOver = false;
	return gameOver;
}

Arcade::Snake::~Snake() = default;
