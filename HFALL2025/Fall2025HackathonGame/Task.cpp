#include "Task.h"
using namespace std;

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