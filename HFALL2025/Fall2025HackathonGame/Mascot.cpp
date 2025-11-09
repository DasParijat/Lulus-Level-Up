#include "Mascot.h"
#include "TextureHolder.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;

Mascot::Mascot() {

	ifstream inputFile("gamedata/level.txt");
	if (inputFile.is_open()) {
		inputFile >> level;
		inputFile.close();
	} // if file open

	updateImage();

	sprite.setPosition(0, 350);

	textbox.setSize(Vector2f(250, 50));
	textbox.setPosition(0, 550);
	textbox.setOutlineColor(Color::White);
	textbox.setOutlineThickness(3);
	textbox.setFillColor(Color::Black);

} // constructor

int Mascot::levelUp() {
	level++;
	updateImage();
	ofstream outputFile("gamedata/level.txt");
	if (outputFile.is_open()) {
		outputFile << level;
		outputFile.close();
	} // if file open
	return level;
} // levelUp

void Mascot::updateImage() {
	stringstream streamFile;
	int levelPic = level;
	if (levelPic > 6) {
		levelPic = 6;
	} // if over 6
	streamFile <<
		"graphics/lulu" <<
		levelPic <<
		".jpg";
	sprite = Sprite(TextureHolder::GetTexture(streamFile.str()));
	sprite.setPosition(0, 350);
} // updateImage

int Mascot::getLevel() {
	return level;
} // getLevel

void Mascot::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(textbox);
} // draw
