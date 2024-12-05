#include "Player.h"
#include "PlayerController.h"
#include "Map.h"

Player::Player(sf::Texture& texture, sf::Vector2f start_pos, float health) {
    _pos = start_pos;
    _health = health;

    _controller = PlayerController::getPlayerController();

    _sprite.setTexture(texture);
    _sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
    _sprite.setScale(2, 2);
    _size = sf::Vector2f(_sprite.getTextureRect().width, _sprite.getTextureRect().height);
}

Player::~Player() {}

void Player::Update(Map &map, float timeForMove, float timeForPlrSprt) {
    Direction lastDirection = _direction;   

    _controller->ControllPlayer( this, map, timeForMove / 400);

    if (timeForPlrSprt > 0.12) {
        if (_direction == Direction::RIGHT) {
            if (lastDirection != Direction::RIGHT) {
                _sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
            }
            else if (_sprite.getTextureRect() == sf::IntRect(32, 0, 16, 16)) {
                _sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
            }
            else if (_sprite.getTextureRect() == sf::IntRect(0, 0, 16, 16)) {
                _sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
            }
            else {
                _sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
            }
        }
        else if (_direction == Direction::LEFT) {
            if (lastDirection != Direction::LEFT) {
                _sprite.setTextureRect(sf::IntRect(48, 0, -16, 16));
            }
            else if (_sprite.getTextureRect() == sf::IntRect(48, 0, -16, 16)) {
                _sprite.setTextureRect(sf::IntRect(0, 16, 16, 16));
            }
            else if (_sprite.getTextureRect() == sf::IntRect(0, 16, 16, 16)) {
                _sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));
            }
            else {
                _sprite.setTextureRect(sf::IntRect(48, 0, -16, 16));
            }
        }
        else if (_direction == Direction::UP) {
            if (lastDirection != Direction::UP) {
                _sprite.setTextureRect(sf::IntRect(32, 16, 16, -16));
            }
            else if (_sprite.getTextureRect() == sf::IntRect(32, 16, 16, -16)) {
                _sprite.setTextureRect(sf::IntRect(0, 32, 16, 16));
            }
            else if (_sprite.getTextureRect() == sf::IntRect(0, 32, 16, 16)) {
                _sprite.setTextureRect(sf::IntRect(16, 32, 16, 16));
            }
            else {
                _sprite.setTextureRect(sf::IntRect(32, 16, 16, -16));
            }
        }
        else if (_direction == Direction::DOWN) {
            if (lastDirection != Direction::DOWN) {
                _sprite.setTextureRect(sf::IntRect(48, 0, -16, 16));
            }
            else if (_sprite.getTextureRect() == sf::IntRect(48, 0, -16, 16)) {
                _sprite.setTextureRect(sf::IntRect(0, 48, 16, 16));
            }
            else if (_sprite.getTextureRect() == sf::IntRect(0, 48, 16, 16)) {
                _sprite.setTextureRect(sf::IntRect(16, 48, 16, 16));
            }
            else {
                _sprite.setTextureRect(sf::IntRect(48, 0, -16, 16));
            }
        }
    }
    
    _sprite.setPosition(_pos);
}

void Player::UpdateSprite() {
    
}