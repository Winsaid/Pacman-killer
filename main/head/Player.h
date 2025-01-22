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
	Player(sf::Texture& texture, sf::Vector2f start_pos, int playerNumber);

	void Update(Map &map, float time, float timeForMove);
	void setState(State state) { _state = state; }
	void setMadMode();
	void unsetMadMode();
	
	PlayerController* getController() { return _controller; }
	bool getMode();
	float getTime();
	int getPlayerNumber() { return _playerNumber; }

private:
	int _playerNumber;
	sf::Clock         _timerForMad;
	State             _state = State::IDLE;
	PlayerController* _controller;
	bool              _madMode = false;
};
