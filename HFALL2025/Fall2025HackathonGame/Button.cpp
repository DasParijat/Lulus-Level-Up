#include "Button.h"
#include "TextureHolder.h"
#include <iostream>

sf::FloatRect Button::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

sf::Sprite Button::getSprite()
{
	if (!isVisible) {
		sprite.setColor(sf::Color(255, 255, 255, 0));
	}
	else {
		sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	return sprite;
}

bool Button::buttonHandling(sf::RenderWindow& window, sf::Event& event, float dt)
{
	if (isClicked) {
		timeSinceClick += dt;
		if (timeSinceClick >= 1.0f);
			sprite.setTexture(TextureHolder::GetTexture(defaultTexture));
			isClicked = false;
			timeSinceClick = 0.0f;
	}

	// Check for mouse hover
	if (event.type == sf::Event::MouseMoved) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
			sprite.setTexture(TextureHolder::GetTexture(hoverTexture));
		}
	}

	// Check for mouse click
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
			sprite.setTexture(TextureHolder::GetTexture(clickedTexture));
			isClicked = true;
		}
	}

	return isClicked;
}
