/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#ifndef CPP_ARCADE_IAGOSHT_HPP
#define CPP_ARCADE_IAGOSHT_HPP

#include "Core/Core.hpp"

#define SUCCESS 0
#define ERROR 1

namespace Arcade {
	class IAGhost {
	public:
		IAGhost();
		IAGhost(Color color, unsigned int x, unsigned int y,
			const std::string &pathSprite);
		~IAGhost();
		void update(Arcade::Pixel player,
			std::vector<Arcade::Pixel> &_screen, bool eating);
		const Arcade::Pixel &getGhost() const;
		void setGhost(const Pixel &ghost);
		void setSprite(const std::string &sprite);
		bool isPlayerDead();
	private:
		Input _direction;
		Arcade::Pixel _ghost;
		Color _under;
		bool _isPlayerDead;

		int goRight(std::vector<Arcade::Pixel> &screen,
			Arcade::Pixel player);
		int goLeft(std::vector<Arcade::Pixel> &screen,
			Arcade::Pixel player);
		int goDown(std::vector<Arcade::Pixel> &screen,
			Arcade::Pixel player);
		int goUp(std::vector<Arcade::Pixel> &screen,
			Arcade::Pixel player);
		void goUpLeft(Pixel player, std::vector<Pixel> &screen);
		void goUpRight(Pixel player, std::vector<Pixel> &screen);
		void goDownLeft(Pixel player, std::vector<Pixel> &screen);
		void goDownRight(Pixel player, std::vector<Pixel> &screen);
	};
}

#endif //CPP_ARCADE_IAGOSHT_HPP
