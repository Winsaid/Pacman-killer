#pragma once

#include <SFML/Graphics.hpp>

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Character {
protected:
	float        _health;
	float        _speed;
	sf::Vector2f _size;
	sf::Vector2f _pos;
	sf::Sprite   _sprite;
	Direction    _direction;

public:
	virtual ~Character();

	void takeDamage(float damage);

	void setPosition(sf::Vector2f pos);
	void setDirection(Direction direction);
	

	float getHP() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	Direction getDirection() const;
	
};
