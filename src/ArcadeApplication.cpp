/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** ArcadeApplication
*/

#include <iostream>
#include <fstream>
#include <dirent.h>
#include "ArcadeApplication.hpp"

ArcadeApplication::ArcadeApplication(int argc, char **argv)
	:_libraryLoader(std::make_unique<Arcade::LibraryLoader>())
{
	if (argc != 2) {
		usage(argv[0]);
		exit(exit_failure);
	}

	auto fileName = std::string(argv[1]);
	_libraryLoader->loadLibrary(std::string(argv[1]));

	auto libraryToStart = getLibraries
		(fileName.substr(fileName.find_last_of("/\\") + 1));
	if (_libraries.empty()) {
		std::cerr << "No graphical libraries in lib/ !" << std::endl;
		exit(exit_failure);
	}

	getGames();
	if (_games.empty()) {
		std::cerr << "No game libraries in games/ !" << std::endl;
		exit(exit_failure);
	}

	_core = std::make_unique<Arcade::Core>
		(_libraries, _games, _musicLibrary, libraryToStart);
}

ArcadeApplication::~ArcadeApplication()
{
	for (auto handle : _handles) {
		_libraryLoader->closeLibrary(handle);
	}
}

void ArcadeApplication::launch()
{
	_core->coreLoop();
}

void ArcadeApplication::usage(const char *programName)
{
	std::cout << "USAGE:" << std::endl
		<< "\t" << programName << " library_to_start_with.so"
		<< std::endl << std::endl << "DESCRIPTION:" << std::endl
		<< "\tlibrary_to_start_with.so\t"
		<< "library used to start the Arcade (must be in lib/)"
		<< std::endl;
}

const std::vector<std::string> &ArcadeApplication::readDirectory
	(const std::string &folder)
{
	auto files = new std::vector<std::string>();

	DIR *dirp = opendir(folder.c_str());
	struct dirent *dp = readdir(dirp);

	while (dp != nullptr) {
		auto fileName = std::string(dp->d_name);
		if (fileName != ".." && fileName != "."
			&& fileName.substr(fileName.find_last_of('.') + 1)
			== "so")
			files->push_back(fileName);
		dp = readdir(dirp);
	}
	closedir(dirp);

	return *files;
}

unsigned int ArcadeApplication::getLibraries
	(const std::string &libraryNameToStart)
{
	auto libraryFiles = readDirectory("lib");
	uint libraryIndexToStart = 0;

	for (uint i = 0; i < libraryFiles.size(); i++) {
		auto libraryFile = libraryFiles.at(i);
		if (libraryNameToStart == libraryFile)
			libraryIndexToStart = i + 1;
		auto handle = _libraryLoader->loadLibrary("./lib/" + libraryFile);
		if (!_libraryLoader->isLibraryOfType(handle, "Library")) {
			std::cerr << libraryFile << " is not an Arcade library!"
				<< std::endl;
			exit(exit_failure);
		}
		_handles.push_back(handle);
		auto createLibraryFunction = _libraryLoader->getFunction
			(handle, "createLibrary");
		auto rawLibraryPointer = ((Arcade::ILibrary *(*)())
			createLibraryFunction)();
		std::shared_ptr<Arcade::ILibrary> wrapper(rawLibraryPointer,
			&nullDestructorILibrary);
		_libraries.push_back(wrapper);
		if (_libraryLoader->isLibraryOfType(handle, "Music")) {
			auto createMusicFunction = _libraryLoader->getFunction
				(handle, "createMusic");
			auto rawIMusicPointer = ((Arcade::IMusic *(*)())
				createMusicFunction)();
			_musicLibrary = std::shared_ptr<Arcade::IMusic>
				(rawIMusicPointer, &nullDestructorIMusic);
		}
	}

	if (libraryIndexToStart == 0) {
		std::cerr << "Library argument is not from the lib folder!"
			<< std::endl;
		exit(exit_failure);
	}

	return libraryIndexToStart - 1;
}

void ArcadeApplication::getGames()
{
	auto libraryFiles = readDirectory("games");

	for (const auto &libraryFile : libraryFiles) {
		auto handle = _libraryLoader->loadLibrary
			("games/" + libraryFile);
		if (!_libraryLoader->isLibraryOfType(handle, "Game")) {
			std::cerr << libraryFile << " is not an Arcade library!"
				<< std::endl;
			exit(exit_failure);
		}
		_handles.push_back(handle);
		auto createLibraryFunction = _libraryLoader->getFunction
			(handle, "createGame");
		auto rawGamePointer =
			((Arcade::IGame *(*)())createLibraryFunction)();
		std::shared_ptr<Arcade::IGame> wrapper(rawGamePointer,
			&nullDestructorIGame);
		_games.push_back(wrapper);
	}
}

void nullDestructorIGame(Arcade::IGame *game)
{
	(void)game;
}

void nullDestructorILibrary(Arcade::ILibrary *library)
{
	(void)library;
}

void nullDestructorIMusic(Arcade::IMusic *music)
{
	(void)music;
}