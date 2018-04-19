/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibraryLoader
*/

#ifndef CPP_ARCADE_LIBRARYLOADER_HPP
#define CPP_ARCADE_LIBRARYLOADER_HPP

#include <string>

namespace Arcade {
	class LibraryLoader {
	public:
		LibraryLoader();
		~LibraryLoader();

		void *loadLibrary(std::string libraryPath);
		void *getFunction(void *handle, std::string functionName);
		void closeLibrary(void *handle);
		bool isLibraryOfType(void *handle, const std::string &type);
	};
}

#endif //CPP_ARCADE_LIBRARYLOADER_HPP
