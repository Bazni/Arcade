/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <Core/Core.hpp>
#include "SDL.hpp"
#include "SFML.hpp"

extern "C" Arcade::ILibrary * createLibrary()
{
	return new Arcade::SDL();
}

extern "C" void destroyLibrary(Arcade::ILibrary *object)
{
	delete object;
}

Arcade::SDL::SDL() = default;

Arcade::SDL::~SDL() = default;

void Arcade::SDL::createWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL initialization failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	if (TTF_Init() != 0) {
		std::cerr << "SDL_ttf initialization failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	IMG_Init(IMG_INIT_PNG);
	_window = SDL_CreateWindow("Arcade -- SDL graphics",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1920, 1080, SDL_WINDOW_SHOWN);
	SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
	if (_window == nullptr) {
		std::cerr << "SDL window creation failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	_renderer = SDL_CreateRenderer(_window, -1,
		SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr) {
		std::cerr << "SDL renderer creation failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	_font = TTF_OpenFont("lib/resources/visitor.ttf", 200);
	_background = IMG_LoadTexture(_renderer,
		"lib/resources/background.png");
}

void Arcade::SDL::destroyWindow()
{
	SDL_DestroyTexture(_background);
	_background = nullptr;
	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;
	SDL_DestroyWindow(_window);
	_window = nullptr;
	TTF_CloseFont(_font);
	_font = nullptr;
	TTF_Quit();
	SDL_Quit();
}

Arcade::Input Arcade::SDL::getInput()
{
	SDL_Event event;

	if (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT)
			return (Arcade::Input::QUIT_EVENT);
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_RIGHT :
				return Arcade::Input::RIGHT_ARROW;
			case SDLK_LEFT :
				return Arcade::Input::LEFT_ARROW;
			case SDLK_DOWN :
				return Arcade::Input::DOWN_ARROW;
			case SDLK_UP :
				return Arcade::Input::UP_ARROW;
			case SDLK_ESCAPE :
				return Arcade::Input::ESCAPE;
			case SDLK_BACKSPACE :
				return Arcade::Input::BACKSPACE;
			case SDLK_RETURN :
				return Arcade::Input::ENTER;
			case SDLK_SPACE :
				return Arcade::Input::SPACE;
			case SDLK_a :
				return Arcade::Input::A_KEY;
			case SDLK_b :
				return Arcade::Input::B_KEY;
			case SDLK_c :
				return Arcade::Input::C_KEY;
			case SDLK_d :
				return Arcade::Input::D_KEY;
			case SDLK_e :
				return Arcade::Input::E_KEY;
			case SDLK_f :
				return Arcade::Input::F_KEY;
			case SDLK_g :
				return Arcade::Input::G_KEY;
			case SDLK_h :
				return Arcade::Input::H_KEY;
			case SDLK_i :
				return Arcade::Input::I_KEY;
			case SDLK_j :
				return Arcade::Input::J_KEY;
			case SDLK_k :
				return Arcade::Input::K_KEY;
			case SDLK_l :
				return Arcade::Input::L_KEY;
			case SDLK_m :
				return Arcade::Input::M_KEY;
			case SDLK_n :
				return Arcade::Input::N_KEY;
			case SDLK_o :
				return Arcade::Input::O_KEY;
			case SDLK_p :
				return Arcade::Input::P_KEY;
			case SDLK_q :
				return Arcade::Input::Q_KEY;
			case SDLK_r :
				return Arcade::Input::R_KEY;
			case SDLK_s :
				return Arcade::Input::S_KEY;
			case SDLK_t :
				return Arcade::Input::T_KEY;
			case SDLK_u :
				return Arcade::Input::U_KEY;
			case SDLK_v :
				return Arcade::Input::V_KEY;
			case SDLK_w :
				return Arcade::Input::W_KEY;
			case SDLK_x :
				return Arcade::Input::X_KEY;
			case SDLK_y :
				return Arcade::Input::Y_KEY;
			case SDLK_z :
				return Arcade::Input::Z_KEY;
			case SDLK_F1 :
				return Arcade::Input::F1;
			case SDLK_F2 :
				return Arcade::Input::F2;
			case SDLK_F3 :
				return Arcade::Input::F3;
			case SDLK_F4 :
				return Arcade::Input::F4;
			case SDLK_F5 :
				return Arcade::Input::F5;
			case SDLK_F6 :
				return Arcade::Input::F6;
			case SDLK_F7 :
				return Arcade::Input::F7;
			case SDLK_F8 :
				return Arcade::Input::F8;
			case SDLK_F9 :
				return Arcade::Input::F9;
			case SDLK_F10 :
				return Arcade::Input::F10;
			case SDLK_F11 :
				return Arcade::Input::F11;
			case SDLK_F12 :
				return Arcade::Input::F12;
			default :
				return Arcade::Input::NO_INPUT;
			}
		}
	}
	return Arcade::Input::NO_INPUT;
}

