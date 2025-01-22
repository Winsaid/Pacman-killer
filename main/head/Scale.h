#pragma once

#include <SFML/Graphics.hpp>

class Scale : public sf::Drawable {
public:
	Scale(int points, sf::RectangleShape outer);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void addCollectedPoint();
	bool isAllPointCollected() { return _points == _collectedPoints; }

private:
	int _points;
	int _collectedPoints = 0;
	sf::RectangleShape _outer;
	sf::RectangleShape _inner;

	void increasePointScale();
};

Scale getScale(int pointsCount);
