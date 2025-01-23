#include "../head/Player.h"
#include "../head/PlayerController.h"
#include "../head/Map.h"

bool Player::getMode() 
{
    return _madMode;
}

void Player::setMadMode() 
{
    _timerForMad.restart();
    _madMode = true;
}

void Player::unsetMadMode() 
{
    _madMode = false;
}

float Player::getTime() 
{
    return _timerForMad.getElapsedTime().asSeconds();
}

Player::Player(sf::Texture& texture, sf::Vector2f start_pos, int playerNumber) {
    _pos = start_pos;
    _health = 3;
    _playerNumber = playerNumber;

    if (playerNumber == 1)
        _controller = PlayerController::getPlayerController();
    else
        _controller = PlayerController::getSecondPlayerController();

    _sprite.setTexture(texture);
    _sprite.setTextureRect(sf::IntRect(48, 0, -16, 16));
    _sprite.setScale(2, 2);
    _sprite.setPosition(start_pos);
    _size = sf::Vector2f(32, 32);
}

void Player::Update(Map &map, float timeForMove, float timeForPlrSprt) {
    Direction lastDirection = _direction;
    _controller->ControllPlayer( this, map, timeForMove / 400);
    if (this->_playerNumber == 1)
        map.setPlayerRect(this->getSprite().getGlobalBounds());
    else
        map.setSecondPlayerRect(this->getSprite().getGlobalBounds());

    if (_playerNumber == 1) {
        if (timeForPlrSprt > 0.1) {
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
    }
    else {
        if (timeForPlrSprt > 0.1) {
            if (_direction == Direction::RIGHT) {
                if (lastDirection != Direction::RIGHT) {
                    _sprite.setTextureRect(sf::IntRect(160, 80, 16, 16));
                }
                else if (_sprite.getTextureRect() == sf::IntRect(160, 80, 16, 16)) {
                    _sprite.setTextureRect(sf::IntRect(128, 80, 16, 16));
                }
                else if (_sprite.getTextureRect() == sf::IntRect(128, 80, 16, 16)) {
                    _sprite.setTextureRect(sf::IntRect(144, 80, 16, 16));
                }
                else {
                    _sprite.setTextureRect(sf::IntRect(160, 80, 16, 16));
                }
            }
            else if (_direction == Direction::LEFT) {
                if (lastDirection != Direction::LEFT) {
                    _sprite.setTextureRect(sf::IntRect(160, 96, 16, 16));
                }
                else if (_sprite.getTextureRect() == sf::IntRect(160, 96, 16, 16)) {
                    _sprite.setTextureRect(sf::IntRect(128, 96, 16, 16));
                }
                else if (_sprite.getTextureRect() == sf::IntRect(128, 96, 16, 16)) {
                    _sprite.setTextureRect(sf::IntRect(144, 96, 16, 16));
                }
                else {
                    _sprite.setTextureRect(sf::IntRect(160, 96, 16, 16));
                }
            }
            else if (_direction == Direction::UP) {
                if (lastDirection != Direction::UP) {
                    _sprite.setTextureRect(sf::IntRect(160, 112, 16, 16));
                }
                else if (_sprite.getTextureRect() == sf::IntRect(160, 112, 16, 16)) {
                    _sprite.setTextureRect(sf::IntRect(128, 112, 16, 16));
                }
                else if (_sprite.getTextureRect() == sf::IntRect(128, 112, 16, 16)) {
                    _sprite.setTextureRect(sf::IntRect(144, 112, 16, 16));
                }
                else {
                    _sprite.setTextureRect(sf::IntRect(160, 112, 16, 16));
                }
            }
            else if (_direction == Direction::DOWN) {
                if (lastDirection != Direction::DOWN) {
                    _sprite.setTextureRect(sf::IntRect(160, 128, 16, 16));
                }
                else if (_sprite.getTextureRect() == sf::IntRect(160, 128, 16, 16)) {
                    _sprite.setTextureRect(sf::IntRect(128, 128, 16, 16));
                }
                else if (_sprite.getTextureRect() == sf::IntRect(128, 128, 16, 16)) {
                    _sprite.setTextureRect(sf::IntRect(144, 128, 16, 16));
                }
                else {
                    _sprite.setTextureRect(sf::IntRect(160, 128, 16, 16));
                }
            }
        }
    }
}
