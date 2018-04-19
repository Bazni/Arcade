/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Header of the Arcade Core
*/

#pragma once

#include <string>
#include "Color.hpp"

namespace Arcade {

	typedef struct {
		unsigned int x;
		unsigned int y;
		Arcade::Color color;
		std::string pathSprite;
	} Pixel;

	typedef struct {
		unsigned int x;
		unsigned int y;
		std::string text;
		bool underline;
	} Text;

	typedef enum {
		NO_INPUT = -1,
		ENTER,
		BACKSPACE,
		SPACE,
		ESCAPE,
		UP_ARROW,
		DOWN_ARROW,
		LEFT_ARROW,
		RIGHT_ARROW,
		A_KEY,
		B_KEY,
		C_KEY,
		D_KEY,
		E_KEY,
		F_KEY,
		G_KEY,
		H_KEY,
		I_KEY,
		J_KEY,
		K_KEY,
		L_KEY,
		M_KEY,
		N_KEY,
		O_KEY,
		P_KEY,
		Q_KEY,
		R_KEY,
		S_KEY,
		T_KEY,
		U_KEY,
		V_KEY,
		W_KEY,
		X_KEY,
		Y_KEY,
		Z_KEY,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		QUIT_EVENT
	} Input;
}

#include <vector>
#include <Libraries/IMusic.hpp>
#include "Libraries/ILibrary.hpp"
#include "Games/IGame.hpp"
#include "HighScoreManager.hpp"

namespace Arcade {
	class ILibrary;
	class IGame;

	class Core {
	public:
		Core(std::vector<std::shared_ptr<Arcade::ILibrary>> _libraries,
			std::vector<std::shared_ptr<Arcade::IGame>> _games,
			std::shared_ptr<Arcade::IMusic> musicLibrary,
			unsigned int libraryIndex);
		~Core();
		void coreLoop();
	private:
		void drawScreen
			(const std::vector<std::vector<Arcade::Pixel>> &layers,
				const std::pair<unsigned int, unsigned int>
				&res);
		void initLibrary();
		void changeLibrary(bool);
		void changeGame(bool);
		void handleGlobalKeyEvents(const Arcade::Input &input);
		void gameLoop(const Arcade::Input &input);
		void menuLoop(const Input &input);
		void handleMenuKeys(const Input &input);
		void handleGameKeys(const Input &input);
		void handlePlayerName(const Arcade::Input &input);
		void displayHighScores();
		void drawLibraries();

		Arcade::HighScoreManager _highScoreManager;

		std::vector<std::shared_ptr<Arcade::ILibrary>> _libraries;
		unsigned int _currentLibraryIndex;
		std::shared_ptr<Arcade::ILibrary> _currentLibrary;

		std::vector<std::shared_ptr<Arcade::IGame>> _games;
		unsigned int _currentGameIndex;
		std::shared_ptr<Arcade::IGame> _currentGame;

		std::shared_ptr<Arcade::IMusic> _musicLibrary;

		std::string _playerName;

		bool _exit;
		bool _pause;
		bool _menu;
	};
}