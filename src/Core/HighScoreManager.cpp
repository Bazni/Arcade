/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include "HighScoreManager.hpp"

Arcade::HighScoreManager::HighScoreManager() = default;

Arcade::HighScoreManager::~HighScoreManager() = default;

void Arcade::HighScoreManager::loadHighScoresFromFile
	(const std::string &highScoreFilePath)
{
	std::ifstream highScoreFile
		(highScoreFilePath, std::ios::in | std::ios::binary);

	if (!highScoreFile.is_open())
		return;
	Score score;
	std::string player;
	std::string game;
	while (highScoreFile >> game >> player >> score) {
		saveHighScore(game, player, score);
		score = 0;
		game.clear();
		player.clear();
	}
	highScoreFile.close();
}

void Arcade::HighScoreManager::loadHighScores()
{
	loadHighScoresFromFile(HIGHSCORE_FILE_PATH);
}

void Arcade::HighScoreManager::saveHighScoresToFile
	(const std::string &highScoreFilePath)
{
	std::ofstream highScoreFile(highScoreFilePath,
		std::ios::out | std::ios::trunc);

	if (!highScoreFile.is_open())
		return;
	for (const auto &game : _highScores) {
		for (const auto &score : game.second) {
			highScoreFile << game.first << " " << score.first
				<< " " << score.second << std::endl;
		}
	}
	highScoreFile.close();
}

void Arcade::HighScoreManager::saveHighScore(const std::string &game,
	const std::string &player, Arcade::Score score)
{
	if (cannotGoInHighScores(game, player, score))
		return;
	if (_highScores[game].size() == 10)
		_highScores[game].erase(_highScores[game].end());
	_highScores[game].emplace_back(std::make_pair(player, score));
	std::sort(_highScores[game].begin(), _highScores[game].end(),
		[](const Arcade::HighScore &a, const Arcade::HighScore &b) {
		return a.second > b.second;
	});
}

void Arcade::HighScoreManager::saveHighScores()
{
	saveHighScoresToFile(HIGHSCORE_FILE_PATH);
}

const std::unordered_map<std::string, std::vector<Arcade::HighScore>>
&Arcade::HighScoreManager::getHighScores()
{
	return _highScores;
}

bool Arcade::HighScoreManager::cannotGoInHighScores(const std::string &game,
	const std::string &player, Arcade::Score score)
{
	return game.empty() || player.empty() || score == 0 ||
		(_highScores[game].size() == 10 &&
			_highScores[game].end()->second > score);
}