void Arcade::SDL::putPixel(Arcade::Pixel pixel)
{
	if (pixel.pathSprite.empty() && pixel.color.a != 0) {
		SDL_Rect rect;
		rect.x = 1920 / 2 - (21 * 31 / 2) + pixel.x * 21;
		rect.y = 1080 / 2 - (21 * 31 / 2) + pixel.y * 21;
		rect.h = 21;
		rect.w = 21;
		SDL_SetRenderDrawColor(_renderer, pixel.color.r, pixel.color.g,
			pixel.color.b, pixel.color.a);
		SDL_RenderFillRect(_renderer, &rect);
	} else {
		SDL_Rect rect;
		rect.x = 1920 / 2 - (21 * 31 / 2) + pixel.x * 21;
		rect.y = 1080 / 2 - (21 * 31 / 2) + pixel.y * 21;
		rect.h = 21;
		rect.w = 21;
		SDL_Texture *texture = IMG_LoadTexture(_renderer,
			pixel.pathSprite.c_str());
		SDL_RenderCopy(_renderer, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
	}
}

void Arcade::SDL::drawBackground(const std::string &backgroundPath)
{
	if (backgroundPath.empty())
		return;
	SDL_Rect rect;
	rect.x = 1920 / 2 - (21 * 31 / 2);
	rect.y = 1080 / 2 - (21 * 31 / 2);
	SDL_Texture *texture = IMG_LoadTexture(_renderer,
		backgroundPath.c_str());
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(_renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

void Arcade::SDL::clear()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
}

void Arcade::SDL::update()
{
	SDL_RenderPresent(_renderer);
}

void Arcade::SDL::sendScore(unsigned int score)
{
	_score = score;
}

void Arcade::SDL::drawUserInterface()
{
	//background
	SDL_Rect rect;
	rect.h = 1080;
	rect.w = 1920;
	rect.x = 0;
	rect.y = 0;
	SDL_RenderCopy(_renderer, _background, NULL, &rect);

	//draw text
	putText({36, 3, "Arcade -- SDL Graphics", false});
	putText({42, 7, _gameName, false});
	putText({40, 8, std::string("Score : ") + std::to_string(_score),
		false});
}

void Arcade::SDL::putText(const Arcade::Text &string)
{
	SDL_Color white = {255, 255, 255, 255};
	SDL_Surface *surfaceText = TTF_RenderText_Blended(_font,
		string.text.c_str(), white);
	SDL_Texture *text = SDL_CreateTextureFromSurface(_renderer,
		surfaceText);
	SDL_Rect rect;
	rect.x = string.x * 21;
	rect.y = string.y * 21;
	rect.w = string.text.length() * 15;
	rect.h = 24;
	SDL_RenderCopy(_renderer, text, NULL, &rect);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(surfaceText);

	if (string.underline) {
		SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
		for (unsigned int i = 0; i < string.text.length() / 2 +
			string.text.length() / 4; ++i) {
			for (int j = 0; j < 21; ++j) {
				SDL_RenderDrawPoint(_renderer,
					(string.x + i) * 21 + j,
					(string.y + 1) * 21);
			}
		}
	}
}

void Arcade::SDL::sendName(const std::string &name)
{
	_gameName = name;
}

std::string Arcade::SDL::getLibraryName()
{
	return "SDL";
}
