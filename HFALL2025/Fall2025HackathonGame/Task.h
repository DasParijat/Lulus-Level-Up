#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>

class Task {

private:
	std::string title;
	struct tm dueDate;
	int difficulty;
	std::string note;
	bool isCompleted = false;

public:
	Task(std::string title, int day, int month, int year, int difficulty, std::string note = "");
	int complete();

};