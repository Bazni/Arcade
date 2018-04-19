/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include "SolarFox.hpp"

extern "C" Arcade::IGame *createGame()
{
	return new Arcade::SolarFox();
}

extern "C" void destroyGame(Arcade::IGame *game)
{
	delete dynamic_cast<Arcade::SolarFox *>(game);
}

Arcade::SolarFox::SolarFox() : _score(0), _gameOver(false)
{
	reset();
}

Arcade::SolarFox::~SolarFox() = default;

std::string Arcade::SolarFox::getName()
{
	return "SolarFox";
}

std::vector<std::vector<Arcade::Pixel>> Arcade::SolarFox::getScreenLayers()
{
	std::vector<std::vector<Arcade::Pixel>> layers;
	std::vector<Arcade::Pixel> entityLayer;

	serializeEntities(entityLayer);
	layers.push_back(_mainLayer);
	layers.push_back(entityLayer);
	return layers;
}

std::string Arcade::SolarFox::getBackground()
{
	return backgroundPath;
}

std::string Arcade::SolarFox::getSoundEffect()
{
	std::string soundEffect = _soundEffect;
	_soundEffect.clear();
	return soundEffect;
}

void Arcade::SolarFox::sendInput(Arcade::Input input)
{
	if (input != NO_INPUT)
		_input = input;
}

void Arcade::SolarFox::processInputs(Arcade::SolarFox::Entity &player)
{
	switch (_input) {
	case Arcade::Input::UP_ARROW :
		if (player.side != DOWN)
			player.side = player.movingSide = UP;
		break;
	case Arcade::Input::DOWN_ARROW :
		if (player.side != UP)
			player.side = player.movingSide = DOWN;
		break;
	case Arcade::Input::LEFT_ARROW :
		if (player.side != RIGHT)
			player.side = player.movingSide = LEFT;
		break;
	case Arcade::Input::RIGHT_ARROW :
		if (player.side != LEFT)
			player.side = player.movingSide = RIGHT;
		break;
	case Arcade::Input::SPACE :
		spawnShipLaserEntity(player);
	default :
		break;
	}
	_input = NO_INPUT;
}

void Arcade::SolarFox::moveEntity(Arcade::SolarFox::Entity &entity)
{
	switch (entity.movingSide) {
	case Arcade::SolarFox::UP :
		if (canMove(entity.x, entity.y - 1, entity.type))
			entity.y--;
		break;
	case Arcade::SolarFox::DOWN :
		if (canMove(entity.x, entity.y + 1, entity.type))
			entity.y++;
		break;
	case Arcade::SolarFox::LEFT :
		if (canMove(entity.x - 1, entity.y, entity.type))
			entity.x--;
		break;
	case Arcade::SolarFox::RIGHT :
		if (canMove(entity.x + 1, entity.y, entity.type))
			entity.x++;
		break;
	}
}

void Arcade::SolarFox::update()
{
	if (_gameOver) {
		reset();
		_gameOver = false;
		_score = 0;
	}
	if (isWin())
		reset();

	auto time = clock();
	float deltaTimePlayer = time - _playerClock;
	float deltaTimeEntity = time - _entityClock;

	if (deltaTimeEntity / CLOCKS_PER_SEC >= 0.05f) {
		_entityClock = time;
		updateEntities();
	}
	if (deltaTimePlayer / CLOCKS_PER_SEC >= 0.20f) {
		_playerClock = time;
		auto &player = getPlayerEntity();
		processInputs(player);
		moveEntity(player);
	}
}

std::pair<unsigned int, unsigned int> Arcade::SolarFox::getRes()
{
	return {height, width};
}

unsigned int Arcade::SolarFox::getScore()
{
	return _score;
}

bool Arcade::SolarFox::isGameOver()
{
	return _gameOver;
}

void Arcade::SolarFox::reset()
{
	_soundEffect.clear();
	_entities.clear();
	_input = Arcade::Input::NO_INPUT;
	_playerClock = _entityClock = clock();
	srand(time(nullptr));
	parseMap(1);
}

