#include "Button.h"
#include "TextureHolder.h"
#include <iostream>

using namespace std;

Button::Button()
{
	sprite = sf::Sprite(TextureHolder::GetTexture(defaultTexture));

}

sf::FloatRect Button::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

sf::Sprite Button::getSprite()
{
	if (!isVisible) {
		sprite.setColor(sf::Color(255, 255, 255, 127));
	}
	else {
		sprite.setColor(sf::Color(255, 255, 255, 255));
	}

	return sprite;
}

void Button::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

void Button::setVisibility(bool isVisible)
{
	this->isVisible = isVisible;
}


bool Button::buttonHandling(sf::RenderWindow& window, sf::Event& event, float dt)
{
	isClicked = false;
	if (isClicked) {
		timeSinceClick += dt;
		if (timeSinceClick >= 0.1f) {
			sprite.setTexture(TextureHolder::GetTexture(defaultTexture));
			timeSinceClick = 0.0f;
		}
	}

	// Return current isClicked value if invisible
	if (!isVisible) return false;

	// Check for mouse hover
	if (event.type == sf::Event::MouseMoved) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
			sprite.setTexture(TextureHolder::GetTexture(hoverTexture));
		}
		else {
			sprite.setTexture(TextureHolder::GetTexture(defaultTexture));
		}
	}

	// Check for mouse click
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
			// sprite.setTexture(TextureHolder::GetTexture(clickedTexture));
			isClicked = true;
		}
	}

	return isClicked;
}
