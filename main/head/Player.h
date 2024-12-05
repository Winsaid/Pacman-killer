#pragma once

#include "Character.h"
#include "PlayerController.h"
#include "Map.h"

enum State {
	IDLE,
	RUN
};

class Player : public Character {
public:
	Player() = delete;
	Player(sf::Texture& texture, sf::Vector2f start_pos);
	~Player();

	void Update(Map &map, float time, float timeForMove);
	void setState(State state) { _state = state; }
	PlayerController* getController() { return _controller; }

private:
	State             _state = State::IDLE;
	PlayerController* _controller;
};