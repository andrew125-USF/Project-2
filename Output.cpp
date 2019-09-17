#include "Output.h"

using namespace std;


Output::Output(int menu)
{
	menu_type = menu;
}

Output::Output()
{
}

int Output::main_menu()
{
	choice = 0;
	cout << endl << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl;
	cout << setw(32) << "Main Menu" << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl;
	cout << setw(23) << "(1) - Student Menu" << endl;
	cout << setw(23) << "(2) - Advisor Menu" << endl;
	cout << setw(15) << "(3) - Exit" << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl << endl << endl;

	cout << setw(35) << "Enter your selection (1/2/3): ";
	getline(cin >> ws, the_choice);
	if (the_choice == "1" || the_choice == "2" || the_choice == "3")
		choice = stoi(the_choice);
	else
	{
		cout << endl << endl << setw(34) << "Invalid input!" << endl;
		choice = main_menu();
	}

	return choice;
}

int Output::advisor_menu()
{
	choice = 0;
	cout << endl << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl;
	cout << setw(33) << "Advisor Menu" << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl;
	cout << setw(27) << "(1) - Display Advisees" << endl;
	cout << setw(26) << "(2) - Search Advisees" << endl;
	cout << setw(22) << "(3) - Add Advisee" << endl;
	cout << setw(25) << "(4) - Delete Advisee" << endl;
	cout << setw(24) << "(5) - Move Advisees" << endl;
	cout << setw(31) << "(6) - GPA Average by Major" << endl;
	cout << setw(27) << "(7) - Display Advisors" << endl;
	cout << setw(34) << "(8) - Check Student's Advisor" << endl;
	cout << setw(23) << "(9) - Access Notes" << endl;
	cout << setw(30) << "(0) - Return to Main Menu" << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl << endl << endl;

	cout << setw(27) << "Enter your selection: ";
	getline(cin >> ws, the_choice);
	if (the_choice == "1" || the_choice == "2" || the_choice == "3" || the_choice == "4" || the_choice == "5" || the_choice == "6" || the_choice == "7" || the_choice == "8" || the_choice == "9" || the_choice == "0" || the_choice == "10")
		choice = stoi(the_choice);
	else
	{
		cout << endl << endl << setw(34) << "Invalid input!" << endl;
		choice = advisor_menu();
	}
	return choice;
}

int Output::student_menu()
{
	choice = 0;
	cout << endl << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl;
	cout << setw(33) << "Student Menu" << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl;
	cout << setw(35) << "(1) - View Advisor Information" << endl;
	cout << setw(18) << "(2) - View ID" << endl;
	cout << setw(28) << "(3) - View & Edit Major" << endl;
	cout << setw(26) << "(4) - View & Edit GPA" << endl;
	cout << setw(34) << "(5) - View & Edit Total Hours" << endl;
	cout << setw(30) << "(0) - Return to Main Menu" << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl << endl << endl;

	cout << setw(27) << "Enter your selection: ";
	getline(cin >> ws, the_choice);
	if (the_choice == "1" || the_choice == "2" || the_choice == "3" || the_choice == "4" || the_choice == "5" || the_choice == "0")
		choice = stoi(the_choice);
	else
	{
		cout << endl << endl << setw(34) << "Invalid input!" << endl;
		choice = student_menu();
	}

	return choice;
}

int Output::display_submenu(string the_id)
{
	choice = 0;

	if (the_id.substr(0, 2) == "ST")
		choice = student_menu();
	else if (the_id.substr(0, 2) == "AD")
		choice = advisor_menu();

	return choice;
}

Output::~Output()
{
}
