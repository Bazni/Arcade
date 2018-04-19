/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SFML
*/

#include <iostream>
#include <Core/Core.hpp>
#include <zconf.h>
#include "SFML.hpp"

extern "C" Arcade::ILibrary *createLibrary()
{
	return new Arcade::SFML();
}

extern "C" Arcade::IMusic *createMusic()
{
	return new Arcade::SFML();
}

extern "C" void destroyLibrary(Arcade::ILibrary *object)
{
	delete object;
}

extern "C" void destroyMusic(Arcade::IMusic *object)
{
	delete object;
}

Arcade::SFML::SFML() = default;

Arcade::SFML::~SFML() = default;

Arcade::Input Arcade::SFML::getInput()
{
	sf::Event event;

	if (!_window.pollEvent(event))
		return Arcade::Input::NO_INPUT;
	if (event.type == sf::Event::Closed)
		return (Arcade::Input::QUIT_EVENT);
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Left :
			return Arcade::Input::LEFT_ARROW;
		case sf::Keyboard::Right :
			return Arcade::Input::RIGHT_ARROW;
		case sf::Keyboard::Up :
			return Arcade::Input::UP_ARROW;
		case sf::Keyboard::Down :
			return Arcade::Input::DOWN_ARROW;
		case sf::Keyboard::Space :
			return Arcade::Input::SPACE;
		case sf::Keyboard::BackSpace :
			return Arcade::Input::BACKSPACE;
		case sf::Keyboard::Return :
			return Arcade::Input::ENTER;
		case sf::Keyboard::Escape :
			return Arcade::Input::ESCAPE;
		case sf::Keyboard::A :
			return Arcade::Input::A_KEY;
		case sf::Keyboard::B :
			return Arcade::Input::B_KEY;
		case sf::Keyboard::C :
			return Arcade::Input::C_KEY;
		case sf::Keyboard::D :
			return Arcade::Input::D_KEY;
		case sf::Keyboard::E :
			return Arcade::Input::E_KEY;
		case sf::Keyboard::F :
			return Arcade::Input::F_KEY;
		case sf::Keyboard::G :
			return Arcade::Input::G_KEY;
		case sf::Keyboard::H :
			return Arcade::Input::H_KEY;
		case sf::Keyboard::I :
			return Arcade::Input::I_KEY;
		case sf::Keyboard::J :
			return Arcade::Input::J_KEY;
		case sf::Keyboard::K :
			return Arcade::Input::K_KEY;
		case sf::Keyboard::L :
			return Arcade::Input::L_KEY;
		case sf::Keyboard::M :
			return Arcade::Input::M_KEY;
		case sf::Keyboard::N :
			return Arcade::Input::N_KEY;
		case sf::Keyboard::O :
			return Arcade::Input::O_KEY;
		case sf::Keyboard::P :
			return Arcade::Input::P_KEY;
		case sf::Keyboard::Q :
			return Arcade::Input::Q_KEY;
		case sf::Keyboard::R :
			return Arcade::Input::R_KEY;
		case sf::Keyboard::S :
			return Arcade::Input::S_KEY;
		case sf::Keyboard::T :
			return Arcade::Input::T_KEY;
		case sf::Keyboard::U :
			return Arcade::Input::U_KEY;
		case sf::Keyboard::V :
			return Arcade::Input::V_KEY;
		case sf::Keyboard::W :
			return Arcade::Input::W_KEY;
		case sf::Keyboard::X :
			return Arcade::Input::X_KEY;
		case sf::Keyboard::Y :
			return Arcade::Input::Y_KEY;
		case sf::Keyboard::Z :
			return Arcade::Input::Z_KEY;
		case sf::Keyboard::F1 :
			return Arcade::Input::F1;
		case sf::Keyboard::F2 :
			return Arcade::Input::F2;
		case sf::Keyboard::F3 :
			return Arcade::Input::F3;
		case sf::Keyboard::F4 :
			return Arcade::Input::F4;
		case sf::Keyboard::F5 :
			return Arcade::Input::F5;
		case sf::Keyboard::F6 :
			return Arcade::Input::F6;
		case sf::Keyboard::F7 :
			return Arcade::Input::F7;
		case sf::Keyboard::F8 :
			return Arcade::Input::F8;
		case sf::Keyboard::F9 :
			return Arcade::Input::F9;
		case sf::Keyboard::F10 :
			return Arcade::Input::F10;
		case sf::Keyboard::F11 :
			return Arcade::Input::F11;
		case sf::Keyboard::F12 :
			return Arcade::Input::F12;
		default :
			return Arcade::Input::NO_INPUT;
		}
	}
	return (Arcade::Input::NO_INPUT);
}

