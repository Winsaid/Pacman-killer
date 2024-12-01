#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include "../head/class_button.h"
#include <iostream>
#include <vector>


class options {
	sf::Font _font;
	sf::Color _textColor;
	sf::Color _backColor;
	int _textSize = 75;
public:
	std::vector<Button> buttons;
	options(sf::Font font, sf::Color textColor, sf::Color backColor): _font(font),_textColor(textColor), _backColor(backColor) {
		Button SelectNameButton(
			setText(std::string("Select Name"), 75, &_font, _textColor),
			setRectangle(sf::Vector2f(250, 100), _backColor, sf::Vector2f(100, 250)),
			"SelectName"
		);

		Button SelectColorButton(
			setText(std::string("Select Color"), 75, &_font, _textColor),
			setRectangle(sf::Vector2f(355, 100), _backColor, sf::Vector2f(100, 370)),
			"Select Color"
		);

		Button SelectMazeButton(
			setText(std::string("Select Maze"), 75, &_font, _textColor),
			setRectangle(sf::Vector2f(432, 100), _backColor, sf::Vector2f(100, 490)),
			"Select Maze"
		);

		Button SelectLifesButton(
			setText(std::string("Select Lifes"), 75, &_font, _textColor),
			setRectangle(sf::Vector2f(250, 100), _backColor, sf::Vector2f(100, 610)),
			"Select Lifes"
		);

		Button BackButton(
			setText(std::string("Back"), 75, &_font, _textColor),
			setRectangle(sf::Vector2f(250, 100), _backColor, sf::Vector2f(100, 730)),
			"Back To Menu"
		);
		buttons.push_back(SelectNameButton);
		buttons.push_back(SelectColorButton);
		buttons.push_back(SelectMazeButton);
		buttons.push_back(SelectLifesButton);
		buttons.push_back(BackButton);
	}
};