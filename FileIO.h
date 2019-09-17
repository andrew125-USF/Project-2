#ifndef FILEIO_h
#define FILEIO_h

#include "Advisor.h"
#include "Student.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>


using namespace std;

class FileIO {
	vector<Advisor*> advisors;
	vector<Student*> students;
	vector<string> notes;
	map<string, vector<string>> the_notes;
	map<string, vector<string>> advisees;
public:
	//Constructors
	FileIO();
	string log_in(string user_type);
	//Set up the menu
	void set_up();

	//Open the files
	void open_students();
	void open_advisors();
	void open_notes();
	void open_advisees();
	void add_advisees_to_advisor();

	//Rewrite text files
	static void rewrite_notes();
	static void rewrite_advisees();
	static void rewrite_students();

	//Getters
	map<string, vector<string>> get_note_list();
	vector<Student*> get_students();
	vector<Advisor*> get_advisors();
	map<string, vector<string>> get_advisees_list();
};
#endif