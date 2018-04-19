/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Header of the Arcade Core
*/

#include <iostream>
#include <memory>
#include "ArcadeApplication.hpp"

int main(int argc, char **argv)
{
	auto arcade = std::make_unique<ArcadeApplication>(argc, argv);

	arcade->launch();
}