/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#pragma once

#include <vector>
#include <memory>
#include "Core/Core.hpp"

namespace Arcade {
	class IGame {
	public:
		virtual std::string getName() = 0;
		virtual std::vector<std::vector<Arcade::Pixel>>
		getScreenLayers() = 0;
		virtual std::string getBackground() = 0;
		virtual std::string getSoundEffect() = 0;
		virtual void sendInput(Arcade::Input input) = 0;
		virtual void update() = 0;
		virtual std::pair<unsigned int, unsigned int> getRes() = 0;
		virtual unsigned int getScore() = 0;
		virtual bool isGameOver() = 0;
		virtual void reset() = 0;
	};
}