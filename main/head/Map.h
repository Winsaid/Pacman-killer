#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


class Level : public sf::Drawable {
public:
	Level(std::vector<sf::String> strings);

	std::vector<sf::String> getStrings() { return _strings; }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isAvailableZone(sf::FloatRect rect);
	sf::FloatRect getIntersectZeroBlock(sf::FloatRect rect);
	sf::FloatRect getIntersectNoZeroBlock(sf::FloatRect rect);
	bool canDefinePacmanPos(sf::FloatRect rect);

private:
	std::vector<sf::String> _strings;

};


class Map : public sf::Drawable {
public:
	Map(std::vector<Level> levels);

	std::vector<sf::CircleShape> getPoints() { return _points; }
	int getStartPointCount() { return _startPointCount; }

	void setPlayerRect(sf::FloatRect playerRect);
	sf::FloatRect getPlayerRect() { return _playerRect; }


	void addLevel(Level level) { _levels.push_back(level); }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isAvailableZone(sf::FloatRect rect);
	void deletePoint(int index);
	sf::FloatRect getIntersectZeroBlock(sf::FloatRect rect);
	sf::FloatRect getIntersectNoZeroBlock(sf::FloatRect rect);
	bool canDefinePacmanPos(sf::FloatRect rect);

private:
	std::vector<Level> _levels;
	std::vector<sf::CircleShape> _points;
	int _startPointCount;
	sf::FloatRect _playerRect;

};
