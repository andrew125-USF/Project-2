#ifndef OUTPUT_H
#define OUTPUT_H
#include <iostream>
#include <string>
#include "Student.h"
#include "Advisor.h"

using namespace std;

class Output
{
private:
	int menu_type;
	int choice;
	string the_choice;
public:
	Output(int menu);
	Output();
	int main_menu();
	int advisor_menu();
	int student_menu();
	int display_submenu(string the_id);

	~Output();
};

#endif

