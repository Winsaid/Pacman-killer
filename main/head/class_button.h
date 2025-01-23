#pragma once

#include "SFML/Graphics.hpp"
#include "GameState.h"
#include <string>

sf::RectangleShape setRectangle(sf::Vector2f size, sf::Color color, sf::Vector2f position = sf::Vector2f(0, 0));
sf::Text setText(std::string text, int size, const sf::Font* font, sf::Color color);
int TextToInt(sf::Text content);
sf::Text IntToText(int content);

class Button : public sf::Drawable {
public:
	Button() = delete;
	Button(sf::Text content, sf::RectangleShape button, std::string textString, GameState state);
	~Button() {};

	void setWidth(int width) { this->_button.setSize(sf::Vector2f(width, this->getHeight())); }
	void setHeight(int height) { this->_button.setSize(sf::Vector2f(this->getWidth(), height)); }
	void setContent(sf::Text content) { this->_content.setString(content.getString()); };
	void setPosition(sf::Vector2f vector);

	int getWidth() { return this->_button.getSize().x; }
	int getHeight() { return this->_button.getSize().y; }
	sf::Text getContent() { return this->_content; }
	sf::Vector2f getPosition() { return this->_button.getPosition(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(_button, states);
		target.draw(_content, states);
	}

	std::string getText() { return _textString; }
	sf::RectangleShape getShape() { return _button; }

	sf::FloatRect getGlobalBounds() const { return _button.getGlobalBounds(); }

	GameState getGameState() {
		return this->_state;
	}

	void setGameState(GameState state) {
		_state = state;
	}
	void setOutline(int pixels, sf::Color color) { _button.setOutlineThickness(pixels); _button.setOutlineColor(color); }
	void setString(std::string string) { this->_textString = string; };
	std::string getString() { return this->_textString; };
private:
	std::string _textString;
	sf::Text _content;
	sf::RectangleShape _button;
	GameState _state;
};