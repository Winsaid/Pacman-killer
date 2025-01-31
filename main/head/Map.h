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
	void setStrings(std::vector<sf::String> string) { _strings = string; }
	
	

private:
	std::vector<sf::String> _strings;
	sf::Vector2f _size;
	sf::Vector2f _position;
};


class Map : public sf::Drawable {
public:
	Map::Map(Level binMap, Level map, sf::Vector2f botPosition, sf::Vector2f playerPosition, sf::Vector2f secondPlayerPosition = sf::Vector2f(0, 0));

	std::vector<sf::CircleShape> getPoints() { return _points; }
	std::vector<sf::Sprite> getBombs() { return _bombs; }
	std::vector<sf::Sprite> getAcseleration() { return _acseleration; }
	int getStartPointCount() { return _startPointCount; }

	sf::Vector2f getPlayerPosition() { return _playerPosition; }
	sf::Vector2f getSecondPlayerPosition() { return _secondPlayerPosition; }
	sf::Vector2f getBotPosition() { return _botPosition; }
	Level getMap() { return _map; }
	Level getBinMap() { return _binMap; }


	void setBomb(sf::Texture& texture);
	void setAcseleration(sf::Texture& texture);

	void setPlayerRect(sf::FloatRect playerRect);
	void setSecondPlayerRect(sf::FloatRect playerRect);
	sf::FloatRect getPlayerRect() { return _firstPlayerRect; }
	sf::FloatRect getSecondPlayerRect() { return _secondPlayerRect; }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isAvailableZone(sf::FloatRect rect);
	void deletePoint(int index);
	void deleteBomb(int index);
	void deleteAcseleration(int index);

	sf::FloatRect getIntersectZeroBlock(sf::FloatRect rect);
	sf::FloatRect getIntersectNoZeroBlock(sf::FloatRect rect);
	bool canDefinePacmanPos(sf::FloatRect rect);

private:
	Level _map;
	Level _binMap;
	std::vector<sf::CircleShape> _points;
	std::vector<sf::Sprite> _bombs;
	std::vector<sf::Sprite> _acseleration;
	int _startPointCount;
	sf::FloatRect _firstPlayerRect;
	sf::FloatRect _secondPlayerRect;
	sf::Vector2f _secondPlayerPosition;
	sf::Vector2f _botPosition;
	sf::Vector2f _playerPosition;
};
