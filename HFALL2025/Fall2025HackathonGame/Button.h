#pragma once
#include "SFML/Graphics.hpp"

class Button {
protected:
	sf::Sprite sprite;
	bool isVisible = true;
	bool isClicked = false;
	float timeSinceClick = 0.0f;

	std::string defaultTexture = "graphics/lulu1.jpeg";
	std::string hoverTexture = "graphics/lulu2.jpeg";
	std::string clickedTexture = "graphics/lulu3.jpeg";

public:
	
	sf::FloatRect getGlobalBounds();
	sf::Sprite getSprite();

	bool buttonHandling(sf::RenderWindow& window, sf::Event& event, float dt);
};