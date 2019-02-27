/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#include "Allegro.hpp"
#include "SFML.hpp"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <Core/Core.hpp>
#include <iostream>

extern "C" Arcade::ILibrary * createLibrary()
{
	return new Arcade::Allegro();
}

extern "C" void destroyLibrary(Arcade::ILibrary *object)
{
	delete object;
}

Arcade::Allegro::Allegro()
{
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
}

Arcade::Allegro::~Allegro()
{
	al_uninstall_system();
}

void Arcade::Allegro::createWindow()
{
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	_display = al_create_display(1920, 1080);
	al_set_window_title(_display, "Arcade -- Allegro Graphics");
	_eventKeyboardQueue = al_create_event_queue();
	al_register_event_source(_eventKeyboardQueue,
		al_get_keyboard_event_source());
	_eventWindowQueue = al_create_event_queue();
	al_register_event_source(_eventWindowQueue,
		al_get_display_event_source(_display));
	_background = al_load_bitmap("lib/resources/background.png");
	_font = al_load_ttf_font("lib/resources/visitor.ttf", 32, 0);
}

void Arcade::Allegro::destroyWindow()
{
	al_destroy_display(_display);
	_display = nullptr;
	al_destroy_event_queue(_eventKeyboardQueue);
	_eventKeyboardQueue = nullptr;
	al_destroy_event_queue(_eventWindowQueue);
	_eventWindowQueue = nullptr;
	al_destroy_bitmap(_background);
	_background = nullptr;
	al_destroy_font(_font);
	_font = nullptr;
}

Arcade::Input Arcade::Allegro::getRawInput()
{
	//al_clear_keyboard_state(_display);

	ALLEGRO_EVENT event;
	if (al_get_next_event(_eventWindowQueue, &event) &&
		event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			return Arcade::Input::QUIT_EVENT;
	if (al_get_next_event(_eventKeyboardQueue, &event)) {
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_BACKSPACE :
				return Arcade::Input::BACKSPACE;
			case ALLEGRO_KEY_A :
				return Arcade::Input::A_KEY;
			case ALLEGRO_KEY_B :
				return Arcade::Input::B_KEY;
			case ALLEGRO_KEY_C :
				return Arcade::Input::C_KEY;
			case ALLEGRO_KEY_D :
				return Arcade::Input::D_KEY;
			case ALLEGRO_KEY_E :
				return Arcade::Input::E_KEY;
			case ALLEGRO_KEY_F :
				return Arcade::Input::F_KEY;
			case ALLEGRO_KEY_G :
				return Arcade::Input::G_KEY;
			case ALLEGRO_KEY_H :
				return Arcade::Input::H_KEY;
			case ALLEGRO_KEY_I :
				return Arcade::Input::I_KEY;
			case ALLEGRO_KEY_J :
				return Arcade::Input::J_KEY;
			case ALLEGRO_KEY_K :
				return Arcade::Input::K_KEY;
			case ALLEGRO_KEY_L :
				return Arcade::Input::L_KEY;
			case ALLEGRO_KEY_M :
				return Arcade::Input::M_KEY;
			case ALLEGRO_KEY_N :
				return Arcade::Input::N_KEY;
			case ALLEGRO_KEY_O :
				return Arcade::Input::O_KEY;
			case ALLEGRO_KEY_P :
				return Arcade::Input::P_KEY;
			case ALLEGRO_KEY_Q :
				return Arcade::Input::Q_KEY;
			case ALLEGRO_KEY_R :
				return Arcade::Input::R_KEY;
			case ALLEGRO_KEY_S :
				return Arcade::Input::S_KEY;
			case ALLEGRO_KEY_T :
				return Arcade::Input::T_KEY;
			case ALLEGRO_KEY_U :
				return Arcade::Input::U_KEY;
			case ALLEGRO_KEY_V :
				return Arcade::Input::V_KEY;
			case ALLEGRO_KEY_W :
				return Arcade::Input::W_KEY;
			case ALLEGRO_KEY_X :
				return Arcade::Input::X_KEY;
			case ALLEGRO_KEY_Y :
				return Arcade::Input::Y_KEY;
			case ALLEGRO_KEY_Z :
				return Arcade::Input::Z_KEY;
			default :
				break;
			}
		}
		switch (event.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE :
			return Arcade::Input::ESCAPE;
		case ALLEGRO_KEY_ENTER :
			return Arcade::Input::ENTER;
		case ALLEGRO_KEY_SPACE :
			return Arcade::Input::SPACE;
		case ALLEGRO_KEY_BACKSPACE :
			return Arcade::Input::BACKSPACE;
		case ALLEGRO_KEY_UP :
			return Arcade::Input::UP_ARROW;
		case ALLEGRO_KEY_DOWN :
			return Arcade::Input::DOWN_ARROW;
		case ALLEGRO_KEY_RIGHT :
			return Arcade::Input::RIGHT_ARROW;
		case ALLEGRO_KEY_LEFT :
			return Arcade::Input::LEFT_ARROW;
		case ALLEGRO_KEY_F1 :
			return Arcade::Input::F1;
		case ALLEGRO_KEY_F2 :
			return Arcade::Input::F2;
		case ALLEGRO_KEY_F3 :
			return Arcade::Input::F3;
		case ALLEGRO_KEY_F4 :
			return Arcade::Input::F4;
		case ALLEGRO_KEY_F5 :
			return Arcade::Input::F5;
		case ALLEGRO_KEY_F6 :
			return Arcade::Input::F6;
		case ALLEGRO_KEY_F7 :
			return Arcade::Input::F7;
		case ALLEGRO_KEY_F8 :
			return Arcade::Input::F8;
		case ALLEGRO_KEY_F9 :
			return Arcade::Input::F9;
		case ALLEGRO_KEY_F10 :
			return Arcade::Input::F10;
		case ALLEGRO_KEY_F11 :
			return Arcade::Input::F11;
		case ALLEGRO_KEY_F12 :
			return Arcade::Input::F12;
		default:
			return Arcade::Input::NO_INPUT;
		}
	}
	return Arcade::Input::NO_INPUT;
}

