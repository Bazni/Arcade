/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Core class of the Arcade
*/

#include <iostream>
#include <utility>
#include "Core.hpp"

Arcade::Core::Core(std::vector<std::shared_ptr<Arcade::ILibrary>> libraries,
	std::vector<std::shared_ptr<Arcade::IGame>> games,
	std::shared_ptr<Arcade::IMusic> musicLibrary,
	unsigned int libraryIndex)
	: _libraries(std::move(libraries)), _currentLibraryIndex(libraryIndex),
	_currentLibrary(_libraries.at(_currentLibraryIndex)),
	_games(std::move(games)), _currentGameIndex(0),
	_currentGame(_games.at(_currentGameIndex)),
	_musicLibrary(std::move(musicLibrary)),
	_playerName("Carli"),
	_exit(false), _pause(false), _menu(true)
{
	initLibrary();
	_highScoreManager.loadHighScores();
}

Arcade::Core::~Core()
{
	_highScoreManager.saveHighScores();
}

void Arcade::Core::coreLoop()
{
	if (_musicLibrary)
		_musicLibrary->playSound("lib/resources/music.ogg", true, 10);
	while (!_exit) {
		auto input = _currentLibrary->getInput();
		handleGlobalKeyEvents(input);
		_currentLibrary->clear();
		_currentLibrary->drawUserInterface();
		if (_menu)
			menuLoop(input);
		else
			gameLoop(input);
		_currentLibrary->putText({3, 5, "Player Name : " + _playerName,
			false});
		drawLibraries();
		_currentLibrary->update();
	}
	_currentLibrary->destroyWindow();
	_musicLibrary->cleanSounds();
}

void Arcade::Core::menuLoop(const Arcade::Input &input)
{
	handleMenuKeys(input);
	handlePlayerName(input);
	for (unsigned int i = 0; i < _games.size(); ++i) {
		_currentLibrary->putText({42, 20 + i, _games[i]->getName(),
			i == _currentGameIndex});
	}
}

void Arcade::Core::handlePlayerName(const Arcade::Input &input)
{
	if (input >= A_KEY && input <= Z_KEY && _playerName.size() <= 20)
		_playerName += static_cast<char>('A') + input - A_KEY;
	if (input == BACKSPACE && !_playerName.empty())
		_playerName = _playerName.substr(0, _playerName.size() - 1);
}

void Arcade::Core::handleMenuKeys(const Arcade::Input &input)
{
	switch (input) {
	case DOWN_ARROW :
		changeGame(true);
		break;
	case UP_ARROW :
		changeGame(false);
		break;
	case ENTER :
		_menu = false;
		break;
	default :
		break;
	}
}

void Arcade::Core::handleGameKeys(const Arcade::Input &input)
{
	switch (input) {
	case F3 :
		changeGame(true);
		break;
	case F4 :
		changeGame(false);
		break;
	case P_KEY :
		_pause = !_pause;
		break;
	case R_KEY :
		_currentGame->reset();
		break;
	default :
		break;
	}
}

void Arcade::Core::gameLoop(const Arcade::Input &input)
{
	handleGameKeys(input);
	auto score = _currentGame->getScore();
	_currentLibrary->sendScore(score);
	_currentLibrary->drawBackground(_currentGame->getBackground());
	_currentGame->sendInput(input);
	if (_pause)
		_currentLibrary->putText({42, 5, "PAUSE!", false});
	else
		_currentGame->update();
	if (_currentGame->isGameOver())
		_highScoreManager.saveHighScore(_currentGame->getName(),
			_playerName, score);
	auto screen = _currentGame->getScreenLayers();
	drawScreen(screen, _currentGame->getRes());
	if (_musicLibrary)
		_musicLibrary->playSound(_currentGame->getSoundEffect(),
			false, 20);
	displayHighScores();
}

void Arcade::Core::initLibrary()
{
	_currentLibrary->createWindow();
	_currentLibrary->sendName(_currentGame->getName());
	_currentLibrary->sendScore(0);
}

void Arcade::Core::changeLibrary(bool leftToRight)
{
	if (_libraries.size() <= 1)
		return;
	_currentLibrary->destroyWindow();
	if (leftToRight)
		_currentLibraryIndex = static_cast<unsigned>
		((_currentLibraryIndex + 1) % _libraries.size());
	else
		_currentLibraryIndex = static_cast<unsigned>
		((_currentLibraryIndex - 1) % _libraries.size());
	_currentLibrary = _libraries[_currentLibraryIndex];
	initLibrary();
}

void Arcade::Core::drawScreen
	(const std::vector<std::vector<Arcade::Pixel>> &layers,
		const std::pair<unsigned int, unsigned int> &res)
{
	for (const auto &layer : layers) {
		for (const auto &pixel : layer)
			if (pixel.x < res.second)
				_currentLibrary->putPixel(pixel);
	}
}

void Arcade::Core::handleGlobalKeyEvents(const Arcade::Input &input)
{
	switch (input) {
	case QUIT_EVENT :
		_exit = true;
		break;
	case F1 :
		_exit = true;
		break;
	case ESCAPE :
		_menu = true;
		break;
	case F5 :
		changeLibrary(true);
		break;
	case F6 :
		changeLibrary(false);
		break;
	default :
		break;
	}
}

void Arcade::Core::changeGame(bool leftToRight)
{
	if (_games.size() <= 1)
		return;
	if (leftToRight)
		_currentGameIndex = static_cast<unsigned>
		((_currentGameIndex + 1) % _games.size());
	else
		_currentGameIndex = _currentGameIndex == 0 ?
			static_cast<unsigned>(_games.size() - 1)
			: static_cast<unsigned>
		((_currentGameIndex - 1) % _games.size());
	_currentGame = _games[_currentGameIndex];
	_currentLibrary->sendName(_currentGame->getName());
}

void Arcade::Core::displayHighScores()
{
	_currentLibrary->putText({3, 15, std::string("Highscores for ")
		+ _currentGame->getName() + " :", false});
	if (_highScoreManager.getHighScores().find(_currentGame->getName()) ==
		_highScoreManager.getHighScores().end())
		return;
	auto highScores = _highScoreManager.getHighScores()
		.at(_currentGame->getName());
	for (auto it = highScores.begin(); it != highScores.end(); ++it) {
		_currentLibrary->putText({3, static_cast<unsigned int>(16 +
					std::distance(highScores.begin(), it)),
			it->first + ": " + std::to_string(it->second), false});
	}
}

void Arcade::Core::drawLibraries()
{
	_currentLibrary->putText({3, 7, "Graphical Libraries :",
		false});
	for (auto it = _libraries.begin(); it != _libraries.end(); ++it) {
		_currentLibrary->putText({3, static_cast<unsigned int>(
			8 + std::distance(_libraries.begin(), it)),
			_currentLibrary == *it ? "> " + (*it)->getLibraryName()
				: (*it)->getLibraryName(), false});
	}
}
