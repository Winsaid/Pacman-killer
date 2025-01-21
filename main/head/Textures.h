#pragma once

#include <SFML/Graphics.hpp>

namespace textures {
	sf::Texture playerTexture;

	static void setTextures() {
		playerTexture.loadFromFile("../../../../images/pacman-sheet.png");
	}
}