void Arcade::Allegro::putPixel(Arcade::Pixel pixel)
{
	if (!pixel.pathSprite.empty()) {
		ALLEGRO_BITMAP *sprite =
			al_load_bitmap(pixel.pathSprite.c_str());
		al_draw_bitmap(sprite, 1920 / 2 - (21 * 31 / 2) + pixel.x * 21,
			1080 / 2 - (21 * 31 / 2) + pixel.y * 21, 0);
		al_destroy_bitmap(sprite);
	}
}

void Arcade::Allegro::drawBackground(const std::string &backgroundPath)
{
	if (backgroundPath.empty())
		return;
	ALLEGRO_BITMAP *bg = al_load_bitmap(backgroundPath.c_str());
	al_draw_bitmap(bg, 1920 / 2 - (21 * 31 / 2),
		1080 / 2 - (21 * 31 / 2), 0);
	al_destroy_bitmap(bg);
}

void Arcade::Allegro::sendScore(unsigned int score)
{
	_score = score;
}

void Arcade::Allegro::drawUserInterface()
{
	al_draw_bitmap(_background, 0, 0, 0);
	putText({35, 3, "Arcade -- Allegro Graphics", false});
	putText({42, 7, _gameName, false});
	putText({40, 8, std::string("Score : ") + std::to_string(_score),
		false});
}

void Arcade::Allegro::sendName(const std::string &name)
{
	_gameName = name;
}

void Arcade::Allegro::clear()
{
	al_clear_to_color(al_map_rgba(0, 0, 0, 255));
}

void Arcade::Allegro::update()
{
	al_flip_display();
}

void Arcade::Allegro::putText(const Arcade::Text &text)
{
	al_draw_text(_font, al_map_rgba(255, 255, 255, 255), text.x * 21,
		text.y * 21, 0, text.text.c_str());
	if (text.underline) {
		for (unsigned int i = 0; i <
			text.text.length() / 2 + text.text.length() / 5; ++i) {
			for (int j = 0; j < 21; ++j) {
				al_draw_pixel((text.x + i) * 21 + j,
					(text.y + 1) * 21,
					al_map_rgba(255, 255, 255, 255));
			}
		}
	}
}

std::string Arcade::Allegro::getLibraryName()
{
	return "Allegro";
}

Arcade::Input Arcade::Allegro::getInput()
{
	static int cooldown = 0;
	static Arcade::Input input = NO_INPUT;
	Arcade::Input rawInput = getRawInput();

	if (rawInput == NO_INPUT)
		return NO_INPUT;
	if (rawInput == input && cooldown == 5) {
		cooldown = 0;
		input = rawInput;
	} else if (rawInput != input) {
		input = rawInput;
	} else {
		cooldown += 1;
		return NO_INPUT;
	}
	return input;
}