void Arcade::SolarFox::parseMap(unsigned char mapNbr)
{
	_mainLayer.clear();

	std::ifstream map(gamePath + std::to_string(mapNbr) + ".map");
	if (!map.is_open()) {
		std::cerr << "Error opening " << gamePath
			<< std::to_string(mapNbr) << ".map" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string line;
	for (unsigned int y = 0; std::getline(map, line); ++y) {
		for (unsigned int x = 0; x <= width; ++x)
			deserialize(x, y, line[x]);
	}
}

void Arcade::SolarFox::deserialize(unsigned int x, unsigned int y, char pixel)
{
	switch (pixel) {
	case ' ' :
		_mainLayer.push_back(backgroundPixel(x, y));
		break;
	case '#' :
		_mainLayer.push_back(wallPixel(x, y));
		break;
	case '*' :
		addEntity(powerUpEntity(x, y));
		_mainLayer.push_back(backgroundPixel(x, y));
		break;
	case 'E' :
		addEntity(enemyEntity(x, y,
			x == 0 ? Arcade::SolarFox::RIGHT :
			y == 0 ? Arcade::SolarFox::DOWN :
			x == width - 1 ? Arcade::SolarFox::LEFT :
			Arcade::SolarFox::UP));
		break;
	case 'P' :
		addEntity(playerEntity(x, y, Arcade::SolarFox::UP));
		_mainLayer.push_back(backgroundPixel(x, y));
		break;
	default :
		break;
	}
}

void Arcade::SolarFox::serializeEntities
	(std::vector<Arcade::Pixel> &entityLayer)
{
	sortEntities();
	for (const auto &entity : _entities) {
		switch (entity.type) {
		case PLAYER :
			entityLayer.push_back
				(playerPixel(entity.x, entity.y, entity.side));
			break;
		case ENEMY :
			entityLayer.push_back
				(enemyPixel(entity.x, entity.y, entity.side,
					entity.status));
			break;
		case POWERUP :
			entityLayer.push_back(powerUpPixel(entity.x, entity.y));
			break;
		case PLAYER_GUNSHOT :
			entityLayer.push_back(playerGunShotPixel
				(entity.x, entity.y, entity.side));
			break;
		case ENEMY_GUNSHOT :
			entityLayer.push_back(enemyGunShotPixel
				(entity.x, entity.y, entity.side));
			break;
		}
	}
}

bool Arcade::SolarFox::canMove(unsigned int x, unsigned int y,
	Arcade::SolarFox::EntityType entityType)
{
	if (entityType == Arcade::SolarFox::PLAYER_GUNSHOT
		|| entityType == Arcade::SolarFox::ENEMY
		|| entityType == Arcade::SolarFox::ENEMY_GUNSHOT)
		return x != (unsigned)-1 && y != (unsigned)-1
			&& x < width && y < height;
	return x != 0 && y != 0 && x < width - 1 && y < height - 1;
}

Arcade::SolarFox::Entity &Arcade::SolarFox::getPlayerEntity()
{
	for (auto &entity : _entities) {
		if (entity.type == Arcade::SolarFox::EntityType::PLAYER)
			return entity;
	}
	return _entities[0];
}

void Arcade::SolarFox::spawnShipLaserEntity
	(const Arcade::SolarFox::Entity &player)
{
	auto gunShotEntity = playerGunShotEntity(player.x, player.y,
		player.side);
	unsigned int x = gunShotEntity.x, y = gunShotEntity.y;

	moveEntity(gunShotEntity);
	if (gunShotEntity.x == x && gunShotEntity.y == y)
		return;
	addEntity(gunShotEntity);
}

void Arcade::SolarFox::addEntity(Arcade::SolarFox::Entity entity)
{
	_entities.push_back(entity);
}

void Arcade::SolarFox::sortEntities()
{
	std::sort(_entities.begin(), _entities.end(), []
		(const Arcade::SolarFox::Entity &a,
			const Arcade::SolarFox::Entity &b) {
		return a.type > b.type;
	});
}

void Arcade::SolarFox::updateEntities()
{
	auto it = _entities.begin();
	while (it != _entities.end()) {
		switch (it->type) {
		case Arcade::SolarFox::EntityType::PLAYER_GUNSHOT :
			moveEntity(*it);
			it->status = static_cast<Status>
			(it->status + 1);
			updateEntityCollision(*it);
			it = it->status >= DYING ? _entities.erase(it)
				: ++it;
			break;
		case Arcade::SolarFox::EntityType::ENEMY_GUNSHOT :
			moveEntity(*it);
			updateEntityCollision(*it);
			if (it->x == 0 || it->x == width - 1 || it->y == 0
				|| it->y == height - 1)
				it = _entities.erase(it);
			else
				++it;
			break;
		case Arcade::SolarFox::EntityType::ENEMY :
			updateEnemy(*it);
			++it;
			break;
		default :
			++it;
			break;
		}
	}
}

void Arcade::SolarFox::updateEntityCollision(Arcade::SolarFox::Entity &entity)
{
	auto it = _entities.begin();
	while (it != _entities.end())
		if (isCollision(entity, *it))
			switch (entity.type) {
			case Arcade::SolarFox::PLAYER_GUNSHOT :
				if (it->type != PLAYER)
					entity.status = DYING;
				if (it->type == ENEMY) {
					it->status = PARALYZED;
					_score += 1000;
					++it;
				}
				else if (it->type != PLAYER) {
					it = _entities.erase(it);
					_score += 100;
				}
				else
					++it;
				break;
			case Arcade::SolarFox::ENEMY_GUNSHOT :
				if (it->type == Arcade::SolarFox::PLAYER)
					gameOver();
				++it;
				break;
			default :
				break;
			}
		else
			++it;
}

bool Arcade::SolarFox::isCollision
	(const Arcade::SolarFox::Entity &a, const Arcade::SolarFox::Entity &b)
{
	return a.x == b.x && a.y == b.y && a.type != b.type;
}

void Arcade::SolarFox::updateEnemy(Arcade::SolarFox::Entity &entity)
{
	moveEnemy(entity);
	if (rand() % 50 == 0)
		spawnEnemyLaserEntity(entity);
}

void Arcade::SolarFox::moveEnemy(Arcade::SolarFox::Entity &entity)
{
	if (entity.cooldown == RECOVERING) {
		entity.cooldown = NOT_PARALYZED;
		entity.status = SPAWNED;
	}
	if (entity.status == PARALYZED) {
		entity.cooldown += 1;
		return;
	}
	if (entity.x == 0 && entity.movingSide == LEFT)
		entity.movingSide = RIGHT;
	else if (entity.x == width - 1 && entity.movingSide == RIGHT)
		entity.movingSide = LEFT;
	else if (entity.y == 0 && entity.movingSide == UP)
		entity.movingSide = DOWN;
	else if (entity.y == height - 1 && entity.movingSide == DOWN)
		entity.movingSide = UP;
	moveEntity(entity);
}

void Arcade::SolarFox::spawnEnemyLaserEntity
	(const Arcade::SolarFox::Entity &enemy)
{
	if ((enemy.x == 0 && (enemy.y == 0 || enemy.y == height - 1))
		|| (enemy.x == width - 1
		&& (enemy.y == 0 || enemy.y == height - 1)))
		return;
	auto gunShot = enemyGunShotEntity(enemy.x, enemy.y, enemy.side);
	moveEntity(gunShot);
	addEntity(gunShot);
}

void Arcade::SolarFox::gameOver()
{
	_gameOver = true;
}

bool Arcade::SolarFox::isWin()
{
	for (auto &entity : _entities)
		if (entity.type == POWERUP)
			return false;
	return true;
}