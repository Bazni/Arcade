/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** 
*/

#ifndef CPP_ARCADE_SOLARFOX_HPP
#define CPP_ARCADE_SOLARFOX_HPP

#include <Games/IGame.hpp>

namespace Arcade {
	class SolarFox : public IGame {
	public:
		using Cooldown = unsigned char;
		typedef enum {
			NOT_PARALYZED = 0,
			RECOVERING = 255
		} CooldownTimer;

		typedef enum {
			SPAWNED,
			LIVING,
			PARALYZED,
			DYING
		} Status;

		typedef enum {
			LEFT,
			RIGHT,
			UP,
			DOWN
		} Side;

		typedef enum {
			PLAYER,
			ENEMY,
			PLAYER_GUNSHOT,
			ENEMY_GUNSHOT,
			POWERUP
		} EntityType;

		typedef struct {
			unsigned int x;
			unsigned int y;
			EntityType type;
			Status status;
			Side side;
			Side movingSide;
			Cooldown cooldown;
		} Entity;

		SolarFox();
		virtual ~SolarFox();

		std::string getName();
		std::vector<std::vector<Arcade::Pixel>>	getScreenLayers();
		std::string getBackground();
		std::string getSoundEffect();
		void sendInput(Arcade::Input input);
		void update();
		std::pair<unsigned int, unsigned int> getRes() ;
		unsigned int getScore();
		bool isGameOver();
		void reset();
	private:
		void parseMap(unsigned char mapNbr);
		void deserialize(unsigned int x, unsigned int y, char pixel);
		void serializeEntities(std::vector<Pixel> &entities);
		bool canMove(unsigned int x, unsigned int y,
			Arcade::SolarFox::EntityType entityType);
		Arcade::SolarFox::Entity &getPlayerEntity();
		void processInputs(Arcade::SolarFox::Entity &player);
		void moveEntity(Arcade::SolarFox::Entity &entity);
		void spawnShipLaserEntity
			(const Arcade::SolarFox::Entity &player);
		void addEntity(Arcade::SolarFox::Entity entity);
		void sortEntities();
		void updateEntities();
		bool isCollision(const Entity &a, const Entity &b);
		void updateEntityCollision(Arcade::SolarFox::Entity &entity);
		void updateEnemy(Arcade::SolarFox::Entity &entity);
		void spawnEnemyLaserEntity(const Entity &enemy);
		void moveEnemy(Entity &entity);
		void gameOver();
		bool isWin();

		unsigned int _score;
		unsigned char _mapNumber;
		bool _gameOver;
		Arcade::Input _input;
		std::string _soundEffect;
		clock_t _playerClock;
		clock_t _entityClock;

		std::vector<Arcade::SolarFox::Entity> _entities;
		std::vector<Arcade::Pixel> _mainLayer;
	};

	static const std::string gamePath = "games/solarfox/";
	static const std::string gameAssetsPath = gamePath + "assets/";
	static const std::string backgroundPath = gameAssetsPath +
		"background.png";
	static constexpr unsigned int height = 31;
	static constexpr unsigned int width = 31;

	static constexpr auto sideToPath = []
		(Arcade::SolarFox::Side side) {
		switch (side) {
		case Arcade::SolarFox::Side::LEFT :
			return "left";
		case Arcade::SolarFox::Side::RIGHT :
			return "right";
		case Arcade::SolarFox::Side::UP :
			return "up";
		case Arcade::SolarFox::Side::DOWN :
			return "down";
		default :
			return "";
		}
	};
	static const auto entityToSprite = []
		(Arcade::SolarFox::EntityType type, Arcade::SolarFox::Side side,
			Arcade::SolarFox::Status status)
		-> std::string {
		switch (type) {
		case Arcade::SolarFox::EntityType::PLAYER :
			return gameAssetsPath + "ship"
				+ sideToPath(side) + ".png";
		case Arcade::SolarFox::EntityType::ENEMY :
			return gameAssetsPath + (status == SolarFox::PARALYZED ?
				"paralyzedenemy" : "enemy")
				+ sideToPath(side) + ".png";
		case Arcade::SolarFox::EntityType::POWERUP :
			return gameAssetsPath + "powerup.png";
		case Arcade::SolarFox::EntityType::PLAYER_GUNSHOT :
			return gameAssetsPath + "shiplaser"
				+ (side == Arcade::SolarFox::LEFT
				|| side == Arcade::SolarFox::RIGHT
				? "leftright" : "downup") + ".png";
		case Arcade::SolarFox::EntityType::ENEMY_GUNSHOT :
			return gameAssetsPath + "enemylaser"
				+ (side == Arcade::SolarFox::LEFT
				|| side == Arcade::SolarFox::RIGHT
				? "leftright" : "downup") + ".png";
		default :
			return "";
		}
	};

