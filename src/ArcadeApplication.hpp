/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Header of Arcade entry point
*/

#ifndef CPP_ARCADE_ARCADE_HPP
#define CPP_ARCADE_ARCADE_HPP

#include <memory>
#include "Core/Core.hpp"
#include "LibraryLoader.hpp"

constexpr int	exit_failure = 84;

class ArcadeApplication {
public:
	ArcadeApplication(int argc, char **argv);
	~ArcadeApplication();

	void launch();
	void usage(const char *programName);
private:

	unsigned int getLibraries(const std::string &libraryNameToStart);
	void getGames();
	const std::vector<std::string> &readDirectory
		(const std::string &folder);

	std::vector<void *> _handles;
	std::vector<std::shared_ptr<Arcade::IGame>> _games;
	std::vector<std::shared_ptr<Arcade::ILibrary>> _libraries;
	std::shared_ptr<Arcade::IMusic> _musicLibrary;
	std::unique_ptr<Arcade::Core> _core;
	std::unique_ptr<Arcade::LibraryLoader> _libraryLoader;
};

void nullDestructorIGame(Arcade::IGame *game);
void nullDestructorILibrary(Arcade::ILibrary *library);
void nullDestructorIMusic(Arcade::IMusic *music);

#endif
