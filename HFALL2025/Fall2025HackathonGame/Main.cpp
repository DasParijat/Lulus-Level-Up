#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "LayoutManager.h"
#include "Button.h"
#include "Task.h"
#include "TextInput.h"
#include "Mascot.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

//--- Globals --//
//Layout
LayoutManager layout(1152.f, 720.f);

// Textures
TextureHolder holder;
Mascot lulu;

// Text
Font font;
Text userInput;
sf::String inputString;
TextInput userBox;
Text luluText;

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
	VideoMode vm(1152, 720);
	RenderWindow window(vm, "Fall 2025 HACKATHON");

	View view(FloatRect(0, 0, 1152, 720));
	window.setView(view);

	luluText.setFont(font);
	luluText.setCharacterSize(20);
	luluText.setFillColor(Color::White);
	luluText.setString("I'm excited to be your \ntask manager!");
	luluText.setPosition(5, 550);
	

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

		// Window layout resizer thingy
		if (event.type == sf::Event::Resized) {
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			window.setView(sf::View(visibleArea));
			layout.update(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
		}


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

	// After processing events
	if (userBox.hasSubmitted) {
		std::string taskTitle = userBox.getString();
		userBox.clear();
		userBox.hasSubmitted = false;

		// Create a new Task with today’s date and difficulty 1 (for now)
		time_t now = time(0);
		tm local{};
		localtime_s(&local, &now);  // thread-safe version

		int day = local.tm_mday;
		int month = local.tm_mon + 1;
		int year = local.tm_year + 1900;

		Task newTask(taskTitle, day, month, year, 1);
		taskList.push_back(newTask);

		std::cout << "Created Task: " << taskTitle << std::endl;
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

	// --- Panel background ---
	sf::FloatRect panelBounds = layout.getLeftPanelBounds();
	sf::RectangleShape leftPanel(sf::Vector2f(panelBounds.width, panelBounds.height));
	leftPanel.setFillColor(sf::Color(35, 40, 60));
	window.draw(leftPanel);

	// --- Buttons and text box ---
	window.draw(menuButton.getSprite());
	userBox.draw(window);

	// --- Lulu ---
	//lulu.setPosition({ panelBounds.width * 0.3f, panelBounds.height * 0.7f });
	lulu.draw(window);
	window.draw(luluText);

	// --- Task Board ---
	int columnCount = 3;
	sf::Vector2f taskSize = layout.getTaskSize(columnCount);

	for (size_t i = 0; i < taskList.size(); ++i) {
		sf::Vector2f pos = layout.getTaskPosition(static_cast<int>(i), columnCount);

		// Sticky note background
		sf::RectangleShape noteBox(taskSize);
		noteBox.setPosition(pos);

		// Color logic
		if (taskList[i].getCompleted()) {
			noteBox.setFillColor(sf::Color(180, 255, 180)); // green for done
		}
		else {
			noteBox.setFillColor(sf::Color(255, 255, 150)); // yellow for active
		}
		noteBox.setOutlineColor(sf::Color(200, 180, 80));
		noteBox.setOutlineThickness(2.f);

		// Drop shadow
		sf::RectangleShape shadow(noteBox);
		shadow.move(5.f, 5.f);
		shadow.setFillColor(sf::Color(0, 0, 0, 60));

		// Task text (auto-scaled to note height)
		sf::Text titleText;
		titleText.setFont(font);
		titleText.setCharacterSize(static_cast<unsigned int>(taskSize.y * 0.25f)); // scale text
		titleText.setFillColor(sf::Color::Black);
		titleText.setString(taskList[i].getTitle());
		titleText.setPosition(pos.x + 10.f, pos.y + 10.f);

		// Draw shadow, box, and text
		window.draw(shadow);
		window.draw(noteBox);
		window.draw(titleText);
	}

	window.display();
}


void initializeGame() {

	if (!font.loadFromFile("fonts/Chewy-Regular.ttf")) {
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