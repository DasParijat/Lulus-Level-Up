#pragma once
#include "SFML/Graphics.hpp"

class Mascot {

private:
	sf::Sprite sprite;
	sf::RectangleShape textbox;
	int level = 1;

public:
	Mascot();
	int levelUp();
	void updateImage();
	int getLevel();
	void draw(sf::RenderWindow& window);
};
