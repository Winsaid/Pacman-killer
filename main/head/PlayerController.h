#pragma once

#include "Map.h"

class Player;

enum PressedButton {
	W,
	A,
	S,
	D,
	STOP
};

class PlayerController {
public:
	PlayerController(const PlayerController& controller) = delete;
	PlayerController& operator=(const PlayerController& other) = delete;
	~PlayerController();

	static PlayerController* getPlayerController();
	void ControllPlayer(Player* player, Map &map, float time);
	PressedButton getPressedButton() { return _pressedButton; }

private:
	PlayerController() = default;
	static PlayerController* _controller;
	PressedButton _pressedButton = STOP;
};
