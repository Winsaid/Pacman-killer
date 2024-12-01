#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include "../head/class_button.h"
#include <iostream>
#include <vector>


class Authors {
	sf::Font _font;
	sf::Color _textColor;
	sf::Color _backColor;
	int _textSize = 75;
public:
	std::vector<Button> buttons;
	sf::Texture backTexture;
	sf::Sprite backSprite;
	int setBack() {
		if (!backTexture.loadFromFile("../../../../images/authors.png"))return 0;
		backSprite.setTexture(backTexture);
		backSprite.setPosition(0, -120);
	}
	std::vector<sf::Text> setDevText() {
		std::vector<sf::Text> text;
		sf::Text createdBy = setText("Created by Legend Trio:", 50, &_font, _textColor);
		sf::Text developerText  = setText("Winsaid",30, &_font, _textColor);
		sf::Text developerText2 = setText("Sonador",30, &_font, _textColor);
		sf::Text developerText3 = setText("Wave78", 30, &_font, _textColor);
		createdBy.setPosition(550, 20);
		developerText.setPosition(900, 120);
		developerText2.setPosition(900, 220);
		developerText3.setPosition(900, 320);
		text.push_back(createdBy);
		text.push_back(developerText);
		text.push_back(developerText2);
		text.push_back(developerText3);
		return text;
	}
	Authors(sf::Font font, sf::Color textColor, sf::Color backColor) : _font(font), _textColor(textColor), _backColor(backColor) {
		
		Button BackButton(
			setText(std::string("Back"), 75, &_font, _textColor),
			setRectangle(sf::Vector2f(250, 100), _backColor, sf::Vector2f(100, 730)),
			"Back To Menu"
		);
		buttons.push_back(BackButton);
	}
};