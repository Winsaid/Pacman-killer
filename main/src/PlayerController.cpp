#include "../head/PlayerController.h"
#include "../head/Player.h"
#include "../head/Map.h"

PlayerController* PlayerController::_controller = nullptr;
PlayerController* PlayerController::_secondController = nullptr;

PlayerController::~PlayerController() {
    delete _controller;
    delete _secondController;
}

PlayerController* PlayerController::getPlayerController() {
    if (!_controller) {
        _controller = new PlayerController();
    }

    return _controller;
}

PlayerController* PlayerController::getSecondPlayerController() {
    if (!_secondController) {
        _secondController = new PlayerController();
    }

    return _secondController;
}

void PlayerController::ControllPlayer(Player* player, Map &map, float time, float ones) {
    sf::Vector2f  updated_pos = player->getPosition();
    sf::FloatRect playerRect(player->getSprite().getGlobalBounds());
    sf::FloatRect smallPlayerRect(player->getSprite().getGlobalBounds());
    float         playerSpeed = 0.06 * ones;
    PressedButton pressedButton;
    PressedButton lastPressedButton;
    if (player->getPlayerNumber() == 1)
        lastPressedButton = _pressedButton;
    else
        lastPressedButton = _secondPressedButton;

    std::vector<sf::CircleShape> points = map.getPoints();
    std::vector<sf::Sprite> bombs = map.getBombs();
    std::vector<sf::Sprite> acseleration = map.getAcseleration();

    smallPlayerRect.height -= 18;
    smallPlayerRect.width -= 18;
    smallPlayerRect.top += 18;
    smallPlayerRect.left += 18;

    for (int index = 0; index < points.size(); ++index) {
        if (smallPlayerRect.intersects(points[index].getGlobalBounds())) {
            map.deletePoint(index);

            if (points[index].getRadius() == 8) {
                player->setMadMode();
            }
        }
    }

    for (int index = 0; index < bombs.size(); ++index) {
        if (smallPlayerRect.intersects(bombs[index].getGlobalBounds())) {
            map.deleteBomb(index);
        }
    }

    for (int index = 0; index < acseleration.size(); ++index) {
        if (smallPlayerRect.intersects(acseleration[index].getGlobalBounds())) {
            map.deleteAcseleration(index);
        }
    }

    std::string ctr = player->getControl();
    if (ctr == "WASD") {
        if (player->getPlayerNumber() == 1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->_pressedButton = PressedButton::A;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->_pressedButton = PressedButton::D;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->_pressedButton = PressedButton::W;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->_pressedButton = PressedButton::S;

            pressedButton = _pressedButton;
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) this->_secondPressedButton = PressedButton::A;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) this->_secondPressedButton = PressedButton::D;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) this->_secondPressedButton = PressedButton::W;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) this->_secondPressedButton = PressedButton::S;

            pressedButton = _secondPressedButton;
        }
    }
    else if (ctr == "arrows") {
        if (player->getPlayerNumber() == 1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) this->_pressedButton = PressedButton::A;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) this->_pressedButton = PressedButton::D;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) this->_pressedButton = PressedButton::W;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) this->_pressedButton = PressedButton::S;
            pressedButton = _pressedButton;
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->_secondPressedButton = PressedButton::A;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->_secondPressedButton = PressedButton::D;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->_secondPressedButton = PressedButton::W;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->_secondPressedButton = PressedButton::S;

            pressedButton = _secondPressedButton;
        }
    }

    if (player->getPlayerNumber() == 1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->_pressedButton = PressedButton::A;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->_pressedButton = PressedButton::D;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->_pressedButton = PressedButton::W;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->_pressedButton = PressedButton::S;

        pressedButton = _pressedButton;
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) this->_secondPressedButton = PressedButton::A;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) this->_secondPressedButton = PressedButton::D;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) this->_secondPressedButton = PressedButton::W;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) this->_secondPressedButton = PressedButton::S;

        pressedButton = _secondPressedButton;
    }
    if (player->getPlayerNumber() == 1) {
        if (this->_pressedButton == PressedButton::A) {
            updated_pos.x -= playerSpeed * time;
            playerRect.left = updated_pos.x;
            playerRect.top = updated_pos.y;

            if (!map.isAvailableZone(playerRect))
            {
                if (lastPressedButton == PressedButton::S) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.top += 32;
                    if (block.top - playerRect.top < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top;
                        updated_pos.x = block.left + 32;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::LEFT);
                        return;
                    }
                }
                else if (lastPressedButton == PressedButton::W) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.top -= 32;
                    if (playerRect.top - block.top < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top;
                        updated_pos.x = block.left + 32;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::LEFT);
                        return;
                    }
                }

                _pressedButton = lastPressedButton;

                if (_pressedButton == PressedButton::D) {
                    updated_pos = player->getPosition();
                    updated_pos.x += playerSpeed * time;
                }
                else if (_pressedButton == PressedButton::W) {
                    updated_pos = player->getPosition();
                    updated_pos.y -= playerSpeed * time;
                    playerRect.top = updated_pos.y;
                    playerRect.left = updated_pos.x;
                    if (!map.isAvailableZone(playerRect)) return;
                }
                else if (_pressedButton == PressedButton::S) {
                    updated_pos = player->getPosition();
                    updated_pos.y += playerSpeed * time;
                    playerRect.top = updated_pos.y;
                    playerRect.left = updated_pos.x;
                    if (!map.isAvailableZone(playerRect)) return;
                }

                sf::FloatRect updatedPlayerRect(updated_pos, player->getSize());
                if (!map.isAvailableZone(updatedPlayerRect)) {
                    sf::FloatRect block = map.getIntersectZeroBlock(updatedPlayerRect);
                    if (player->getDirection() == Direction::RIGHT) {
                        updated_pos.x = block.left - 32;
                    }
                    else if (player->getDirection() == Direction::LEFT) {
                        updated_pos.x = block.left + 32;
                    }
                    else if (player->getDirection() == Direction::UP) {
                        updated_pos.y = block.top + 32;
                    }
                    else if (player->getDirection() == Direction::DOWN) {
                        updated_pos.y = block.top - 32;
                    }
                    _pressedButton = PressedButton::STOP;
                    player->setState(State::IDLE);
                }
                player->setPosition(updated_pos);
                return;
            }
            else
            {
                player->setPosition(updated_pos);
                player->setDirection(Direction::LEFT);
                return;
            }
        }
        else if (this->_pressedButton == PressedButton::D) {
            updated_pos.x += playerSpeed * time;
            playerRect.left = updated_pos.x;
            playerRect.top = updated_pos.y;

            if (!map.isAvailableZone(playerRect))
            {
                if (lastPressedButton == PressedButton::S) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.top += 32;
                    if (block.top - playerRect.top < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top;
                        updated_pos.x = block.left - 32;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }
                else if (lastPressedButton == PressedButton::W) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.top -= 32;
                    if (playerRect.top - block.top < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top;
                        updated_pos.x = block.left - 32;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }

                _pressedButton = lastPressedButton;

                if (_pressedButton == PressedButton::A) {
                    updated_pos = player->getPosition();
                    updated_pos.x -= playerSpeed * time;
                }
                else if (_pressedButton == PressedButton::W) {
                    updated_pos = player->getPosition();
                    updated_pos.y -= playerSpeed * time;
                    playerRect.top = updated_pos.y;
                    playerRect.left = updated_pos.x;
                    if (!map.isAvailableZone(playerRect)) return;
                }
                else if (_pressedButton == PressedButton::S) {
                    updated_pos = player->getPosition();
                    updated_pos.y += playerSpeed * time;
                    playerRect.top = updated_pos.y;
                    playerRect.left = updated_pos.x;
                    if (!map.isAvailableZone(playerRect)) return;
                }

                sf::FloatRect updatedPlayerRect(updated_pos, player->getSize());
                if (!map.isAvailableZone(updatedPlayerRect)) {
                    sf::FloatRect block = map.getIntersectZeroBlock(updatedPlayerRect);
                    if (player->getDirection() == Direction::RIGHT) {
                        updated_pos.x = block.left - 32;
                    }
                    else if (player->getDirection() == Direction::LEFT) {
                        updated_pos.x = block.left + 32;
                    }
                    else if (player->getDirection() == Direction::UP) {
                        updated_pos.y = block.top + 32;
                    }
                    else if (player->getDirection() == Direction::DOWN) {
                        updated_pos.y = block.top - 32;
                    }
                    _pressedButton = PressedButton::STOP;
                    player->setState(State::IDLE);
                }
                player->setPosition(updated_pos);
                return;
            }
            else
            {
                player->setPosition(updated_pos);
                player->setDirection(Direction::RIGHT);
                return;
            }
        }
        else if (this->_pressedButton == PressedButton::W) {
            updated_pos.y -= playerSpeed * time;
            playerRect.left = updated_pos.x;
            playerRect.top = updated_pos.y;

            if (!map.isAvailableZone(playerRect))
            {
                if (lastPressedButton == PressedButton::A) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.left -= 32;
                    if (playerRect.left - block.left < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top + 32;
                        updated_pos.x = block.left;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }
                else if (lastPressedButton == PressedButton::D) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.left += 32;
                    if (block.left - playerRect.left < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top + 32;
                        updated_pos.x = block.left;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }

                _pressedButton = lastPressedButton;

                if (_pressedButton == PressedButton::D) {
                    updated_pos = player->getPosition();
                    updated_pos.x += playerSpeed * time;
                    playerRect.left = updated_pos.x;
                    playerRect.top = updated_pos.y;
                    if (!map.isAvailableZone(playerRect)) return;
                }
                else if (_pressedButton == PressedButton::A) {
                    updated_pos = player->getPosition();
                    updated_pos.x -= playerSpeed * time;
                    playerRect.left = updated_pos.x;
                    playerRect.top = updated_pos.y;
                    if (!map.isAvailableZone(playerRect)) return;
                }
                else if (_pressedButton == PressedButton::S) {
                    updated_pos = player->getPosition();
                    updated_pos.y += playerSpeed * time;
                }

                sf::FloatRect updatedPlayerRect(updated_pos, player->getSize());
                if (!map.isAvailableZone(updatedPlayerRect)) {
                    sf::FloatRect block = map.getIntersectZeroBlock(updatedPlayerRect);
                    if (player->getDirection() == Direction::RIGHT) {
                        updated_pos.x = block.left - 32;
                    }
                    else if (player->getDirection() == Direction::LEFT) {
                        updated_pos.x = block.left + 32;
                    }
                    else if (player->getDirection() == Direction::UP) {
                        updated_pos.y = block.top + 32;
                    }
                    else if (player->getDirection() == Direction::DOWN) {
                        updated_pos.y = block.top - 32;
                    }
                    _pressedButton = PressedButton::STOP;
                    player->setState(State::IDLE);
                }
                player->setPosition(updated_pos);
                return;
            }
            else
            {
                player->setPosition(updated_pos);
                player->setDirection(Direction::UP);
                return;
            }
        }
        else if (this->_pressedButton == PressedButton::S) {
            updated_pos.y += playerSpeed * time;
            playerRect.left = updated_pos.x;
            playerRect.top = updated_pos.y;

            if (!map.isAvailableZone(playerRect))
            {
                if (lastPressedButton == PressedButton::A) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.left -= 32;
                    if (playerRect.left - block.left < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top - 32;
                        updated_pos.x = block.left;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }
                else if (lastPressedButton == PressedButton::D) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.left += 32;
                    if (block.left - playerRect.left < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top - 32;
                        updated_pos.x = block.left;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }

                _pressedButton = lastPressedButton;

                if (_pressedButton == PressedButton::D) {
                    updated_pos = player->getPosition();
                    updated_pos.x += playerSpeed * time;
                    playerRect.left = updated_pos.x;
                    playerRect.top = updated_pos.y;
                    if (!map.isAvailableZone(playerRect)) return;
                }
                else if (_pressedButton == PressedButton::W) {
                    updated_pos = player->getPosition();
                    updated_pos.y -= playerSpeed * time;
                }
                else if (_pressedButton == PressedButton::A) {
                    updated_pos = player->getPosition();
                    updated_pos.x -= playerSpeed * time;
                    playerRect.left = updated_pos.x;
                    playerRect.top = updated_pos.y;
                    if (!map.isAvailableZone(playerRect)) return;
                }

                sf::FloatRect updatedPlayerRect(updated_pos, player->getSize());
                if (!map.isAvailableZone(updatedPlayerRect)) {
                    sf::FloatRect block = map.getIntersectZeroBlock(updatedPlayerRect);
                    if (player->getDirection() == Direction::RIGHT) {
                        updated_pos.x = block.left - 32;
                    }
                    else if (player->getDirection() == Direction::LEFT) {
                        updated_pos.x = block.left + 32;
                    }
                    else if (player->getDirection() == Direction::UP) {
                        updated_pos.y = block.top + 32;
                    }
                    else if (player->getDirection() == Direction::DOWN) {
                        updated_pos.y = block.top - 32;
                    }
                    _pressedButton = PressedButton::STOP;
                    player->setState(State::IDLE);
                }
                player->setPosition(updated_pos);
                return;
            }
            else
            {
                player->setPosition(updated_pos);
                player->setDirection(Direction::DOWN);
                return;
            }
        }
    }
    else {
        if (this->_secondPressedButton == PressedButton::A) {
            updated_pos.x -= playerSpeed * time;
            playerRect.left = updated_pos.x;
            playerRect.top = updated_pos.y;

            if (!map.isAvailableZone(playerRect))
            {
                if (lastPressedButton == PressedButton::S) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.top += 32;
                    if (block.top - playerRect.top < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top;
                        updated_pos.x = block.left + 32;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::LEFT);
                        return;
                    }
                }
                else if (lastPressedButton == PressedButton::W) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.top -= 32;
                    if (playerRect.top - block.top < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top;
                        updated_pos.x = block.left + 32;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::LEFT);
                        return;
                    }
                }

                _secondPressedButton = lastPressedButton;

                if (_secondPressedButton == PressedButton::D) {
                    updated_pos = player->getPosition();
                    updated_pos.x += playerSpeed * time;
                }
                else if (_secondPressedButton == PressedButton::W) {
                    updated_pos = player->getPosition();
                    updated_pos.y -= playerSpeed * time;
                    playerRect.top = updated_pos.y;
                    playerRect.left = updated_pos.x;
                    if (!map.isAvailableZone(playerRect)) return;
                }
                else if (_secondPressedButton == PressedButton::S) {
                    updated_pos = player->getPosition();
                    updated_pos.y += playerSpeed * time;
                    playerRect.top = updated_pos.y;
                    playerRect.left = updated_pos.x;
                    if (!map.isAvailableZone(playerRect)) return;
                }

                sf::FloatRect updatedPlayerRect(updated_pos, player->getSize());
                if (!map.isAvailableZone(updatedPlayerRect)) {
                    sf::FloatRect block = map.getIntersectZeroBlock(updatedPlayerRect);
                    if (player->getDirection() == Direction::RIGHT) {
                        updated_pos.x = block.left - 32;
                    }
                    else if (player->getDirection() == Direction::LEFT) {
                        updated_pos.x = block.left + 32;
                    }
                    else if (player->getDirection() == Direction::UP) {
                        updated_pos.y = block.top + 32;
                    }
                    else if (player->getDirection() == Direction::DOWN) {
                        updated_pos.y = block.top - 32;
                    }
                    _secondPressedButton = PressedButton::STOP;
                    player->setState(State::IDLE);
                }
                player->setPosition(updated_pos);
                return;
            }
            else
            {
                player->setPosition(updated_pos);
                player->setDirection(Direction::LEFT);
                return;
            }
        }
        else if (this->_secondPressedButton == PressedButton::D) {
            updated_pos.x += playerSpeed * time;
            playerRect.left = updated_pos.x;
            playerRect.top = updated_pos.y;

            if (!map.isAvailableZone(playerRect))
            {
                if (lastPressedButton == PressedButton::S) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.top += 32;
                    if (block.top - playerRect.top < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top;
                        updated_pos.x = block.left - 32;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }
                else if (lastPressedButton == PressedButton::W) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.top -= 32;
                    if (playerRect.top - block.top < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top;
                        updated_pos.x = block.left - 32;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }

                _secondPressedButton = lastPressedButton;

                if (_secondPressedButton == PressedButton::A) {
                    updated_pos = player->getPosition();
                    updated_pos.x -= playerSpeed * time;
                }
                else if (_secondPressedButton == PressedButton::W) {
                    updated_pos = player->getPosition();
                    updated_pos.y -= playerSpeed * time;
                    playerRect.top = updated_pos.y;
                    playerRect.left = updated_pos.x;
                    if (!map.isAvailableZone(playerRect)) return;
                }
                else if (_secondPressedButton == PressedButton::S) {
                    updated_pos = player->getPosition();
                    updated_pos.y += playerSpeed * time;
                    playerRect.top = updated_pos.y;
                    playerRect.left = updated_pos.x;
                    if (!map.isAvailableZone(playerRect)) return;
                }

                sf::FloatRect updatedPlayerRect(updated_pos, player->getSize());
                if (!map.isAvailableZone(updatedPlayerRect)) {
                    sf::FloatRect block = map.getIntersectZeroBlock(updatedPlayerRect);
                    if (player->getDirection() == Direction::RIGHT) {
                        updated_pos.x = block.left - 32;
                    }
                    else if (player->getDirection() == Direction::LEFT) {
                        updated_pos.x = block.left + 32;
                    }
                    else if (player->getDirection() == Direction::UP) {
                        updated_pos.y = block.top + 32;
                    }
                    else if (player->getDirection() == Direction::DOWN) {
                        updated_pos.y = block.top - 32;
                    }
                    _secondPressedButton = PressedButton::STOP;
                    player->setState(State::IDLE);
                }
                player->setPosition(updated_pos);
                return;
            }
            else
            {
                player->setPosition(updated_pos);
                player->setDirection(Direction::RIGHT);
                return;
            }
        }
        else if (this->_secondPressedButton == PressedButton::W) {
            updated_pos.y -= playerSpeed * time;
            playerRect.left = updated_pos.x;
            playerRect.top = updated_pos.y;

            if (!map.isAvailableZone(playerRect))
            {
                if (lastPressedButton == PressedButton::A) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.left -= 32;
                    if (playerRect.left - block.left < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top + 32;
                        updated_pos.x = block.left;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }
                else if (lastPressedButton == PressedButton::D) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.left += 32;
                    if (block.left - playerRect.left < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top + 32;
                        updated_pos.x = block.left;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }

                _secondPressedButton = lastPressedButton;

                if (_secondPressedButton == PressedButton::D) {
                    updated_pos = player->getPosition();
                    updated_pos.x += playerSpeed * time;
                    playerRect.left = updated_pos.x;
                    playerRect.top = updated_pos.y;
                    if (!map.isAvailableZone(playerRect)) return;
                }
                else if (_secondPressedButton == PressedButton::A) {
                    updated_pos = player->getPosition();
                    updated_pos.x -= playerSpeed * time;
                    playerRect.left = updated_pos.x;
                    playerRect.top = updated_pos.y;
                    if (!map.isAvailableZone(playerRect)) return;
                }
                else if (_secondPressedButton == PressedButton::S) {
                    updated_pos = player->getPosition();
                    updated_pos.y += playerSpeed * time;
                }

                sf::FloatRect updatedPlayerRect(updated_pos, player->getSize());
                if (!map.isAvailableZone(updatedPlayerRect)) {
                    sf::FloatRect block = map.getIntersectZeroBlock(updatedPlayerRect);
                    if (player->getDirection() == Direction::RIGHT) {
                        updated_pos.x = block.left - 32;
                    }
                    else if (player->getDirection() == Direction::LEFT) {
                        updated_pos.x = block.left + 32;
                    }
                    else if (player->getDirection() == Direction::UP) {
                        updated_pos.y = block.top + 32;
                    }
                    else if (player->getDirection() == Direction::DOWN) {
                        updated_pos.y = block.top - 32;
                    }
                    _secondPressedButton = PressedButton::STOP;
                    player->setState(State::IDLE);
                }
                player->setPosition(updated_pos);
                return;
            }
            else
            {
                player->setPosition(updated_pos);
                player->setDirection(Direction::UP);
                return;
            }
        }
        else if (this->_secondPressedButton == PressedButton::S) {
            updated_pos.y += playerSpeed * time;
            playerRect.left = updated_pos.x;
            playerRect.top = updated_pos.y;

            if (!map.isAvailableZone(playerRect))
            {
                if (lastPressedButton == PressedButton::A) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.left -= 32;
                    if (playerRect.left - block.left < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top - 32;
                        updated_pos.x = block.left;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }
                else if (lastPressedButton == PressedButton::D) {
                    sf::FloatRect block = map.getIntersectZeroBlock(playerRect);
                    block.left += 32;
                    if (block.left - playerRect.left < 1 && map.isAvailableZone(block)) {
                        updated_pos.y = block.top - 32;
                        updated_pos.x = block.left;
                        player->setPosition(updated_pos);
                        player->setDirection(Direction::RIGHT);
                        return;
                    }
                }

                _secondPressedButton = lastPressedButton;

                if (_secondPressedButton == PressedButton::D) {
                    updated_pos = player->getPosition();
                    updated_pos.x += playerSpeed * time;
                    playerRect.left = updated_pos.x;
                    playerRect.top = updated_pos.y;
                    if (!map.isAvailableZone(playerRect)) return;
                }
                else if (_secondPressedButton == PressedButton::W) {
                    updated_pos = player->getPosition();
                    updated_pos.y -= playerSpeed * time;
                }
                else if (_secondPressedButton == PressedButton::A) {
                    updated_pos = player->getPosition();
                    updated_pos.x -= playerSpeed * time;
                    playerRect.left = updated_pos.x;
                    playerRect.top = updated_pos.y;
                    if (!map.isAvailableZone(playerRect)) return;
                }

                sf::FloatRect updatedPlayerRect(updated_pos, player->getSize());
                if (!map.isAvailableZone(updatedPlayerRect)) {
                    sf::FloatRect block = map.getIntersectZeroBlock(updatedPlayerRect);
                    if (player->getDirection() == Direction::RIGHT) {
                        updated_pos.x = block.left - 32;
                    }
                    else if (player->getDirection() == Direction::LEFT) {
                        updated_pos.x = block.left + 32;
                    }
                    else if (player->getDirection() == Direction::UP) {
                        updated_pos.y = block.top + 32;
                    }
                    else if (player->getDirection() == Direction::DOWN) {
                        updated_pos.y = block.top - 32;
                    }
                    _secondPressedButton = PressedButton::STOP;
                    player->setState(State::IDLE);
                }
                player->setPosition(updated_pos);
                return;
            }
            else
            {
                player->setPosition(updated_pos);
                player->setDirection(Direction::DOWN);
                return;
            }
        }
    }

    sf::FloatRect updatedPlayerRect(updated_pos, player->getSize());
    if (!map.isAvailableZone(updatedPlayerRect)) {
        sf::FloatRect block = map.getIntersectZeroBlock(updatedPlayerRect);
        if (player->getDirection() == Direction::RIGHT) {
            updated_pos.x = block.left - 32;
        }
        else if (player->getDirection() == Direction::LEFT) {
            updated_pos.x = block.left + 32;
        }
        else if (player->getDirection() == Direction::UP) {
            updated_pos.y = block.top + 32;
        }
        else if (player->getDirection() == Direction::DOWN) {
            updated_pos.y = block.top - 32;
        }
    }

    player->setPosition(updated_pos);
}