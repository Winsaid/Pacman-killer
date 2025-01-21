#include "../head/Map.h";
#include "../head/Constants.h"

void Map::deletePoint(int index) {
	auto iter = _points.begin();
	_points.erase(iter + index);
}

Map::Map(Level level) : _level(level)
{
	sf::String tempStr;
	sf::CircleShape point;
	point.setRadius(4);
	point.setFillColor(sf::Color::Yellow);

	for (int i = 1; i < level.GetMapSize().y; ++i) {
		for (int j = 2, counter = 0; j < level.GetMapSize().x * 2 - 2; j += 2, ++counter) {
			tempStr = _level.GetMap()[i].substring(j, 2);
			if (tempStr == sf::String("0*")) {
				point.setPosition(sf::Vector2f(level.GetMapPositon().x + counter * 16 * 2 + 44, level.GetMapPositon().y + i * 16 * 2 + 12));
				_points.push_back(point);
			}
			else if (tempStr == sf::String("0!")) {
				point.setRadius(8);
				point.setPosition(sf::Vector2f(level.GetMapPositon().x + counter * 16 * 2 + 40, level.GetMapPositon().y + i * 16 * 2 + 8));
				_points.push_back(point);
				point.setRadius(4);
			}
		}
	}
}

Level::Level(int numberLevel, bool twoPlayer) {
	if (numberLevel == 1) {
		_BinMap = LEVEL_TWO;
		_Map = LEVEL_TWO_S;
		_FirstPlayerPosition = sf::Vector2f(586, 408);
		_BotsPosition = std::vector<sf::Vector2f>();
		_MapPositon = sf::Vector2f(MAP_START_LEVEL_TWO_X, MAP_START_LEVEL_TWO_Y);
		_MapSize = sf::Vector2f(MAP_LEVEL_TWO_WIDTH, MAP_LEVEL_TWO_HEIGHT);
		if (twoPlayer) {
			_SecondPlayerPosition = sf::Vector2f(586, 408);
		}
	}
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Texture texture;
	texture.loadFromFile("../../../../images/pacman-sheet.png");

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(2, 2);

	sf::String tempStr;

	for (int indexY = 0; indexY < _MapSize.y; ++indexY) {
		for (int indexX = 0, counter = 0; indexX < _MapSize.x * 2; indexX += 2, ++counter) {
			tempStr = _Map[indexY].substring(indexX, 2);
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
			else {
				sprite.setTextureRect(sf::IntRect(32, 48, 16, 16));
			}

			sprite.setPosition(sf::Vector2f(_MapPositon.x + counter * 16 * 2, _MapPositon.y + indexY * 16 * 2));			
			target.draw(sprite);
		}
	}
}

sf::FloatRect Map::getIntersectZeroBlock(sf::FloatRect rect) {
	return _level.getIntersectZeroBlock(rect);
}

sf::FloatRect Level::getIntersectZeroBlock(sf::FloatRect rect) {
	for (int strIndex = 0; strIndex < _BinMap.size(); ++strIndex) {
		for (int chIndex = 0; chIndex < _BinMap[strIndex].getSize(); ++chIndex) {
			if (_BinMap[strIndex][chIndex] == sf::String("0")) {
				sf::FloatRect blockRect(sf::Vector2f(_MapPositon.x + chIndex * 16 * 2, _MapPositon.y + strIndex * 16 * 2), sf::Vector2f(32, 32));
				if (blockRect.intersects(rect)) {
					return blockRect;
				}
			}
		}
	}
}

sf::FloatRect Map::getIntersectNoZeroBlock(sf::FloatRect rect) {
	return _level.getIntersectNoZeroBlock(rect);
}

sf::FloatRect Level::getIntersectNoZeroBlock(sf::FloatRect rect) {
	for (int strIndex = 0; strIndex < _BinMap.size(); ++strIndex) {
		for (int chIndex = 0; chIndex < _BinMap[strIndex].getSize(); ++chIndex) {
			if (_BinMap[strIndex][chIndex] == sf::String("1") || _BinMap[strIndex][chIndex] == sf::String("2")) {
				sf::FloatRect blockRect(sf::Vector2f(_MapPositon.x + chIndex * 16 * 2, _MapPositon.y + strIndex * 16 * 2), sf::Vector2f(32, 32));
				if (blockRect.intersects(rect)) {
					return blockRect;
				}
			}
		}
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_level);
	for (int i = 0; i < _points.size(); ++i) target.draw(_points[i]);
}

bool Map::isAvailableZone(sf::FloatRect rect)
{
	if (!_level.isAvailableZone(rect)) return false;

	return true;
}

bool Level::isAvailableZone(sf::FloatRect playerRect)
{
	for (int strIndex = 0; strIndex < GetBinMap().size(); ++strIndex) {
		for (int chIndex = 0; chIndex < GetBinMap()[strIndex].getSize(); ++chIndex) {
			if (GetBinMap()[strIndex][chIndex] == '0') {
				sf::FloatRect rect(sf::Vector2f(_MapPositon.x + chIndex * 16 * 2, _MapPositon.y + strIndex * 16 * 2), sf::Vector2f(32, 32));

				if (rect.intersects(playerRect)) return false;
			}
		}
	}

	return true;
}

bool Map::canDefinePacmanPos(sf::FloatRect rect)
{
	if (_level.canDefinePacmanPos(rect))
		return true;

	return false;
}

bool Level::canDefinePacmanPos(sf::FloatRect playerRect)
{
	for (int strIndex = 0; strIndex < GetBinMap().size(); ++strIndex) {
		for (int chIndex = 0; chIndex < GetBinMap()[strIndex].getSize(); ++chIndex) {
			if (GetBinMap()[strIndex][chIndex] == '2') {
				sf::FloatRect rect(sf::Vector2f(_MapPositon.x + chIndex * 16 * 2, _MapPositon.y + strIndex * 16 * 2), sf::Vector2f(32, 32));

				if (std::abs(rect.top - playerRect.top) < 1 && std::abs(rect.left - playerRect.left) < 2) return true;
			}
		}
	}

	return false;
}

void Map::setPlayerRect(sf::FloatRect playerRect)
{
	this->_playerRect = playerRect;
}
