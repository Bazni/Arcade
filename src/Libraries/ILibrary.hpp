/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Interface for graphical libraries to the Core
*/

#pragma once

#include "Core/Core.hpp"

namespace Arcade {
	class ILibrary {
	public:
		virtual Arcade::Input getInput() = 0;
		virtual void putPixel(Arcade::Pixel pixel) = 0;
		virtual void drawBackground(const std::string &backgroundPath)
		= 0;
		virtual void sendScore(unsigned int score) = 0;
		virtual void sendName(const std::string &name) = 0;
		virtual void drawUserInterface() = 0;
		virtual void putText(const Arcade::Text &text) = 0;
		virtual void clear() = 0;
		virtual void update() = 0;
		virtual void createWindow() = 0;
		virtual void destroyWindow() = 0;
		virtual std::string getLibraryName() = 0;
		virtual ~ILibrary() = default;
	};
}
