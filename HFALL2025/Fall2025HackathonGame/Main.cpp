#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

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
	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();

	}
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

	window.display();
}

void initializeGame() {
	
}

void finalizeGame() {
	/*
	for (auto obj : gameObjects) {
		delete obj; // frees memory that was pointed to
	}
	gameObjects.clear();
	*/
}