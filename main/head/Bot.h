#pragma once

#include "Character.h"
#include "Map.h"
#include "Player.h"
#include <vector>
#include <cstdlib>

enum BotType {
	Red,
	Pink,
	Blue,
	Orange
};

class Bot : public Character {
public:
	Bot(BotType color, sf::Texture &texture);

	void Update(Map &map, float timeForMove, float timeForChBotDir);
	bool catchPlayer(Player* player);
	void setMadModeSkin(sf::IntRect textureRect);
	void setBlue1();
	void setBlue2();
	void setWhite1();
	void setWhite2();
	int  getSecondsForMadMode() { return _clockForMadMode.getElapsedTime().asSeconds(); }
	void restartClock() { _clockForMadMode.restart(); }
	void setMadMode() { _madMode = true; this->restartClock(); }
	void unsetMadMode() { _madMode = false; }
	bool getMadMode() { return _madMode; }

private:
	sf::Vector2f _lastPosition;
	sf::Clock _clockForMadMode;
	bool _madMode = false;
};
