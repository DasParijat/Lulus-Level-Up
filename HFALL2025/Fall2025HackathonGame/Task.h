#pragma once
#include <SFML/Graphics.hpp>
// Include C++20 date/time utilities (modern replacement for <ctime>)
#include <chrono>
// Include string class for text-based fields like title and note
#include <string>


class Task {

private:
    // Title or short description of the task
    std::string title;

    // Stores the due date/time as a chrono time_point (modern type-safe date representation)
    std::chrono::system_clock::time_point dueDate;

    // Difficulty rating (used to calculate reward points)
    int difficulty;

    // Optional text note with extra details
    std::string note;

public:
    // CONSTRUCTOR
    Task(std::string title, int day, int month, int year, int difficulty, std::string note = "");

    // complete()
    // Calculates how many points the player earns
    // if the task is completed before or after the due date.
    int complete();

    // getDueDate()
    // Returns the internal due date for display or logging.
    std::chrono::system_clock::time_point getDueDate() const { return dueDate; }

    // title getter
    std::string getTitle() const { return title; }

};