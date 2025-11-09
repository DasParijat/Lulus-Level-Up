#pragma once
#include "SFML/Graphics.hpp"

class Button {
protected:
	sf::Sprite sprite;
	bool isVisible = false;
	bool isClicked = false;
	float timeSinceClick = 0.0f;

	std::string defaultTexture = "graphics/buttonDefault.png";
	std::string hoverTexture = "graphics/buttonHover.png";
	std::string clickedTexture = "graphics/buttonClicked.png";

public:
	Button();
	
	sf::FloatRect getGlobalBounds();
	sf::Sprite getSprite();
	void setPosition(sf::Vector2f position);

	void setVisibility(bool isVisible);

	bool buttonHandling(sf::RenderWindow& window, sf::Event& event, float dt);
};