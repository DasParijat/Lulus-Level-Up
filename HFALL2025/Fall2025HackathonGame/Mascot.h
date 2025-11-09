#pragma once
#include <SFML/Graphics.hpp>

class Mascot {

private:
	sf::Sprite sprite;
	sf::RectangleShape textbox;
	int level;

public:
	Mascot();
	void levelUp();
};
