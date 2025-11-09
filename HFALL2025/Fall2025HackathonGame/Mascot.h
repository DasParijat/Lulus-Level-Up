#pragma once
#include "SFML/Graphics.hpp"

class Mascot {

private:
	sf::Sprite sprite;
	sf::RectangleShape textbox;
	int level = 1;

public:
	Mascot();
	void levelUp();
	void updateImage();
	int getLevel();
	void draw(sf::RenderWindow& window);
};
