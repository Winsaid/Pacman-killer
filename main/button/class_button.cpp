#include "class_button.h"

Button::Button(sf::Text content, sf::RectangleShape button)
	: _content(content), _button(button)
{
	int textXSize = this->_content.getLocalBounds().width;
	int textYSize = this->_content.getLocalBounds().height;

	if (textXSize > this->_button.getSize().x)
		this->_button.setSize(sf::Vector2f(textXSize, this->_button.getSize().y));

	if (textYSize > this->_button.getSize().y)
		this->_button.setSize(sf::Vector2f(this->_button.getSize().x, textYSize));

	int contentXPosition = this->getPosition().x + (this->getWidth() - this->_content.getLocalBounds().width) / 2;
	int contentYPosition = this->getPosition().y;
	this->_content.setPosition(sf::Vector2f(contentXPosition, contentYPosition));
}

void Button::setPosition(sf::Vector2f position)
{
	int contentXPosition = position.x + (this->getWidth() - this->_content.getLocalBounds().width) / 2;
	int contentYPosition = position.y;
	this->_button.setPosition(position);
	this->_content.setPosition(sf::Vector2f(contentXPosition, contentYPosition));
}

sf::Text setText(std::string text, int size, const sf::Font* font, sf::Color color)
{
	sf::Text producedText;
	producedText.setString(text);
	producedText.setCharacterSize(size);
	producedText.setFont(*font);
	producedText.setFillColor(color);
	return producedText;
}

sf::RectangleShape setRectangle(sf::Vector2f size, sf::Color color, sf::Vector2f position)
{
	sf::RectangleShape rectangle(size);
	rectangle.setFillColor(color);
	rectangle.setPosition(position);
	return rectangle;
}
