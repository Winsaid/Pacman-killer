#include "Map.h";

int MAP_HEIGHT_BIN = 11;
int MAP_WIDTH_BIN  = 20;
int MAP_START_X = 328;
int MAP_START_Y = 152;

int MAP_LEVEL_TWO_HEIGHT = 22;
int MAP_LEVEL_TWO_WIDTH = 19;
int MAP_START_LEVEL_TWO_X = 298;
int MAP_START_LEVEL_TWO_Y = 152;

void Map::deletePoint(int index) {
	auto iter = _points.begin();
	_points.erase(iter + index);
}

Map::Map(std::vector<Level> levels) : _levels(levels)
{
	sf::String tempStr;
	sf::CircleShape point;
	point.setRadius(4);
	point.setFillColor(sf::Color::Yellow);

	for (int i = 1; i < MAP_LEVEL_TWO_HEIGHT; ++i) {
		for (int j = 2, counter = 0; j < MAP_LEVEL_TWO_WIDTH * 2 - 2; j += 2, ++counter) {
			tempStr = _levels[1].getStrings()[i].substring(j, 2);
			if (tempStr == sf::String("0*")) {
				point.setPosition(sf::Vector2f(MAP_START_LEVEL_TWO_X + counter * 16 * 2 + 44, MAP_START_LEVEL_TWO_Y + i * 16 * 2 + 12));
				_points.push_back(point);
			}
			else if (tempStr == sf::String("0!")) {
				point.setRadius(8);
				point.setPosition(sf::Vector2f(MAP_START_LEVEL_TWO_X + counter * 16 * 2 + 40, MAP_START_LEVEL_TWO_Y + i * 16 * 2 + 8));
				_points.push_back(point);
				point.setRadius(4);
			}
		}
	}
}

Level::Level(std::vector<sf::String> strings)
	: _strings(strings) {}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Texture texture;
	texture.loadFromFile("./images/pacman-sheet.png");

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(2, 2);

	sf::String tempStr;

	for (int indexY = 0; indexY < MAP_LEVEL_TWO_HEIGHT; ++indexY) {
		for (int indexX = 0, counter = 0; indexX < MAP_LEVEL_TWO_WIDTH * 2; indexX += 2, ++counter) {
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
			else {
				sprite.setTextureRect(sf::IntRect(32, 48, 16, 16));
			}

			sprite.setPosition(sf::Vector2f(MAP_START_LEVEL_TWO_X + counter * 16 * 2, MAP_START_LEVEL_TWO_Y + indexY * 16 * 2));			
			target.draw(sprite);
		}
	}
}

sf::FloatRect Map::getIntersectBlock(sf::FloatRect rect) {
	return _levels[0].getIntersectBlock(rect);
}

sf::FloatRect Level::getIntersectBlock(sf::FloatRect rect) {
	for (int strIndex = 0; strIndex < _strings.size(); ++strIndex) {
		for (int chIndex = 0; chIndex < _strings[strIndex].getSize(); ++chIndex) {
			if (_strings[strIndex][chIndex] == sf::String("0"))
			{
				sf::FloatRect blockRect(sf::Vector2f(MAP_START_LEVEL_TWO_X + chIndex * 16 * 2, MAP_START_LEVEL_TWO_Y + strIndex * 16 * 2), sf::Vector2f(32, 32));
				if (blockRect.intersects(rect)) {
					return blockRect;
				}
			}
		}
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_levels[1]);
	for (int i = 0; i < _points.size(); ++i) target.draw(_points[i]);
}

bool Map::isAvailableZone(sf::FloatRect rect)
{
	if (!_levels[0].isAvailableZone(rect)) return false;

	return true;
}

bool Level::isAvailableZone(sf::FloatRect playerRect)
{
	for (int strIndex = 0; strIndex < _strings.size(); ++strIndex) {
		for (int chIndex = 0; chIndex < _strings[strIndex].getSize(); ++chIndex) {
			if (_strings[strIndex][chIndex] == '0') {
				sf::FloatRect rect(sf::Vector2f(MAP_START_LEVEL_TWO_X + chIndex * 16 * 2, MAP_START_LEVEL_TWO_Y + strIndex * 16 * 2), sf::Vector2f(32, 32));

				if (rect.intersects(playerRect)) return false;
			}
		}
	}

	return true;
}

