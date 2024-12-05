#pragma once

#include "Character.h"
#include "Map.h"
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

	void Update(Map &map, float time);
	std::vector<Direction> getAvailableDirection(Map map);

private:
	std::vector<Direction> _lastDirections;

};
