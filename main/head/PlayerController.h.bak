#pragma once

#include "Map.h"

class Player;

enum PressedButton {
	W,
	A,
	S,
	D,
	STOP,
};

class PlayerController {
public:
	PlayerController(const PlayerController& controller) = delete;
	PlayerController& operator=(const PlayerController& other) = delete;
	~PlayerController();

	void setPressedButton(PressedButton button) { _pressedButton = button; }

	static PlayerController* getPlayerController();
	static PlayerController* getSecondPlayerController();
	void ControllPlayer(Player* player, Map &map, float time);
	PressedButton getPressedButton() { return _pressedButton; }

private:
	PlayerController() = default;
	static PlayerController* _controller;
	static PlayerController* _secondController;
	PressedButton _pressedButton = PressedButton::A;
	PressedButton _secondPressedButton = PressedButton::A;
};