	//pixel lambdas
	static constexpr auto createPixel = []
		(unsigned int x, unsigned int y,
		Arcade::Color color, const std::string &spritePath)
		-> Arcade::Pixel {
		return {x, y, color, spritePath};
	};
	static const auto wallPixel = []
		(unsigned int x, unsigned int y) {
		return createPixel(x, y, {50, 50, 50, 0}, "");
	};
	static const auto backgroundPixel = []
		(unsigned int x, unsigned int y) {
		return createPixel(x, y, {0, 0, 0, 0}, "");
	};
	static const auto playerPixel = []
		(unsigned int x, unsigned int y, Arcade::SolarFox::Side side) {
		return createPixel(x, y, {255, 255, 255, 0},
			entityToSprite(Arcade::SolarFox::PLAYER, side,
				SolarFox::SPAWNED));
	};
	static const auto enemyPixel = []
		(unsigned int x, unsigned int y, Arcade::SolarFox::Side side,
			Arcade::SolarFox::Status status) {
		return createPixel(x, y, {255, 0, 0, 0},
			entityToSprite(Arcade::SolarFox::ENEMY, side, status));
	};
	static const auto powerUpPixel = []
		(unsigned int x, unsigned int y) {
		return createPixel(x, y, {255, 255, 0, 0},
			entityToSprite(Arcade::SolarFox::POWERUP,
			Arcade::SolarFox::UP, SolarFox::SPAWNED));
	};
	static const auto enemyGunShotPixel = []
		(unsigned int x, unsigned int y, Arcade::SolarFox::Side side) {
		return createPixel(x, y, {255, 0, 255, 255},
			entityToSprite(Arcade::SolarFox::ENEMY_GUNSHOT, side,
				SolarFox::SPAWNED));
	};
	static const auto playerGunShotPixel = []
		(unsigned int x, unsigned int y, Arcade::SolarFox::Side side) {
		return createPixel(x, y, {255, 0, 255, 0},
			entityToSprite(Arcade::SolarFox::PLAYER_GUNSHOT, side,
				SolarFox::SPAWNED));
	};

	//entity lambdas
	static constexpr auto createEntity = []
		(unsigned int x, unsigned int y,
		Arcade::SolarFox::EntityType type, Arcade::SolarFox::Side side,
			Arcade::SolarFox::Side movingSide)
		-> Arcade::SolarFox::Entity {
		return {x, y, type, SolarFox::SPAWNED, side, movingSide, 0};
	};
	static const auto playerEntity = []
		(unsigned int x, unsigned int y, Arcade::SolarFox::Side side) {
		return createEntity(x, y,
			Arcade::SolarFox::PLAYER, side, side);
	};
	static const auto enemyEntity = []
		(unsigned int x, unsigned int y, Arcade::SolarFox::Side side) {
		return createEntity(x, y,
			Arcade::SolarFox::ENEMY, side,
			side == SolarFox::LEFT || side == SolarFox::RIGHT ?
				static_cast<SolarFox::Side>(side + 2) :
				side == SolarFox::UP || side == SolarFox::DOWN ?
					static_cast<SolarFox::Side>(side - 2)
					: SolarFox::UP);
	};
	static const auto powerUpEntity = []
		(unsigned int x, unsigned int y) {
		return createEntity(x, y,
			SolarFox::POWERUP, SolarFox::UP, SolarFox::UP);
	};
	static const auto playerGunShotEntity = []
		(unsigned int x, unsigned int y, Arcade::SolarFox::Side side) {
		return createEntity(x, y,
			Arcade::SolarFox::PLAYER_GUNSHOT, side, side);
	};
	static const auto enemyGunShotEntity = []
		(unsigned int x, unsigned int y, Arcade::SolarFox::Side side) {
		return createEntity(x, y,
			Arcade::SolarFox::ENEMY_GUNSHOT, side, side);
	};
}

extern "C" void destroyGame(Arcade::IGame *game);
extern "C" Arcade::IGame *createGame();

#endif //CPP_ARCADE_SOLARFOX_HPP
