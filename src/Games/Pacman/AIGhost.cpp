/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#include <Core/Core.hpp>
#include <cstdlib>
#include <cstdio>
#include "AIGhost.hpp"

Arcade::IAGhost::IAGhost(Arcade::Color color, unsigned int x, unsigned int y,
	const std::string &pathSprite) : _direction(NO_INPUT), _under({255, 255, 255, 255}), _isPlayerDead(false)
{
	_ghost.color = color;
	_ghost.x = x;
	_ghost.y = y;
	_ghost.pathSprite = pathSprite;
}

constexpr int calcPos(int x, int y)
{
	return x * 31 + y;
}

int Arcade::IAGhost::goLeft(std::vector<Arcade::Pixel> &screen,
	Arcade::Pixel player)
{
	Color target;

	target = screen[calcPos(_ghost.y - 1, _ghost.x)].color;
	if (_ghost.x == player.x && _ghost.y - 1 == player.y)
		_isPlayerDead = true;
	else if (_ghost.x == player.x && _ghost.y == player.y)
		_isPlayerDead = true;
	if (target.r == 0 && target.g == 0 && target.b == 139) {
		return ERROR;
	} else {
		_ghost.y--;
		_direction = UP_ARROW;
		return SUCCESS;
	}
}

int Arcade::IAGhost::goRight(std::vector<Arcade::Pixel> &screen,
	Arcade::Pixel player)
{
	Color target;

	target = screen[calcPos(_ghost.y + 1, _ghost.x)].color;
	if (_ghost.x == player.x && _ghost.y + 1 == player.y)
		_isPlayerDead = true;
	else if (_ghost.x == player.x && _ghost.y + 1 == player.y)
		_isPlayerDead = true;
	if (target.r == 0 && target.g == 0 && target.b == 139) {
		return ERROR;
	} else {
		_ghost.y++;
		_direction = DOWN_ARROW;
		return SUCCESS;
	}
}

int Arcade::IAGhost::goUp(std::vector<Arcade::Pixel> &screen,
	Arcade::Pixel player)
{
	Color target;

	target = screen[calcPos(_ghost.y, _ghost.x - 1)].color;
	if (_ghost.x - 1 == player.x && _ghost.y == player.y)
		_isPlayerDead = true;
	else if (_ghost.x - 1 == player.x && _ghost.y == player.y)
		_isPlayerDead = true;
	if (target.r == 0 && target.g == 0 && target.b == 139) {
		return ERROR;
	} else {
		_ghost.x--;
		_direction = LEFT_ARROW;
		return SUCCESS;
	}
}

int Arcade::IAGhost::goDown(std::vector<Arcade::Pixel> &screen,
	Arcade::Pixel player)
{
	Color target;

	target = screen[calcPos(_ghost.y, _ghost.x + 1)].color;
	if (_ghost.x + 1 == player.x && _ghost.y + 1 == player.y)
		_isPlayerDead = true;
	else if (_ghost.x + 1 == player.x && _ghost.y + 1 == player.y)
		_isPlayerDead = true;
	if (target.r == 0 && target.g == 0 && target.b == 139) {
		return ERROR;
	} else {
		_ghost.x++;
		_direction = RIGHT_ARROW;
		return SUCCESS;
	}
}

void Arcade::IAGhost::goUpLeft(Arcade::Pixel player,
	std::vector<Arcade::Pixel> &screen)
{
	int random = rand() % 2;

	if (random == 0) {
		if (goLeft(screen, player) == ERROR)
			goUp(screen, player);
	} else if (random == 1) {
		if (goUp(screen, player) == ERROR)
			goLeft(screen, player);
	}
}

void Arcade::IAGhost::goUpRight(Arcade::Pixel player,
	std::vector<Arcade::Pixel> &screen)
{
	int random = rand() % 2;

	if (random == 1) {
		if (goRight(screen, player) == ERROR)
			goUp(screen, player);
	} else if (random == 0) {
		if (goUp(screen, player) == ERROR)
			goRight(screen, player);
	}
}

void Arcade::IAGhost::goDownLeft(Arcade::Pixel player,
	std::vector<Arcade::Pixel> &screen)
{
	int random = rand() % 2;

	if (random == 1) {
		if (goLeft(screen, player) == ERROR)
			goDown(screen, player);
	} else if (random == 0) {
		if (goDown(screen, player) == ERROR)
			goLeft(screen, player);
	}
}

void Arcade::IAGhost::goDownRight(Arcade::Pixel player,
	std::vector<Arcade::Pixel> &screen)
{
	int random = rand() % 2;

	if (random == 1) {
		if (goRight(screen, player) == ERROR)
			goDown(screen, player);
	} else if (random == 0) {
		if (goDown(screen, player) == ERROR)
			goRight(screen, player);
	}
}

void Arcade::IAGhost::update(Arcade::Pixel player,
	std::vector<Arcade::Pixel> &screen, bool eating)
{
	if (rand() % 2 == 0 && eating)
		return;
	if (!eating) {
		if (player.y <= _ghost.y && player.x <= _ghost.x)
			goUpLeft(player, screen);
		else if (player.y < _ghost.y && player.x > _ghost.x)
			goDownLeft(player, screen);
		else if (player.y > _ghost.y && player.x < _ghost.x)
			goUpRight(player, screen);
		else
			goDownRight(player, screen);
	} else {
		if (player.y <= _ghost.y && player.x <= _ghost.x)
			goDownRight(player, screen);
		else if (player.y < _ghost.y && player.x > _ghost.x)
			goUpRight(player, screen);
		else if (player.y > _ghost.y && player.x < _ghost.x)
			goDownLeft(player, screen);
		else
			goUpLeft(player, screen);
	}
}

const Arcade::Pixel &Arcade::IAGhost::getGhost() const
{
	return _ghost;
}

void Arcade::IAGhost::setSprite(const std::string &sprite)
{
	this->_ghost.pathSprite = sprite;
}

void Arcade::IAGhost::setGhost(const Arcade::Pixel &ghost)
{
	_ghost = ghost;
}

bool Arcade::IAGhost::isPlayerDead()
{
	return _isPlayerDead;
}

Arcade::IAGhost::IAGhost() = default;

Arcade::IAGhost::~IAGhost() = default;