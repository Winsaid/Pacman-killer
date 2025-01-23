#include "../head/Bot.h"

const int LEVEL_TWO_BOT_START_X = 686;
const int LEVEL_TWO_BOT_START_Y = 308;

const int LEVEL_ZERO_BOT_START_X = 886;
const int LEVEL_ZERO_BOT_START_Y = 308;

void Bot::setBlue1()
{
	_sprite.setTextureRect(sf::IntRect(128, 64, 16, 16));
}

void Bot::setBlue2()
{
	_sprite.setTextureRect(sf::IntRect(144, 64, 16, 16));
}

void Bot::setWhite1()
{
	_sprite.setTextureRect(sf::IntRect(160, 64, 16, 16));
}

void Bot::setWhite2()
{
	_sprite.setTextureRect(sf::IntRect(178, 64, 16, 16));
}

void Bot::setMadModeSkin(sf::IntRect textureRect)
{
	if (textureRect == sf::IntRect(128, 64, 16, 16)) {
		this->setBlue2();
	}
	else if (textureRect == sf::IntRect(144, 64, 16, 16))
		this->setWhite1();
	else if (textureRect == sf::IntRect(160, 64, 16, 16))
		this->setWhite2();
	else
		this->setBlue1();
}

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
		break;

	case Pink:
		_sprite.setTextureRect(sf::IntRect(32, 80, 16, 16));
		break;

	case Blue:
		_sprite.setTextureRect(sf::IntRect(32, 96, 16, 16));
		break;

	case Orange:
		_sprite.setTextureRect(sf::IntRect(32, 112, 16, 16));
		break;

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
		if (!_madMode)
			_sprite.setTextureRect(sf::IntRect(0, _sprite.getTextureRect().top, 16, 16));
		
		updated_pos.x += botSpeed * timeForMove;
		break;

	case Direction::LEFT:
		if (!_madMode)
			_sprite.setTextureRect(sf::IntRect(32, _sprite.getTextureRect().top, 16, 16));
		
		updated_pos.x -= botSpeed * timeForMove;
		break;

	case Direction::UP:
		if (!_madMode)
			_sprite.setTextureRect(sf::IntRect(64, _sprite.getTextureRect().top, 16, 16));
		
		updated_pos.y -= botSpeed * timeForMove;
		break;

	case Direction::DOWN:
		if (!_madMode)
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
