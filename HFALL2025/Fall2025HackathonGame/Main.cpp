#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

// Text
Font font;
Text userInput;
sf::String inputString;



void gameLoop(RenderWindow& window);
void handleInput(RenderWindow& window);
void updateGame(float dt);
void renderScene(RenderWindow& window);

void initializeGame();
void finalizeGame();


int main() {
	VideoMode vm(1024, 1024);
	RenderWindow window(vm, "Fall 2025 HACKATHON");

	View view(FloatRect(0, 0, 1024, 1024));
	window.setView(view);

	// TODO fix up game loop when hackathon starts
	// initializeGame();
	gameLoop(window);
	// finalizeGame();

	return 0;
}

void gameLoop(RenderWindow& window) {
	Clock clock;

	initializeGame();

	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();
		handleInput(window);
		updateGame(dt);
		renderScene(window);
	}

	finalizeGame();

}

void handleInput(RenderWindow& window) {
	Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case Event::Closed:
			window.close();
			return;
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape) {
				window.close();
				return;
			}

		case Event::TextEntered:
			if (event.text.unicode == 8 && !inputString.isEmpty()) {
				// Handle backspace
				inputString.erase(inputString.getSize() - 1, 1);
			}
			else if (event.text.unicode < 128 && event.text.unicode != 8) {
				// Add normal characters (ASCII only)
				inputString += static_cast<char>(event.text.unicode);
			}
			userInput.setString(inputString);
			break;

		default:
			break;
		}
	}
}

void updateGame(float dt) {

	/*
	for (auto obj : gameObjects) {
		obj->update(dt);
	}
	checkCollisions(gameObjects);
	*/
}

void renderScene(RenderWindow& window) {
	window.clear();

	// window.draw(counter);
	window.draw(userInput);
	window.display();
}

void initializeGame() {
	
	if (!font.loadFromFile("fonts/HappyHalloween.ttf")) {
		cout << "Error loading font\n";
	}

	userInput.setFont(font);
	userInput.setCharacterSize(30);
	userInput.setFillColor(Color::White);
	userInput.setPosition(50, 900);
	userInput.setString("");

}

void finalizeGame() {
	/*
	for (auto obj : gameObjects) {
		delete obj; // frees memory that was pointed to
	}
	gameObjects.clear();
	*/
}