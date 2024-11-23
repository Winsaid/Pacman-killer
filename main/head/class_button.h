#pragma once

#include "SFML/Graphics.hpp"
#include <string>

sf::RectangleShape setRectangle(sf::Vector2f size, sf::Color color, sf::Vector2f position = sf::Vector2f(0, 0));
sf::Text setText(std::string text, int size, const sf::Font* font, sf::Color color);

class Button : public sf::Drawable {
public:
	Button() = delete;
	Button(sf::Text content, sf::RectangleShape button);
	~Button() {};

	void setWidth(int width) { this->_button.setSize(sf::Vector2f(width, this->getHeight())); }
	void setHeight(int height) { this->_button.setSize(sf::Vector2f(this->getWidth(), height)); }
	void setContent(sf::Text content) { this->_content = content; };
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

private:
	sf::Text _content;
	sf::RectangleShape _button;
};
