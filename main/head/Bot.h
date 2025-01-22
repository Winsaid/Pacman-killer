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

	void Update(Map map, float timeForMove, float timeForChBotDir);
	bool catchPlayer(Player* player);

private:
	sf::Vector2f _lastPosition;
};
