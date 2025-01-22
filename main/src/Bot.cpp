#include "../head/Bot.h"
//#include "../head/Constants.h"

const int LEVEL_TWO_BOT_START_X = 624;
const int LEVEL_TWO_BOT_START_Y = 500;

auto createPathFromStartToEnd(Map& map, sf::FloatRect start, sf::FloatRect end)
{
	std::vector<sf::FloatRect> path;
	return path;
}

Bot::Bot(BotType color, sf::Texture& texture)
{
	_sprite.setTexture(texture);
	_direction = Direction::LEFT;

	switch (color) {
	case Red:
		_sprite.setTextureRect(sf::IntRect(32, 64, 16, 16));
	case Pink:
		_sprite.setTextureRect(sf::IntRect(32, 80, 16, 16));
	case Blue:
		_sprite.setTextureRect(sf::IntRect(32, 96, 16, 16));
	case Orange:
		_sprite.setTextureRect(sf::IntRect(32, 112, 16, 16));
	}

	_sprite.setScale(2, 2);
	_pos.x = LEVEL_TWO_BOT_START_X;
	_pos.y = LEVEL_TWO_BOT_START_Y;
	_health = 1;
	_size = sf::Vector2f(32, 32);
}

void Bot::Update(Map& map, float timeForMove, float timeForChBotDir)
{
	sf::FloatRect botRect = this->getSprite().getGlobalBounds();

	if (map.canDefinePacmanPos(botRect)) {
		auto playerPos = map.getPlayerRect();
		auto botPos = this->getSprite().getGlobalBounds();
		auto start = map.getIntersectNoZeroBlock(botPos);
		auto end = map.getIntersectNoZeroBlock(playerPos);
		auto path = createPathFromStartToEnd(map, start, end);

	}

	Direction lastDirection = _direction;
	sf::FloatRect rect = this->_sprite.getGlobalBounds();
	timeForMove /= 400;
	float botSpeed = 0.06;
	std::vector<Direction> availableDirections;

	botRect.top -= 0.5;
	if (map.isAvailableZone(botRect)) {
		availableDirections.push_back(Direction::UP);
	}
	botRect.top += 1;
	if (map.isAvailableZone(botRect)) {
		availableDirections.push_back(Direction::DOWN);
	}
	botRect.top -= 0.5;
	botRect.left += 0.5;
	if (map.isAvailableZone(botRect)) {
		availableDirections.push_back(Direction::RIGHT);
	}
	botRect.left -= 1;
	if (map.isAvailableZone(botRect)) {
		availableDirections.push_back(Direction::LEFT);
	}

	int max = availableDirections.size();
	int randNum = rand() % (max);
	sf::Vector2f updated_pos = this->_pos;

	if (timeForChBotDir > 3)
		_direction = availableDirections[randNum];

	switch (_direction) {
	case Direction::RIGHT:
		_sprite.setTextureRect(sf::IntRect(0, _sprite.getTextureRect().top, 16, 16));
		updated_pos.x += botSpeed * timeForMove;
		break;

	case Direction::LEFT:
		_sprite.setTextureRect(sf::IntRect(32, _sprite.getTextureRect().top, 16, 16));
		updated_pos.x -= botSpeed * timeForMove;
		break;

	case Direction::UP:
		_sprite.setTextureRect(sf::IntRect(64, _sprite.getTextureRect().top, 16, 16));
		updated_pos.y -= botSpeed * timeForMove;
		break;

	case Direction::DOWN:
		_sprite.setTextureRect(sf::IntRect(96, _sprite.getTextureRect().top, 16, 16));
		updated_pos.y += botSpeed * timeForMove;
		break;
	}

	sf::FloatRect updatedBotRect(updated_pos, this->getSize());
	if (!map.isAvailableZone(updatedBotRect)) {
		sf::FloatRect block = map.getIntersectZeroBlock(updatedBotRect);
		float intersect;
		if (_direction == Direction::RIGHT) {
			updated_pos.x = block.left - 32;
		}
		else if (_direction == Direction::LEFT) {
			updated_pos.x = block.left + 32;
		}
		else if (_direction == Direction::UP) {
			updated_pos.y = block.top + 32;
		}
		else if (_direction == Direction::DOWN) {
			updated_pos.y = block.top - 32;
		}
	}

	_sprite.setPosition(updated_pos);
	_lastPosition = updated_pos;
	_pos = updated_pos;
}

bool Bot::catchPlayer(Player* player)
{
	sf::FloatRect playerRect = player->getSprite().getGlobalBounds();
	playerRect.top += 12;
	playerRect.left += 12;
	playerRect.height -= 24;
	playerRect.width -= 24;

	if (this->getSprite().getGlobalBounds().intersects(playerRect))
		return true;

	return false;
}
