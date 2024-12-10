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
	void setMadMode() { timerForMad.restart(); }
	
	PlayerController* getController() { return _controller; }
	bool getMode();
	float getTime();

private:
	sf::Clock timerForMad;
	State             _state = State::IDLE;
	PlayerController* _controller;
};
