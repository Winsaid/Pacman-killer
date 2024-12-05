#include "Character.h"

Character::~Character() {}

void Character::takeDamage(float damage) {
    _health -= damage;
}

void Character::setPosition(sf::Vector2f pos) {
    _pos = pos;
    _sprite.setPosition(_pos);
}

void Character::setDirection(Direction direction) {
    _direction = direction;
}

float Character::getHP() const {
    return _health;
}

sf::Vector2f Character::getSize() const {
    return _size;
}

sf::Vector2f Character::getPosition() const {
    return _pos;
}

sf::Sprite Character::getSprite() const {
    return _sprite;
}

Direction Character::getDirection() const {
    return _direction;
}