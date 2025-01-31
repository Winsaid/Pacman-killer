#include "../head/Map.h";
#include <iostream>
void Map::deletePoint(int index) {
	auto iter = _points.begin();
	_points.erase(iter + index);
}

void Map::deleteBomb(int index) {
	auto iter = _bombs.begin();
	_bombs.erase(iter + index);
}

void Map::deleteAcseleration (int index) {
	auto iter = _acseleration.begin();
	_acseleration.erase(iter + index);
}

Map::Map(Level binMap, Level map, sf::Vector2f botPosition, sf::Vector2f playerPosition, sf::Vector2f secondPlayerPosition) : _binMap(binMap), _map(map), _botPosition(botPosition), _playerPosition(playerPosition), _secondPlayerPosition(secondPlayerPosition)
{
	sf::String tempStr;
	sf::CircleShape point;
	point.setRadius(4);
	point.setFillColor(sf::Color::Yellow);

	for (int i = 1; i < _map.getSize().x; ++i) {
		for (int j = 2, counter = 0; j < _map.getSize().y * 2 - 2; j += 2, ++counter) {
			tempStr = _map.getStrings()[i].substring(j, 2);
			if (tempStr == sf::String("0*")) {
				point.setPosition(sf::Vector2f(_map.getPosition().x + counter * 16 * 2 + 44, _map.getPosition().y + i * 16 * 2 + 12));
				_points.push_back(point);
			}
			else if (tempStr == sf::String("0!")) {
				point.setRadius(8);
				point.setPosition(sf::Vector2f(_map.getPosition().x + counter * 16 * 2 + 40, _map.getPosition().y + i * 16 * 2 + 8));
				_points.push_back(point);
				point.setRadius(4);
			}
		}
	}
}

void Map::setBomb(sf::Texture& texture) {
	sf::String tempStr;
	sf::Sprite bomb;

	bomb.setTexture(texture);
	bomb.setTextureRect(sf::IntRect(0, 176, 16, 16));
	bomb.setScale(2, 2);
	int count = 0;
	for (int i = 1; i < _binMap.getSize().x; ++i) {
		for (int j = 2; j < _binMap.getSize().y - 1; ++j) {
			tempStr = _binMap.getStrings()[i].substring(j, 1);
			if (tempStr == sf::String("1")) {
				++count;
			}
		}
	}

	int randNum = 1 + rand() % count;
	count = 0;


	for (int i = 1; i < _binMap.getSize().x; ++i) {
		for (int j = 2; j < _binMap.getSize().y - 1; ++j) {
			tempStr = _binMap.getStrings()[i].substring(j, 1);
			if (tempStr == sf::String("1")) {
				++count;
			}
			if (count == randNum) {
				bomb.setPosition(sf::Vector2f(_binMap.getPosition().x + j * 16 * 2 + 32, _binMap.getPosition().y + i * 16 * 2));
			}
		}
	}
	_bombs.push_back(bomb);
}

void Map::setAcseleration(sf::Texture& texture) {
	sf::String tempStr;
	sf::Sprite acseleration;

	acseleration.setTexture(texture);
	acseleration.setTextureRect(sf::IntRect(64, 192, 16, 16));
	acseleration.setScale(2, 2);
	int count = 0;
	for (int i = 1; i < _binMap.getSize().x; ++i) {
		for (int j = 2; j < _binMap.getSize().y - 1; ++j) {
			tempStr = _binMap.getStrings()[i].substring(j, 1);
			if (tempStr == sf::String("1")) {
				++count;
			}
		}
	}

	int randNum = 1 + rand() % count;
	count = 0;


	for (int i = 1; i < _binMap.getSize().x; ++i) {
		for (int j = 2; j < _binMap.getSize().y - 1; ++j) {
			tempStr = _binMap.getStrings()[i].substring(j, 1);
			if (tempStr == sf::String("1")) {
				++count;
			}
			if (count == randNum) {
				acseleration.setPosition(sf::Vector2f(_binMap.getPosition().x + j * 16 * 2 + 32, _binMap.getPosition().y + i * 16 * 2));
			}
		}
	}
	_acseleration.push_back(acseleration);
}

