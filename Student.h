#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>
#include "User.h"

using namespace std;

class Advisor;

class Student : public User {
private:
	string major;
	int totalHours;
	double GPA;
	Advisor* advisor;
	vector<string> notes;
public:
	//Constructor
	Student(string id, string password, string major, int totalHours, double GPA);

	//Getters
	double get_GPA();
	string get_Major();
	int get_hours();

	//Setters
	void set_GPA(double newGPA);
	void set_Major(string newMajor);
	void set_TotalHours(int newHours);

	//Advisor
	Advisor* get_advisor();
	void set_advisor(Advisor* advisor);

	//Notes
	void set_notes(vector<string> the_notes);
	void add_new_note(string note);
	vector<string> get_notes();

	//Overrides
	void print_my_info() override;
	void print_welcome() override;
};

#endif //STUDENT_H