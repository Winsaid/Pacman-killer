#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Level : public sf::Drawable {
public:
	Level(int numberLevel, bool twoPlayers);
	std::vector<sf::String> GetBinMap() { return _BinMap; }
	std::vector<sf::String> GetMap() { return _Map; }
	sf::Vector2f GetFirstPlayerPosition() { return _FirstPlayerPosition; }
	sf::Vector2f GetSecondPlayerPosition() { return _SecondPlayerPosition; }
	std::vector<sf::Vector2f> GetBotsPosition() { return _BotsPosition; }
	sf::Vector2f GetMapPositon() { return _MapPositon; }
	sf::Vector2f GetMapSize() { return _MapSize; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isAvailableZone(sf::FloatRect rect);
	sf::FloatRect getIntersectZeroBlock(sf::FloatRect rect);
	sf::FloatRect getIntersectNoZeroBlock(sf::FloatRect rect);
	bool canDefinePacmanPos(sf::FloatRect rect);

private:
	std::vector<sf::String> _BinMap;
	std::vector<sf::String> _Map;
	sf::Vector2f _FirstPlayerPosition;
	sf::Vector2f _SecondPlayerPosition;
	std::vector<sf::Vector2f> _BotsPosition;
	sf::Vector2f _MapPositon;
	sf::Vector2f _MapSize;
};

class Map : public sf::Drawable {
public:
	Map(Level level);

	std::vector<sf::CircleShape> getPoints() { return _points; }
	int getStartPointCount() { return _startPointCount; }

	void setPlayerRect(sf::FloatRect playerRect);
	sf::FloatRect getPlayerRect() { return _playerRect; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isAvailableZone(sf::FloatRect rect);
	void deletePoint(int index);
	sf::FloatRect getIntersectZeroBlock(sf::FloatRect rect);
	sf::FloatRect getIntersectNoZeroBlock(sf::FloatRect rect);
	bool canDefinePacmanPos(sf::FloatRect rect);

private:
	Level _level;
	std::vector<sf::CircleShape> _points;
	int _startPointCount;
	sf::FloatRect _playerRect;

};
