#include "Bot.h"

const int LEVEL_TWO_BOT_START_X = 620;
const int LEVEL_TWO_BOT_START_Y = 500;

Bot::Bot(BotType color, sf::Texture& texture)
{
	_sprite.setTexture(texture);
	_direction = Direction::LEFT;

	switch (color) {
	case Red:
		_sprite.setTextureRect(sf::IntRect(64, 64, 16, 16));
	case Pink:
		_sprite.setTextureRect(sf::IntRect(64, 80, 16, 16));
	case Blue:
		_sprite.setTextureRect(sf::IntRect(64, 96, 16, 16));
	case Orange:
		_sprite.setTextureRect(sf::IntRect(64, 112, 16, 16));
	}

	_sprite.setScale(2, 2);
	_pos.x  = LEVEL_TWO_BOT_START_X;
	_pos.x  = LEVEL_TWO_BOT_START_Y;
	_health = 1;
}

void Bot::Update(Map& map,  float time)
{
	Direction lastDirection = _direction;
	sf::FloatRect rect      = this->_sprite.getGlobalBounds();
	time                   /= 400;
	float botSpeed          = 0.08;
	std::vector<Direction> availableDirections;

	sf::FloatRect botRect = this->getSprite().getGlobalBounds();

	botRect.top -= 2;
	if (map.isAvailableZone(botRect)) {
		availableDirections.push_back(Direction::UP);
	}
	botRect.top += 4;
	if (map.isAvailableZone(botRect))
	{
		availableDirections.push_back(Direction::DOWN);
	}
	botRect.top -= 2;
	botRect.left += 2;
	if (map.isAvailableZone(botRect)) {
		availableDirections.push_back(Direction::RIGHT);
	}
	botRect.left -= 4;
	if (map.isAvailableZone(botRect)) {
		availableDirections.push_back(Direction::LEFT);
	}

	if (availableDirections.size() > 1) {
		int directionCount  = availableDirections.size();
		int randomDirection = rand() % (directionCount + 1) + 1;
		if (randomDirection > directionCount)
			_direction = availableDirections[randomDirection - 2];
		else if (randomDirection = directionCount)
			_direction = availableDirections[randomDirection - 1];
	}
	else if (availableDirections.size() == 1) {
		if (_direction == Direction::LEFT)       _direction == Direction::RIGHT;
		else if (_direction == Direction::RIGHT) _direction == Direction::LEFT;
		else if (_direction == Direction::UP)    _direction == Direction::DOWN;
		else if (_direction == Direction::DOWN)  _direction == Direction::UP;
	}

	_lastDirections = availableDirections;
	sf::Vector2f updated_pos = this->_pos;

	switch (_direction) {
	case Direction::RIGHT:
		_sprite.setTextureRect(sf::IntRect(0, _sprite.getTextureRect().top, 16, 16));
		updated_pos.x += botSpeed * time + 0.15;
		_sprite.setPosition(updated_pos);
		break;

	case Direction::LEFT:
		_sprite.setTextureRect(sf::IntRect(32, _sprite.getTextureRect().top, 16, 16));
		updated_pos.x -= botSpeed * time + 0.15;
		_sprite.setPosition(updated_pos);
		break;

	case Direction::UP:
		_sprite.setTextureRect(sf::IntRect(64, _sprite.getTextureRect().top, 16, 16));
		updated_pos.y -= botSpeed * time + 0.15;
		_sprite.setPosition(updated_pos);
		break;

	case Direction::DOWN:
		_sprite.setTextureRect(sf::IntRect(96, _sprite.getTextureRect().top, 16, 16));
		updated_pos.y += botSpeed * time + 0.15;
		_sprite.setPosition(updated_pos);
		break;
	}

	_pos = updated_pos;
}

std::vector<Direction> Bot::getAvailableDirection(Map map)
{                                                                               
	sf::FloatRect botRect = this->_sprite.getGlobalBounds();
	botRect.top -= 1.5;
	std::vector<Direction> availableDirection;
	//if (!map.isAvailableZone(botRect)) {
	botRect.left += 2;
	//}
	//botRect.top -= 1.5;
	//if (map.isAvailableZone(botRect)) 
	//{
	//	availableDirection.push_back(Direction::UP);
	//}
	//botRect.top += 3;
	//if (map.isAvailableZone(botRect)) 
	//{
	//	availableDirection.push_back(Direction::DOWN);
	//}
	//botRect.top -= 1.5;
	//botRect.left += 1.5;
	//if (map.isAvailableZone(botRect))
	//{
	//	availableDirection.push_back(Direction::RIGHT);
	//}
	//botRect.left -= 3;
	//if (map.isAvailableZone(botRect)) 
	//{
	//	availableDirection.push_back(Direction::LEFT);
	//}
	return availableDirection;
}
