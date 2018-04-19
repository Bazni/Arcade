/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#ifndef CPP_ARCADE_COLOR_HPP
#define CPP_ARCADE_COLOR_HPP

namespace Arcade {

	struct Color {
		bool operator==(const Arcade::Color &color) const {
			return this->r == color.r && this->g == color.g
				&& this->b == color.b && this->a == color.a;
		}
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};
}

#endif //CPP_ARCADE_COLOR_HPP