Level::Level(std::vector<sf::String> strings, sf::Vector2f size, sf::Vector2f position)
	: _strings(strings), _size(size), _position(position){}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Texture texture;
	texture.loadFromFile("../../../../images/pacman-sheet.png");

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(2, 2);

	sf::String tempStr;

	for (int indexY = 0; indexY < _size.x; ++indexY) {
		for (int indexX = 0, counter = 0; indexX < _size.y * 2; indexX += 2, ++counter) {
			tempStr = _strings[indexY].substring(indexX, 2);
			if (tempStr == sf::String("20")) {
				sprite.setTextureRect(sf::IntRect(192, 16, 16, 16));
			}
			else if (tempStr == sf::String("21")) {
				sprite.setTextureRect(sf::IntRect(208, 16, 16, 16));
			}
			else if (tempStr == sf::String("22")) {
				sprite.setTextureRect(sf::IntRect(192, 32, 16, 16));
			}
			else if (tempStr == sf::String("23")) {
				sprite.setTextureRect(sf::IntRect(208, 32, 16, 16));
			}
			else if (tempStr == sf::String("24")) {
				sprite.setTextureRect(sf::IntRect(208, 64, 16, 16));
			}
			else if (tempStr == sf::String("25")) {
				sprite.setTextureRect(sf::IntRect(208, 112, 16, 16));
			}
			else if (tempStr == sf::String("26")) {
				sprite.setTextureRect(sf::IntRect(208, 80, 16, 16));
			}
			else if (tempStr == sf::String("27")) {
				sprite.setTextureRect(sf::IntRect(208, 96, 16, 16));
			}
			else if (tempStr == sf::String("01")) {
				sprite.setTextureRect(sf::IntRect(192, 64, 16, 16));
			}
			else if (tempStr == sf::String("02")) {
				sprite.setTextureRect(sf::IntRect(192, 80, 16, 16));
			}
			else if (tempStr == sf::String("05")) {
				sprite.setTextureRect(sf::IntRect(160, 16, 16, 16));
			}
			else if (tempStr == sf::String("06")) {
				sprite.setTextureRect(sf::IntRect(176, 16, 16, 16));
			}
			else if (tempStr == sf::String("07")) {
				sprite.setTextureRect(sf::IntRect(160, 32, 16, 16));
			}
			else if (tempStr == sf::String("08")) {
				sprite.setTextureRect(sf::IntRect(176, 32, 16, 16));
			}
			else if (tempStr == sf::String("17")) {
				sprite.setTextureRect(sf::IntRect(0, 176, 16, 16));
			}
			else {
				sprite.setTextureRect(sf::IntRect(32, 48, 16, 16));
			}

			sprite.setPosition(sf::Vector2f(_position.x + counter * 16 * 2, _position.y + indexY * 16 * 2));
			target.draw(sprite);
		}
	}
}

sf::FloatRect Map::getIntersectZeroBlock(sf::FloatRect rect) {
	return _binMap.getIntersectZeroBlock(rect);
}

sf::FloatRect Level::getIntersectZeroBlock(sf::FloatRect rect) {
	for (int strIndex = 0; strIndex < _strings.size(); ++strIndex) {
		for (int chIndex = 0; chIndex < _strings[strIndex].getSize(); ++chIndex) {
			if (_strings[strIndex][chIndex] == sf::String("0")) {
				sf::FloatRect blockRect(sf::Vector2f(_position.x + chIndex * 16 * 2, _position.y + strIndex * 16 * 2), sf::Vector2f(32, 32));
				if (blockRect.intersects(rect)) {
					return blockRect;
				}
			}
		}
	}
}

sf::FloatRect Map::getIntersectNoZeroBlock(sf::FloatRect rect) {
	return _binMap.getIntersectNoZeroBlock(rect);
}

sf::FloatRect Level::getIntersectNoZeroBlock(sf::FloatRect rect) {
	for (int strIndex = 0; strIndex < _strings.size(); ++strIndex) {
		for (int chIndex = 0; chIndex < _strings[strIndex].getSize(); ++chIndex) {
			if (_strings[strIndex][chIndex] == sf::String("1") || _strings[strIndex][chIndex] == sf::String("2")) {
				sf::FloatRect blockRect(sf::Vector2f(_position.x + chIndex * 16 * 2, _position.y + strIndex * 16 * 2), sf::Vector2f(32, 32));
				if (blockRect.intersects(rect)) {
					return blockRect;
				}
			}
		}
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_map);
	for (int i = 0; i < _points.size(); ++i) target.draw(_points[i]);
	for (int i = 0; i < _bombs.size(); ++i) target.draw(_bombs[i]);
	for (int i = 0; i < _acseleration.size(); ++i) target.draw(_acseleration[i]);
}

bool Map::isAvailableZone(sf::FloatRect rect)
{
	if (!_binMap.isAvailableZone(rect)) return false;

	return true;
}

bool Level::isAvailableZone(sf::FloatRect playerRect)
{
	for (int strIndex = 0; strIndex < _strings.size(); ++strIndex) {
		for (int chIndex = 0; chIndex < _strings[strIndex].getSize(); ++chIndex) {
			if (_strings[strIndex][chIndex] == '0') {
				sf::FloatRect rect(sf::Vector2f(_position.x + chIndex * 16 * 2, _position.y + strIndex * 16 * 2), sf::Vector2f(32, 32));

				if (rect.intersects(playerRect)) return false;
			}
		}
	}

	return true;
}

bool Map::canDefinePacmanPos(sf::FloatRect rect)
{
	if (_binMap.canDefinePacmanPos(rect))
		return true;

	return false;
}

bool Level::canDefinePacmanPos(sf::FloatRect playerRect)
{
	for (int strIndex = 0; strIndex < _strings.size(); ++strIndex) {
		for (int chIndex = 0; chIndex < _strings[strIndex].getSize(); ++chIndex) {
			if (_strings[strIndex][chIndex] == '2') {
				sf::FloatRect rect(sf::Vector2f(_position.x + chIndex * 16 * 2, _position.y + strIndex * 16 * 2), sf::Vector2f(32, 32));

				if (std::abs(rect.top - playerRect.top) < 1 && std::abs(rect.left - playerRect.left) < 2) return true;
			}
		}
	}

	return false;
}

void Map::setPlayerRect(sf::FloatRect playerRect)
{
	this->_firstPlayerRect = playerRect;
}

void Map::setSecondPlayerRect(sf::FloatRect playerRect)
{
	this->_secondPlayerRect = playerRect;
}
