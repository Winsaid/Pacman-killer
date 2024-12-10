#include "Scale.h"

Scale::Scale(int points, sf::RectangleShape outer)
	: _points(points), _outer(outer), _inner(outer)
{
	_inner.setFillColor(sf::Color::Black);
	_inner.setOutlineThickness(0);
	sf::Vector2f pos  = _outer.getPosition();
	sf::Vector2f size = _outer.getSize();
	_inner.setPosition(pos.x + 5, pos.y);
	_inner.setSize(sf::Vector2f(size.x - 5, size.y));
}

void Scale::addCollectedPoint() 
{
	this->increasePointScale();
	++_collectedPoints; 
}

void Scale::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_outer);
	target.draw(_inner);
}

void Scale::increasePointScale()
{
	float increaseWidth  = _inner.getSize().x / (_points - _collectedPoints);
	sf::Vector2f newSize = _inner.getSize();
	sf::Vector2f newPos  = _inner.getPosition();
	newSize.x -= increaseWidth;
	newPos.x += increaseWidth;
	_inner.setSize(newSize);
	_inner.setPosition(newPos);
}

Scale getScale(int pointsCount)
{
	sf::RectangleShape outer;
	outer.setFillColor(sf::Color::Green);
	outer.setSize(sf::Vector2f(150.f, 30.f));
	outer.setPosition(sf::Vector2f(800.f, 50.f));
	outer.setOutlineThickness(8.f);
	outer.setOutlineColor(sf::Color::Blue);
	return Scale(pointsCount, outer);
}
