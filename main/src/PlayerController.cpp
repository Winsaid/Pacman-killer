#include "PlayerController.h"
#include "Player.h"
#include "Map.h"

PlayerController* PlayerController::_controller = nullptr;

PlayerController::~PlayerController() {
    delete _controller;
}

PlayerController* PlayerController::getPlayerController() {
    if (!_controller) {
        _controller = new PlayerController();
    }

    return _controller;
}

void PlayerController::ControllPlayer(Player* player, Map &map, float time) {
    sf::Vector2f  updated_pos = player->getPosition();
    sf::FloatRect playerRect(player->getSprite().getGlobalBounds());
    sf::FloatRect smallPlayerRect(player->getSprite().getGlobalBounds());
    float         playerSpeed = 0.05;
    PressedButton lastPressedButton = _pressedButton;
    std::vector<sf::CircleShape> points = map.getPoints();

    smallPlayerRect.height -= 18;
    smallPlayerRect.width -= 18;
    smallPlayerRect.top += 18;
    smallPlayerRect.left += 18;

    for (int index = 0; index < points.size(); ++index)
        if (smallPlayerRect.intersects(points[index].getGlobalBounds()))
            map.deletePoint(index);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->_pressedButton = PressedButton::A;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->_pressedButton = PressedButton::D;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->_pressedButton = PressedButton::W;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->_pressedButton = PressedButton::S;

    if (this->_pressedButton == PressedButton::A) {
        updated_pos.x -= playerSpeed * time;
        playerRect.left = updated_pos.x - 1;
        playerRect.top = updated_pos.y;

        if (!map.isAvailableZone(playerRect))
        {
            _pressedButton = lastPressedButton;
            updated_pos = player->getPosition();

            if (_pressedButton == PressedButton::D) {
                updated_pos.x += playerSpeed * time;
            }
            else if (_pressedButton == PressedButton::W) {
                updated_pos.y -= playerSpeed * time;
                playerRect.top = updated_pos.y;
                playerRect.left = updated_pos.x;
                if (!map.isAvailableZone(playerRect)) return;
            }
            else if (_pressedButton == PressedButton::S) {
                updated_pos.y += playerSpeed * time;
                playerRect.top = updated_pos.y;
                playerRect.left = updated_pos.x;
                if (!map.isAvailableZone(playerRect)) return;
            }
            player->setPosition(updated_pos);
            return;
        }
        else  player->setDirection(Direction::LEFT);
    } 
    else if (this->_pressedButton == PressedButton::D) {
        updated_pos.x += playerSpeed * time;
        playerRect.left = updated_pos.x + 1;
        playerRect.top = updated_pos.y;

        if (!map.isAvailableZone(playerRect))
        {
            _pressedButton = lastPressedButton;
            updated_pos = player->getPosition();

            if (_pressedButton == PressedButton::A) {
                updated_pos.x -= playerSpeed * time;
            }
            else if (_pressedButton == PressedButton::W) {
                updated_pos.y -= playerSpeed * time;
                playerRect.top = updated_pos.y;
                playerRect.left = updated_pos.x;
                if (!map.isAvailableZone(playerRect)) return;
            }
            else if (_pressedButton == PressedButton::S) {
                updated_pos.y += playerSpeed * time;
                playerRect.top = updated_pos.y;
                playerRect.left = updated_pos.x;
                if (!map.isAvailableZone(playerRect)) return;
            }
            player->setPosition(updated_pos);
            return;
        }
        else player->setDirection(Direction::RIGHT);
    }
    else if (this->_pressedButton == PressedButton::W) {
        updated_pos.y -= playerSpeed * time;
        playerRect.left = updated_pos.x;
        playerRect.top = updated_pos.y - 1;

        if (!map.isAvailableZone(playerRect))
        {
            _pressedButton = lastPressedButton;
            updated_pos = player->getPosition();

            if (_pressedButton == PressedButton::D) {
                updated_pos.x += playerSpeed * time;
                playerRect.left = updated_pos.x;
                playerRect.top = updated_pos.y;
                if (!map.isAvailableZone(playerRect)) return;
            }
            else if (_pressedButton == PressedButton::A) {
                updated_pos.x -= playerSpeed * time;
                playerRect.left = updated_pos.x;
                playerRect.top = updated_pos.y;
                if (!map.isAvailableZone(playerRect)) return;
            }
            else if (_pressedButton == PressedButton::S) {
                updated_pos.y += playerSpeed * time;
            }
            player->setPosition(updated_pos);
            return;
        }
        else player->setDirection(Direction::UP);
    }
    else if (this->_pressedButton == PressedButton::S) {
        updated_pos.y += playerSpeed * time;
        playerRect.left = updated_pos.x;
        playerRect.top = updated_pos.y + 1;
        
        if (!map.isAvailableZone(playerRect))
        {
            _pressedButton = lastPressedButton;
            updated_pos = player->getPosition();

            if (_pressedButton == PressedButton::D) {
                updated_pos.x += playerSpeed * time;
                playerRect.left = updated_pos.x;
                playerRect.top = updated_pos.y;
                if (!map.isAvailableZone(playerRect)) return;
            }
            else if (_pressedButton == PressedButton::W) {
                updated_pos.y -= playerSpeed * time;
            }
            else if (_pressedButton == PressedButton::A) {
                updated_pos.x -= playerSpeed * time;
                playerRect.left = updated_pos.x;
                playerRect.top = updated_pos.y;
                if (!map.isAvailableZone(playerRect)) return;
            }
            player->setPosition(updated_pos);
            return;
        }
        else player->setDirection(Direction::DOWN);
    }

    player->setPosition(updated_pos);
}