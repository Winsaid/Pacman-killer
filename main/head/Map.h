#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


class Level : public sf::Drawable {
public:
	Level(std::vector<sf::String> strings, sf::Vector2f size, sf::Vector2f position);

	std::vector<sf::String> getStrings() { return _strings; }
	sf::Vector2f getSize() { return _size; }
	sf::Vector2f getPosition() { return _position; }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isAvailableZone(sf::FloatRect rect);
	sf::FloatRect getIntersectZeroBlock(sf::FloatRect rect);
	sf::FloatRect getIntersectNoZeroBlock(sf::FloatRect rect);
	bool canDefinePacmanPos(sf::FloatRect rect);
	

private:
	std::vector<sf::String> _strings;
	sf::Vector2f _size;
	sf::Vector2f _position;
};


class Map : public sf::Drawable {
public:
	Map::Map(Level binMap, Level map, sf::Vector2f botPosition, sf::Vector2f playerPosition);

	std::vector<sf::CircleShape> getPoints() { return _points; }
	int getStartPointCount() { return _startPointCount; }

	sf::Vector2f getPlayerPosition() { return _playerPosition; }
	sf::Vector2f getBotPosition() { return _botPosition; }
	void setPlayerRect(sf::FloatRect playerRect);
	sf::FloatRect getPlayerRect() { return _playerRect; }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isAvailableZone(sf::FloatRect rect);
	void deletePoint(int index);
	sf::FloatRect getIntersectZeroBlock(sf::FloatRect rect);
	sf::FloatRect getIntersectNoZeroBlock(sf::FloatRect rect);
	bool canDefinePacmanPos(sf::FloatRect rect);

private:
	Level _map;
	Level _binMap;
	std::vector<sf::CircleShape> _points;
	int _startPointCount;
	int _tempPointCount;
	sf::FloatRect _playerRect;
	sf::Vector2f _botPosition;
	sf::Vector2f _playerPosition;
};
