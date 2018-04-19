/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#include <iostream>
#include <caca.h>
#include <Core/Core.hpp>
#include <ncurses.h>
#include <fcntl.h>
#include "LibCaca.hpp"
#include "SFML.hpp"

extern "C" Arcade::ILibrary * createLibrary()
{
	return new Arcade::LibCaca();
}

extern "C" void destroyLibrary(Arcade::ILibrary *object)
{
	delete object;
}

Arcade::LibCaca::LibCaca() = default;

Arcade::LibCaca::~LibCaca() = default;

void Arcade::LibCaca::createWindow()
{
	_canvas = caca_create_canvas(275, 100);
	_display = caca_create_display(_canvas);
	if (_display == nullptr) {
		std::cerr << "LibCaca initialization error." << std::endl;
		exit(EXIT_FAILURE);
	}
	caca_set_display_title(_display, "Arcade -- LibCaca graphics");
}

void Arcade::LibCaca::destroyWindow()
{
	caca_free_display(_display);
	_display = nullptr;
	_canvas = nullptr;
}

Arcade::Input Arcade::LibCaca::getInput()
{
	caca_event_t	event;

	if (caca_get_event(_display, CACA_EVENT_KEY_PRESS, &event, 0) == 1)
		switch (caca_get_event_key_ch(&event)) {
		case CACA_KEY_UP :
			return Arcade::Input::UP_ARROW;
		case CACA_KEY_DOWN :
			return Arcade::Input::DOWN_ARROW;
		case CACA_KEY_LEFT :
			return Arcade::Input::LEFT_ARROW;
		case CACA_KEY_RIGHT :
			return Arcade::Input::RIGHT_ARROW;
		case CACA_KEY_ESCAPE :
			return Arcade::Input::ESCAPE;
		case CACA_KEY_RETURN :
			return Arcade::Input::ENTER;
		case CACA_KEY_BACKSPACE :
			return Arcade::Input::BACKSPACE;
		case ' ' :
			return Arcade::Input::SPACE;
		case 'a' :
			return Arcade::Input::A_KEY;
		case 'b' :
			return Arcade::Input::B_KEY;
		case 'c' :
			return Arcade::Input::C_KEY;
		case 'd' :
			return Arcade::Input::D_KEY;
		case 'e' :
			return Arcade::Input::E_KEY;
		case 'f' :
			return Arcade::Input::F_KEY;
		case 'g' :
			return Arcade::Input::G_KEY;
		case 'h' :
			return Arcade::Input::H_KEY;
		case 'i' :
			return Arcade::Input::I_KEY;
		case 'j' :
			return Arcade::Input::J_KEY;
		case 'k' :
			return Arcade::Input::K_KEY;
		case 'l' :
			return Arcade::Input::L_KEY;
		case 'm' :
			return Arcade::Input::M_KEY;
		case 'n' :
			return Arcade::Input::N_KEY;
		case 'o' :
			return Arcade::Input::O_KEY;
		case 'p' :
			return Arcade::Input::P_KEY;
		case 'q' :
			return Arcade::Input::Q_KEY;
		case 'r' :
			return Arcade::Input::R_KEY;
		case 's' :
			return Arcade::Input::S_KEY;
		case 't' :
			return Arcade::Input::T_KEY;
		case 'u' :
			return Arcade::Input::U_KEY;
		case 'v' :
			return Arcade::Input::V_KEY;
		case 'w' :
			return Arcade::Input::W_KEY;
		case 'x' :
			return Arcade::Input::X_KEY;
		case 'y' :
			return Arcade::Input::Y_KEY;
		case 'z' :
			return Arcade::Input::Z_KEY;
		case CACA_KEY_F1 :
			return Arcade::Input::F1;
		case CACA_KEY_F2 :
			return Arcade::Input::F2;
		case CACA_KEY_F3 :
			return Arcade::Input::F3;
		case CACA_KEY_F4 :
			return Arcade::Input::F4;
		case CACA_KEY_F5 :
			return Arcade::Input::F5;
		case CACA_KEY_F6 :
			return Arcade::Input::F6;
		case CACA_KEY_F7 :
			return Arcade::Input::F7;
		case CACA_KEY_F8 :
			return Arcade::Input::F8;
		case CACA_KEY_F9 :
			return Arcade::Input::F9;
		case CACA_KEY_F10 :
			return Arcade::Input::F10;
		case CACA_KEY_F11 :
			return Arcade::Input::F11;
		case CACA_KEY_F12 :
			return Arcade::Input::F12;
		default :
			return Arcade::Input::NO_INPUT;
		}
	return Arcade::Input::NO_INPUT;
}

void Arcade::LibCaca::putPixel(Arcade::Pixel pixel)
{
	if (pixel.color.a == 0)
		pixel.color.a = 255;
	uint16_t alpha = pixel.color.a << 12;
	uint16_t red = pixel.color.r << 8;
	uint16_t green = pixel.color.g << 4;
	uint16_t blue = pixel.color.b;
	uint16_t true_color = alpha | red | blue | green;
	caca_set_color_argb(_canvas, 0, true_color);
	caca_draw_box(_canvas, 275 / 2 - 31 + pixel.x,
		100 / 2 - 31 + pixel.y, 1, 1, ' ');
}

void Arcade::LibCaca::clear()
{
	caca_set_color_argb(_canvas, 0, 0);
	caca_clear_canvas(_canvas);
}

void Arcade::LibCaca::update()
{
	caca_refresh_display(_display);
}

void Arcade::LibCaca::sendScore(unsigned int score)
{
	_score = score;
}

void Arcade::LibCaca::drawUserInterface()
{
	caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);

	//top of game ui
	caca_put_str(_canvas, 107, 3, "Arcade -- LibCaca Graphics");
	caca_put_str(_canvas, 117, 10, _gameName.c_str());
	caca_printf(_canvas, 115, 11, "Score : %d", _score);

	//controls
	caca_set_attr(_canvas, CACA_UNDERLINE);
	caca_put_str(_canvas, 1, 40, "Controls :");
	caca_set_attr(_canvas, 0);
	caca_put_str(_canvas, 1, 41, "Press R to reset the game.");
	caca_put_str(_canvas, 1, 42, "Press P to pause the game.");
	caca_put_str(_canvas, 1, 43, "Press Escape to go back to the menu.");
	caca_put_str(_canvas, 1, 44, "Press F1 to quit Arcade.");
	caca_put_str(_canvas, 1, 45, "Press F3 to use the previous game.");
	caca_put_str(_canvas, 1, 46, "Press F4 to use the next game.");
	caca_put_str(_canvas, 1, 47, "Press F5 to use the previous library.");
	caca_put_str(_canvas, 1, 48, "Press F6 to use the next library.");
}

void Arcade::LibCaca::putText(const Arcade::Text &text)
{
	caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
	if (text.underline)
		caca_set_attr(_canvas, CACA_UNDERLINE);
	caca_put_str(_canvas, text.x * 3 - 8, text.y + 3, text.text.c_str());
	caca_set_attr(_canvas, 0);
}

void Arcade::LibCaca::sendName(const std::string &name)
{
	_gameName = name;
}

std::string Arcade::LibCaca::getLibraryName()
{
	return "LibCaca";
}
