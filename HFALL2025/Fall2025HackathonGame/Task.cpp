#include "Task.h"

#include <chrono>     // time_point, system_clock, etc.
#include <iostream>   // cout and basic I/O
#include <ctime>      // time_t, tm, and mktime for conversions
#include <iomanip>    // put_time for readable date/time output

using namespace std;
using namespace std::chrono;


// CONSTRUCTOR
Task::Task(string title, int day, int month, int year, string note)
	: title(title), note(note)
{
	// Build a standard C "tm" struct to hold the date
	std::tm tmDue = {};

	// Populate it with the provided calendar values
	tmDue.tm_year = year - 1900;  // 'tm_year' counts years since 1900
	tmDue.tm_mon = month - 1;    // 'tm_mon' counts months 0�11
	tmDue.tm_mday = day;
	tmDue.tm_hour = 23;           // Default due time is 11:59 PM
	tmDue.tm_min = 59;

	// Convert tm -> time_t (seconds since epoch)
	time_t due_time_t = std::mktime(&tmDue);

	// Convert time_t -> chrono::time_point (modern format)
	dueDate = std::chrono::system_clock::from_time_t(due_time_t);

}

// complete()
// Compares the current system time with the stored due date.
// If completed on or before due date -> bonus points.
// Otherwise -> just difficulty points.
int Task::complete() {
	auto now = std::chrono::system_clock::now();
	return value;
}

// printDueDate()
// (Free function, not part of the class.)
// Prints the due date in a human-readable format using localtime_s.
void printDueDate(std::chrono::system_clock::time_point dueDate) {
	using namespace std;
	using namespace std::chrono;

	// Convert time_point -> time_t (raw timestamp)
	time_t timeT = system_clock::to_time_t(dueDate);

	// Safely convert to local time
	std::tm localTm{};
	localtime_s(&localTm, &timeT);

	// Print formatted date/time
	cout << std::put_time(&localTm, "%b %d, %Y %H:%M") << endl;
}


/*
Task::Task(string title, int day, int month, int year, int difficulty, string note) {
	this->title = title;
	dueDate.tm_mday = day;
	dueDate.tm_mon = month;
	dueDate.tm_year = year;
	time_t timeNow = time(0);
	tm* tmNow = localtime(&timeNow);
	dueDate.tm_hour = tmNow->tm_hour;
	dueDate.tm_min = tmNow->tm_min;
	dueDate.tm_isdst = tmNow->tm_isdst;
	this->difficulty = difficulty;
	this->note = note;
} // constructor

int Task::complete() {
	int pointVal;
	time_t dueTime = mktime(&dueDate);
	time_t currTime = time(0);
	if (currTime <= dueTime) {
		pointVal = 5 + difficulty;
	} // if by due date
	else {
		pointVal = difficulty;
	} // else
	return pointVal;
} // complete
*/