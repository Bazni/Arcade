/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#ifndef CPP_ARCADE_HIGHSCOREMANAGER_HPP
#define CPP_ARCADE_HIGHSCOREMANAGER_HPP

#include <string>
#include <vector>
#include <unordered_map>

namespace Arcade {

	constexpr auto HIGHSCORE_FILE_PATH = "highscore";
	using Score = unsigned long;
	using HighScore = std::pair<std::string, Arcade::Score>;

	class HighScoreManager {
	public:
		HighScoreManager();
		~HighScoreManager();

		void loadHighScores();
		void saveHighScores();
		void saveHighScore(const std::string &game,
			const std::string &player, Arcade::Score score);
		const std::unordered_map<std::string, std::vector<HighScore>>
		&getHighScores();
	private:
		void loadHighScoresFromFile
			(const std::string &highScoreFilePath);
		void saveHighScoresToFile(const std::string &highScoreFilePath);
		bool cannotGoInHighScores(const std::string &game,
			const std::string &player, Arcade::Score score);

		std::unordered_map<std::string,	std::vector<HighScore>>
			_highScores;
	};
}

#endif
