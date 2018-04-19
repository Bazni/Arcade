/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#include <dlfcn.h>
#include <iostream>
#include "LibraryLoader.hpp"

Arcade::LibraryLoader::LibraryLoader()
{
}

Arcade::LibraryLoader::~LibraryLoader()
{
}

void *Arcade::LibraryLoader::loadLibrary(std::string libraryPath)
{
	void *library = dlopen(libraryPath.c_str(), RTLD_NOW);

	if (library == nullptr) {
		std::cerr << dlerror() << std::endl;
		exit(84);
	}
	dlerror();
	return library;
}

void Arcade::LibraryLoader::closeLibrary(void *handle)
{
	dlclose(handle);
}

void *Arcade::LibraryLoader::getFunction(void *handle,
	std::string functionName)
{
	return dlsym(handle, functionName.c_str());
}

bool Arcade::LibraryLoader::isLibraryOfType
	(void *handle, const std::string &type)
{
	return getFunction(handle, "create" + type) != nullptr
		&& getFunction(handle, "destroy" + type) != nullptr;
}