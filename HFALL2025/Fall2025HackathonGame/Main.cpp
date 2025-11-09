#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "Task.h"
#include "TextInput.h"
#include "Mascot.h"
#include "TextureHolder.h"


using namespace sf;
using namespace std;

// Text
TextureHolder holder;

Mascot lulu;

Font font;
Text userInput;
sf::String inputString;
TextInput userBox;

void gameLoop(RenderWindow& window);
void handleInput(RenderWindow& window, float dt);
void updateGame(float dt);
void renderScene(RenderWindow& window);

void initializeGame();
void finalizeGame();

Button menuButton;

int main() {
	VideoMode vm(800, 600);
	RenderWindow window(vm, "Fall 2025 HACKATHON");

	View view(FloatRect(0, 0, 800, 600));
	window.setView(view);

	
	while (window.isOpen()) {
		Clock clock;
		sf::Event event;
		float dt = clock.restart().asSeconds();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			menuButton.buttonHandling(window, event, dt);
		}

		window.clear();
		window.draw(menuButton.getSprite());
		lulu.draw(window);
		window.display();
	}
	

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
		handleInput(window, dt);
		// updateGame(dt);
		renderScene(window);
	}

	finalizeGame();

}

void handleInput(RenderWindow& window, float dt) {
	Event event;
	while (window.pollEvent(event)) {
		menuButton.buttonHandling(window, event, dt);
		userBox.handleEvent(event);

		switch (event.type) {
		case Event::Closed:
			window.close();
			return;
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape) {
				window.close();
				return;
			}

			//case Event::TextEntered:
			//	if (event.text.unicode == 8 && !inputString.isEmpty()) {
			//		// Handle backspace
			//		inputString.erase(inputString.getSize() - 1, 1);
			//	}
			//	else if (event.text.unicode < 128 && event.text.unicode != 8) {
			//		// Add normal characters (ASCII only)
			//		inputString += static_cast<char>(event.text.unicode);
			//	}
			//	userInput.setString(inputString);
			//	break;

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

	// Draw background or static UI
	// window.draw(counter);

	// Draw interactive buttons
	window.draw(menuButton.getSprite());

	// Draw the text input box last so it’s visible above the button
	userBox.draw(window);

	// Display everything
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

	menuButton.setPosition(Vector2f(30, 30));

	userBox.setFont(font);
	userBox.setPosition(50.f, 520.f);  // near bottom of an 800×600 window
	userBox.setBoxSize(700.f, 40.f);   // fill most of width

	Task demoTask("Hackathon Demo", 9, 11, 2025, 3);
	int points = demoTask.complete();

	auto timeT = std::chrono::system_clock::to_time_t(demoTask.getDueDate());
	std::tm localTm{};
	localtime_s(&localTm, &timeT);

	std::ostringstream oss;
	oss << "Task: Hackathon Demo\n"
		<< "Due: " << std::put_time(&localTm, "%b %d, %Y %H:%M") << "\n"
		<< "Points if completed: " << points;

	userInput.setString(oss.str());


}

void finalizeGame() {
	/*
	for (auto obj : gameObjects) {
		delete obj; // frees memory that was pointed to
	}
	gameObjects.clear();
	*/
}