void Arcade::SFML::putPixel(Arcade::Pixel pixel)
{
	if (pixel.pathSprite.empty()) {
		sf::RectangleShape shape(sf::Vector2f(21, 21));
		shape.setPosition(1920 / 2 - (21 * 31 / 2) + pixel.x * 21,
			1080 / 2 - (21 * 31 / 2) + pixel.y * 21);
		sf::Color sfmlColor(pixel.color.r, pixel.color.g,
			pixel.color.b, pixel.color.a);
		shape.setFillColor(sfmlColor);
		_window.draw(shape);
	} else {
		sf::Texture texture;
		texture.loadFromFile(pixel.pathSprite);
		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setPosition(1920 / 2 - (21 * 31 / 2) + pixel.x * 21,
			1080 / 2 - (21 * 31 / 2) + pixel.y * 21);
		_window.draw(sprite);
	}
}

void Arcade::SFML::clear()
{
	_window.clear(sf::Color::Black);
}

void Arcade::SFML::update()
{
	_window.display();
}

void Arcade::SFML::createWindow()
{
	_font.loadFromFile("lib/resources/visitor.ttf");
	_window.create(sf::VideoMode(1920, 1080),
		"Arcade - SFML graphics"
		, sf::Style::Resize | sf::Style::Close | sf::Style::Fullscreen);
	if (!_bgTexture.loadFromFile("lib/resources/background.png")) {
		exit(EXIT_FAILURE);
	}
	_bgSprite.setTexture(_bgTexture);
}

void Arcade::SFML::destroyWindow()
{
	_window.close();
}

void Arcade::SFML::drawBackground(const std::string &backgroundPath)
{
	if (backgroundPath.empty())
		return;
	sf::Texture texture;
	texture.loadFromFile(backgroundPath);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(1920 / 2 - (21 * 31 / 2),
		1080 / 2 - (21 * 31 / 2));
	_window.draw(sprite);
}

void Arcade::SFML::sendScore(unsigned int score)
{
	_score = score;
}

void Arcade::SFML::drawUserInterface()
{
	_window.draw(_bgSprite);
	putText({36, 3, "Arcade -- SFML Graphics", false});
	putText({42, 7, _gameName, false});
	putText({40, 8, std::string("Score : ") + std::to_string(_score),
		false});
}

void Arcade::SFML::putText(const Arcade::Text &string)
{
	sf::Text text(string.text, _font);
	text.setPosition(string.x * 21, string.y * 21);
	text.setCharacterSize(32);
	text.setFillColor(sf::Color::White);
	_window.draw(text);

	if (string.underline) {
		sf::RectangleShape underline(sf::Vector2f(
			(string.text.length() / 2 + string.text.length() / 4) *
				21, 1));
		underline.setPosition(string.x * 21, (string.y + 1) * 21 + 13);
		underline.setFillColor(sf::Color::White);
		_window.draw(underline);
	}
}

void Arcade::SFML::sendName(const std::string &name)
{
	_gameName = name;
}

void Arcade::SFML::cleanUnusedSounds()
{
	auto it = _soundQueue.begin();
	while (it != _soundQueue.end()) {
		if ((*it)->getStatus() == sf::Sound::Status::Stopped)
			it = _soundQueue.erase(it);
		else
			++it;
	}
}

void Arcade::SFML::playSound(const std::string &path, bool loop, float volume)
{
	cleanUnusedSounds();
	if (path.empty())
		return;
	//if buffer doesn't exist eg. if sample rate is 0
	if (_soundBuffer[path].getSampleRate() == 0)
		if (!_soundBuffer[path].loadFromFile(path)) {
			std::cerr << "Error loading " << path << std::endl;
			return;
		}
	auto sound = new sf::Sound(_soundBuffer[path]);
	sound->setLoop(loop);
	sound->setVolume(volume);
	sound->play();
	_soundQueue.emplace_back(std::unique_ptr<sf::Sound>(sound));
}

void Arcade::SFML::cleanSounds()
{
	_soundQueue.clear();
	_soundBuffer.clear();
}

std::string Arcade::SFML::getLibraryName()
{
	return "SFML";
}
