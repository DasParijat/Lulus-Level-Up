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

//--- Globals --//
TextureHolder holder;
Mascot lulu;

// Text
Font font;
Text userInput;
sf::String inputString;
TextInput userBox;
Text luluText;
Text levelText;

float textUpdate;
float progTimeTotal;

int points;
int maxPoints;

RectangleShape levelBar;
RectangleShape levelToGoBar;

//Tasks
std::vector<Task> taskList;  // store created tasks

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
		updateGame(dt);
		renderScene(window);
	}

	finalizeGame();

}

void handleInput(RenderWindow& window, float dt) {
	Event event;
	while (window.pollEvent(event)) {
		if (taskList.size() <= 0) {
			menuButton.setVisibility(false);
		}
		else {
			menuButton.setVisibility(true);
		}

		if (menuButton.buttonHandling(window, event, dt)) {
			points += taskList.front().complete();
			taskList.erase(taskList.begin());
			cout << points << endl;
		}

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
			/*
			if (event.key.code == Keyboard::Space) {
				points += 10;
				return;
			} */

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

	// After processing events
	if (userBox.hasSubmitted) {
		std::string taskTitle = userBox.getString();
		userBox.clear();
		userBox.hasSubmitted = false;

		// Create a new Task with today�s date and difficulty 1 (for now)
		time_t now = time(0);
		tm local{};
		localtime_s(&local, &now);  // thread-safe version

		int day = local.tm_mday;
		int month = local.tm_mon + 1;
		int year = local.tm_year + 1900;

		Task newTask(taskTitle, day, month, year);
		taskList.push_back(newTask);

		std::cout << "Created Task: " << taskTitle << std::endl;
	}

}

void updateGame(float dt) {

	progTimeTotal += dt;

	// Check if leveled up
	if (points >= maxPoints) {
		int level = lulu.levelUp();
		points -= maxPoints;
		maxPoints += 5;
		if (maxPoints > 50) {
			maxPoints = 50;
		} // maxPoints cap
		switch (level) {
		case 2:
			luluText.setString("Wow!! You're so\nhard at work!");
			break;
		case 3:
			luluText.setString("I put on a dress to\ncelebrate your victory!");
			break;
		case 4:
			luluText.setString("Your progress makes\nme smile!");
			break;
		case 5:
			luluText.setString("I'm so happy for you!!");
			break;
		case 6:
			luluText.setString("Thanks to you, I have\nbecome a task god.");
			break;
		default:
			luluText.setString("Another level up!");
			break;
		}
		textUpdate = progTimeTotal + (rand() % 10 + 5);
	}

	// update luluText
	if (textUpdate <= progTimeTotal) {
		int randNum = rand() % 10 + 1;
		switch (randNum) {
		case 1:
			luluText.setString("You can do it!");
			break;
		case 2:
			luluText.setString("Feed me tasks!");
			break;
		case 3:
			luluText.setString("With every task you do,\nmy power grows...");
			break;
		case 4:
			luluText.setString("Bark bark.");
			break;
		case 5:
			luluText.setString("You seem way too busy to\nplay. Keep going!");
			break;
		case 6:
			luluText.setString("I chewed on some of\nyour tasks. Sorry.");
			break;
		case 7:
			luluText.setString("Don't forget anything!");
			break;
		case 8:
			luluText.setString("How long til we\nlevel up??");
			break;
		case 9:
			luluText.setString("I'm bored.\nCan we do a task?");
			break;
		case 10:
			luluText.setString("I want a treat. The\ntreat is tasks!");
			break;
		}
		textUpdate = progTimeTotal + (rand() % 10 + 5);

	}

	// Update levelText
	stringstream streamLevel;
	streamLevel <<
		"Level: " <<
		lulu.getLevel();
	levelText.setString(streamLevel.str());

	// Update level bar
	levelBar.setSize(Vector2f(200 / maxPoints * points, 20));
}

void renderScene(RenderWindow& window) {
	window.clear();

	// Draw background or static UI
	// window.draw(counter);

	lulu.draw(window);
	window.draw(luluText);
	window.draw(levelText);
	window.draw(levelToGoBar);
	window.draw(levelBar);

	// Draw interactive buttons
	window.draw(menuButton.getSprite());


	//---- Start tasky loop -------//
	float y = 50.f;
	for (const auto& t : taskList) {

		// Sticky note background
		sf::RectangleShape noteBox(sf::Vector2f(300.f, 80.f));
		noteBox.setPosition(450, y);

		// Color
		noteBox.setFillColor(sf::Color(134, 52, 140));
		noteBox.setOutlineColor(sf::Color(168, 0, 173));
		noteBox.setOutlineThickness(2.f);

		// Drop shadow
		sf::RectangleShape shadow(noteBox);
		shadow.move(5.f, 5.f);
		shadow.setFillColor(sf::Color(0, 0, 0, 60));

		// Task text
		sf::Text titleText;
		titleText.setFont(font);
		titleText.setCharacterSize(20);
		titleText.setFillColor(sf::Color::White);
		titleText.setString(t.getTitle());
		titleText.setPosition(noteBox.getPosition().x + 10.f, noteBox.getPosition().y + 10.f);

		// Draw shadow, box, and text
		window.draw(shadow);
		window.draw(noteBox);
		window.draw(titleText);

		y += 100.f;  // space between notes
	}
	//---- End tasky loop -------//

	// Draw the text input box last so it�s visible above the button
	userBox.draw(window);

	// Display everything
	window.display();
}

void initializeGame() {

	srand(int(0));

	if (!font.loadFromFile("fonts/HappyHalloween.ttf")) {
		cout << "Error loading font\n";
	}

	luluText.setFont(font);
	luluText.setCharacterSize(20);
	luluText.setFillColor(Color::White);
	luluText.setPosition(25, 550);
	luluText.setString("I'm so excited to be\nyour task manager!");

	levelText.setFont(font);
	levelText.setCharacterSize(25);
	levelText.setFillColor(Color::White);
	levelText.setPosition(80, 280);

	levelToGoBar.setFillColor(Color(168, 0, 173));
	levelToGoBar.setPosition(25, 320);
	levelToGoBar.setSize(Vector2f(200, 20));
	levelBar.setFillColor(Color(255, 61, 203));
	levelBar.setPosition(25, 320);
	
	userInput.setFont(font);
	userInput.setCharacterSize(30);
	userInput.setFillColor(Color::White);
	userInput.setPosition(50, 900);
	userInput.setString("");

	menuButton.setPosition(Vector2f(30, 30));

	userBox.setFont(font);
	userBox.setPosition(300.f, 520.f);  // near bottom of an 800�600 window
	userBox.setBoxSize(450.f, 40.f);   // fill most of width

	maxPoints = 5 + (5 * lulu.getLevel());

	progTimeTotal = 0;
	textUpdate = (rand() % 10 + 5);

	/*
	auto timeT = std::chrono::system_clock::to_time_t(demoTask.getDueDate());
	std::tm localTm{};
	localtime_s(&localTm, &timeT);
	

	std::ostringstream oss;
	oss << "Task: Hackathon Demo\n"
		<< "Due: " << std::put_time(&localTm, "%b %d, %Y %H:%M") << "\n"
		<< "Points if completed: " << points;

	userInput.setString(oss.str());
	*/


}

void finalizeGame() {
	/*
	for (auto obj : gameObjects) {
		delete obj; // frees memory that was pointed to
	}
	gameObjects.clear();
	*/
}