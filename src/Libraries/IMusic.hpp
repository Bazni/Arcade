/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Interface for musical libraries to the Core
*/

#pragma once

#include <string>

namespace Arcade {
	class IMusic {
	public:
		virtual void playSound
			(const std::string &path, bool loop, float volume) = 0;
		virtual void cleanSounds() = 0;
		virtual ~IMusic() = default;
	};
}