#include "Student.h"
#include "Advisor.h"
#include "User.h"
#include "FileIO.h"

using namespace std;

Student::Student(string id, string password, string major, int totalHours, double GPA) :User(id, password)
{
	this->major = major;
	this->totalHours = totalHours;
	this->GPA = GPA;
	this->advisor = NULL;
}

Advisor* Student::get_advisor()
{
	return advisor;
}

void Student::set_advisor(Advisor* new_advisor)
{
	advisor = new_advisor;
}

int Student::get_hours()
{
	return totalHours;
}

double Student::get_GPA()
{
	return GPA;
}
void Student::set_GPA(double newGPA)
{

	GPA = newGPA;
	FileIO::rewrite_students();
}

string Student::get_Major()
{
	return major;
}

void Student::set_Major(string newMajor)
{
	major = newMajor;
	FileIO::rewrite_students();
}

void Student::set_TotalHours(int newHours)
{
	totalHours = newHours;
	FileIO::rewrite_students();
}

void Student::set_notes(vector<string> the_notes)
{
	notes = the_notes;
}

void Student::add_new_note(string note)
{
	notes.push_back(note);
	FileIO::rewrite_notes();
}

vector<string> Student::get_notes()
{
	return notes;
}

void Student::print_my_info()
{
	cout << setw(5) << "";
	cout << "ID: " << get_id() << endl;
	cout << setw(5) << "";
	cout << "Major: " << get_Major() << endl;
	cout << setw(5) << "";
	cout << "Total Hours: " << get_hours() << endl;
	cout << setw(5) << "";
	cout << "GPA: " << get_GPA() << endl;
}

void Student::print_welcome()
{
	cout << setw(33) << "Welcome, Student " << get_id() << endl;
}