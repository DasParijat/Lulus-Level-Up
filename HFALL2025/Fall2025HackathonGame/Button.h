#pragma once
#include "SFML/Graphics.hpp"

class Button {
protected:
	sf::Sprite sprite;
	bool isVisible = true;
	bool isClicked = false;
	float timeSinceClick = 0.0f;

	std::string defaultTexture = "graphics/lulu1.jpg";
	std::string hoverTexture = "graphics/lulu2.jpg";
	std::string clickedTexture = "graphics/lulu3.jpg";

public:
	Button();
	
	sf::FloatRect getGlobalBounds();
	sf::Sprite getSprite();
	void setPosition(sf::Vector2f position);

	void setVisibility(bool isVisible);

	bool buttonHandling(sf::RenderWindow& window, sf::Event& event, float dt);
};