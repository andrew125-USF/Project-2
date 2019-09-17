/*This Program was created by Hannah Zbuchalski, Andrew Farrenkopf and Robin AbdelMessih.
The purpose of this program is to create a database for Advisors and Students to access*/
#include <cstdlib>
#include <iostream>
#include <string>
#include "FileIO.h"
#include "Advisor.h"
#include "Output.h"

using namespace std;

int main()
{
	vector<Advisor*> advisors;
	vector<Student*> students;
	map<string, vector<string>> notes;

	//open files (one and only time to open & read from files). set up opens the files
	FileIO new_file;
	new_file.set_up();

	//store the values from set_up into maps * vectors
	advisors = new_file.get_advisors();
	students = new_file.get_students();
	notes = new_file.get_note_list();

	//set vector object pointers
	Advisor::set_students(students);
	Advisor::set_advisors(advisors);

	Output the_menus;
	bool menu_flag = true;
	string id = "";

	//loop until user asks to quit
	while (1)
	{
		bool invalid_flag = false;
		int menu_choice = 0;
		string min, max;

		if (menu_flag)
		{
			id = "";
			Student* the_student = NULL;
			Advisor* the_advisor = NULL;

			// display the top level menu
			menu_choice = the_menus.main_menu();

			switch (menu_choice)
			{
			case 1:
				//student log-in
				id = new_file.log_in("ST");
				break;
			case 2:
				//advisor log-in
				id = new_file.log_in("AD");
				break;
			case 3:
				//exit
				cout << endl << "Bye!" << endl;
				return 0;
				break;
			default:
				break;
			}

			// invalid user credentials
			if (id == "")
			{
				cout << endl << endl;
				cout << setw(8) << "";
				cout << "Invalid credentials, please try again." << endl;
				continue;
			}
		}

		menu_flag = false;

		//Menu for students
		if (id.substr(0, 2) == "ST")
		{
			int menu_choice = 0, flag = 0;
			string input = "";
			double dnum = 0.0;
			int num = 0;
			Advisor* advisor;

			Student* student = Advisor::find_student(id);
			if (student == NULL)
				continue;

			menu_choice = the_menus.student_menu();

			switch (menu_choice)
			{
			case 0:
				//Displays menu
				menu_flag = true;
				break;
			case 1:
				//view advisor information
				advisor = student->get_advisor();
				if (advisor != NULL)
				{
					cout << endl;
					advisor->print_my_info();
				}
				else
				{
					cout << endl << setw(5) << "";
					cout << "You do not currently have an advisor!" << endl;
				}
				break;
			case 2:
				//view id
				cout << endl << setw(14) << "Your ID: " << student->get_id() << endl;
				break;
			case 3:
				//view & edit major
				cout << endl << setw(20) << "Current Major: " << student->get_Major() << endl;
				cout << setw(26) << "Update Major? (Y/N): ";
				getline(cin >> ws, input);

				//error checking
				flag = 1;
				while (flag != 0)
				{
					transform(input.begin(), input.end(), input.begin(), ::toupper);

					if (input == "Y")
					{
						string new_major;
						bool invalid_flag = false;
						cout << setw(22) << "Input new major: ";
						getline(cin >> ws, new_major);
						while (1)
						{
							for (auto m : new_major)
							{
								if (isdigit(m) || ispunct(m))
									invalid_flag = true;
							}
							if (invalid_flag == false)
							{
								student->set_Major(new_major);
								cout << endl << setw(5) << "";
								cout << "Major was successfully updated." << endl;
								flag = 0;
								break;
							}
							else if (invalid_flag == true)
							{
								invalid_flag = false;
								cout << setw(30) << "Invalid entry, try again." << endl << endl;
								cout << setw(22) << "Input new major: ";
								getline(cin >> ws, new_major);
							}
						}
						break;
					}
					if (input == "N")
					{
						flag = 0;
						break;
					}
					else
					{
						cout << setw(32) << "Invalid letter, try again: ";
						getline(cin >> ws, input);
					}
				}
				break;
			case 4:
				//view & edit gpa
				cout << fixed;
				cout << endl << endl << setw(18) << "Current GPA: " << setprecision(2) << student->get_GPA() << endl;
				cout << setw(24) << "Update GPA? (Y/N): ";
				getline(cin >> ws, input);

				//error checking
				flag = 1;
				while (flag != 0)
				{
					transform(input.begin(), input.end(), input.begin(), ::toupper);

					if (input == "Y")
					{
						string new_gpa;
						cout << setw(20) << "Input new GPA: ";
						getline(cin >> ws, new_gpa);
						while (1)
						{
							bool invalid_flag = false;
							for (auto g : new_gpa)
							{
								if (isalpha(g))
									invalid_flag = true;

								if (ispunct(g))
								{
									if (g == '.')
										continue;
									else
										invalid_flag = true;
								}
							}
							if (invalid_flag == false)
								dnum = stod(new_gpa);
							if (dnum <= 0)
								invalid_flag = true;


							if (invalid_flag == true)
							{
								cout << setw(30) << "Invalid entry, try again." << endl << endl;
								cout << setw(20) << "Input new GPA: ";
								getline(cin >> ws, new_gpa);
							}
							else if (invalid_flag == false)
							{
								student->set_GPA(dnum);
								cout << endl << setw(5) << "";
								cout << "GPA was successfully updated." << endl;
								flag = 0;
								break;
							}
						}
						break;
					}
					if (input == "N")
					{
						flag = 0;
						break;
					}
					else
					{
						cout << setw(32) << "Invalid letter, try again: ";
						getline(cin >> ws, input);
					}
				}
				break;
			case 5:
				//view & edit total hours
				cout << endl << endl << setw(26) << "Current Total Hours: " << student->get_hours() << endl;
				cout << setw(32) << "Update Total Hours? (Y/N): ";
				getline(cin >> ws, input);

				//error checking
				flag = 1;
				while (flag != 0)
				{

					transform(input.begin(), input.end(), input.begin(), ::toupper);

					if (input == "Y")
					{
						string new_hours;
						cout << setw(22) << "Input new hours: ";
						getline(cin >> ws, new_hours);

						while (1)
						{
							bool invalid_flag = false;
							for (auto h : new_hours)
							{
								if (isalpha(h) || ispunct(h))
									invalid_flag = true;
							}
							if (invalid_flag == false)
								num = stoi(new_hours);

							if (invalid_flag == true)
							{
								cout << setw(30) << "Invalid entry, try again." << endl << endl;
								cout << setw(22) << "Input new hours: ";
								getline(cin >> ws, new_hours);
							}
							else if (invalid_flag == false)
							{
								student->set_TotalHours(num);
								cout << endl << setw(5) << "";
								cout << "Total hours were successfully updated." << endl;
								flag = 0;
								break;
							}
						}
						break;
					}
					if (input == "N")
					{
						flag = 0;
						break;
					}
					else
					{
						cout << setw(32) << "Invalid letter, try again: ";
						getline(cin >> ws, input);
					}
				}
				break;
			default:
				cout << "Invalid Number, Try again" << endl;
				break;
			}
		}
		//The advisor menu
		else if (id.substr(0, 2) == "AD")
		{
			int menu_choice = 0, num = 0;
			double dnum = 0.0;
			string input = "", advisor_id = "", student_id = "", authorization_code = "";
			Advisor* advisor = NULL;

			advisor = Advisor::find_advisor(id);
			if (advisor == NULL)
				continue;

			menu_choice = the_menus.advisor_menu();
			switch (menu_choice)
			{
			case 0:
				menu_flag = true;
				break;
			case 1:
				//display advisees
				cout << endl << setw(14) << "Sort by: " << endl;
				cout << setw(11) << "(1) ID" << endl;
				cout << setw(14) << "(2) Major" << endl;
				cout << setw(20) << "(3) Total Hours" << endl;
				cout << setw(32) << "(0) Return to previous menu" << endl << endl;
				cout << setw(27) << "Enter your selection: ";
				getline(cin >> ws, input);
				while (1)
				{
					for (auto p : input)
					{
						if (!isdigit(p))
							invalid_flag = true;
					}
					if (invalid_flag == false)
					{
						num = stoi(input);
						switch (num)
						{
						case 0:
							break;
						case 1:
						case 2:
						case 3:
							try
							{
								advisor->displayStudents(num);
							}
							catch (InvalidString &e)
							{
								cout << setw(5 + e.message.size()) << e.message << endl;
							}
							break;
						default:
							cout << endl << setw(31) << "Invalid entry, try again: ";
							getline(cin >> ws, input);
							continue;
							break;
						}
						break;
					}
					else
					{
						cout << setw(31) << "Invalid entry, try again: ";
						getline(cin >> ws, input);
					}
					invalid_flag = false;
				}
				break;
			case 2:
				// search advisees
				cout << setw(13) << "Find by:" << endl;
				cout << setw(11) << "(1) ID" << endl;
				cout << setw(14) << "(2) Major" << endl;
				cout << setw(29) << "(3) Range of Total Hours" << endl;
				cout << setw(33) << "(4) Major and Range of Hours" << endl;
				cout << setw(32) << "(0) Return to Previous Menu" << endl;
				cout << endl << setw(27) << "Enter your selection: ";
				getline(cin >> ws, input);
				while (1)
				{
					for (auto p : input)
					{
						if (!isdigit(p))
							invalid_flag = true;
					}
					if (invalid_flag == false)
					{
						num = stoi(input);
						switch (num)
						{
						case 0:
							break;
						case 1:
							while (1)
							{
								bool retry = false;
								bool invalid = false;
								bool exit = false;
								cout << setw(5) << "";
								cout << "Enter Student's ID: ";
								getline(cin >> ws, input);
								transform(input.begin(), input.end(), input.begin(), ::toupper);
								try
								{
									advisor->findStudent(input);
								}
								catch (InvalidString &e)
								{
									invalid = true;
									cout << endl << setw(5 + e.message.size()) << e.message << endl;
									cout << setw(5) << "";
									cout << "Try again? (Y/N): ";
									getline(cin >> ws, input);
									while (1)
									{
										transform(input.begin(), input.end(), input.begin(), ::toupper);
										if (input == "Y")
										{
											break;
										}
										else if (input == "N")
										{
											exit = true;
											break;
										}
										else
										{
											cout << setw(31) << "Invalid entry, try again: ";
											getline(cin >> ws, input);
										}
									}
								}
								if (invalid == false || exit == true)
								{
									break;
								}
							}
							break;
						case 2:
							while (1)
							{
								bool retry = false;
								bool invalid = false;
								bool exit = false;
								cout << setw(5) << "";
								cout << "Enter Student's Major: ";
								getline(cin >> ws, input);
								transform(input.begin(), input.end(), input.begin(), ::toupper);
								try
								{
									advisor->findStudent_byMajor(input);
								}
								catch (InvalidString &e)
								{
									invalid = true;
									cout << endl << setw(5 + e.message.size()) << e.message << endl;
									cout << setw(5) << "";
									cout << "Try again? (Y/N): ";
									getline(cin >> ws, input);
									while (1)
									{
										transform(input.begin(), input.end(), input.begin(), ::toupper);
										if (input == "Y")
										{
											break;
										}
										else if (input == "N")
										{
											exit = true;
											break;
										}
										else
										{
											cout << setw(31) << "Invalid entry, try again: ";
											getline(cin >> ws, input);
										}
									}
								}
								if (invalid == false || exit == true)
								{
									break;
								}
							}
							break;
						case 3:
							while (1)
							{
								bool exit = false;
								bool invalid = false;
								cout << setw(21) << "Enter min time: ";
								getline(cin >> ws, min);
								cout << setw(21) << "Enter max time: ";
								getline(cin >> ws, max);
								try
								{
									advisor->displayRange(advisor, min, max);
								}
								catch (InvalidInt &e)
								{
									cout << endl << setw(5 + e.message.size()) << e.message << endl;
									invalid = true;
								}
								catch (InvalidString &e)
								{
									cout << endl << setw(5 + e.message.size()) << e.message << endl;
									invalid = true;
								}
								catch (InvalidRange &e)
								{
									cout << endl << setw(5 + e.message.size()) << e.message << endl;
									invalid = true;
								}
								if (invalid == true)
								{
									cout << setw(5) << "";
									cout << "Try again? (Y/N): ";
									getline(cin >> ws, input);
									while (1)
									{
										transform(input.begin(), input.end(), input.begin(), ::toupper);
										if (input == "Y")
										{
											break;
										}
										else if (input == "N")
										{
											exit = true;
											break;
										}
										else
										{
											cout << setw(31) << "Invalid entry, try again: ";
											getline(cin >> ws, input);
										}
									}
								}
								if (invalid == false || exit == true)
								{
									break;
								}
							}
							break;
						case 4:
							while (1)
							{
								bool invalid = false;
								bool exit = false;
								cout << endl << setw(5) << "";
								cout << "Enter min time: ";
								getline(cin >> ws, min);
								cout << setw(5) << "";
								cout << "Enter max time: ";
								getline(cin >> ws, max);
								cout << setw(5) << "";
								cout << "Enter Major: ";
								getline(cin >> ws, input);
								transform(input.begin(), input.end(), input.begin(), ::toupper);
								try
								{
									advisor->findStudent(advisor, input, min, max);
								}
								catch (InvalidInt &e)
								{
									cout << endl << setw(5 + e.message.size()) << e.message << endl;
									invalid = true;
								}
								catch (InvalidString &e)
								{
									cout << endl << setw(5 + e.message.size()) << e.message << endl;
									invalid = true;
								}
								catch (InvalidRange &e)
								{
									cout << endl << setw(5 + e.message.size()) << e.message << endl;
									invalid = true;
								}
								if (invalid == true)
								{
									cout << setw(5) << "";
									cout << "Try again? (Y/N): ";
									getline(cin >> ws, input);
									while (1)
									{
										transform(input.begin(), input.end(), input.begin(), ::toupper);
										if (input == "Y")
										{
											break;
										}
										else if (input == "N")
										{
											exit = true;
											break;
										}
										else
										{
											cout << setw(31) << "Invalid entry, try again: ";
											getline(cin >> ws, input);
										}
									}
								}
								if (invalid == false || exit == true)
								{
									break;
								}
							}
							break;
						default:
							cout << setw(5) << "";
							cout << "Invalid Number Try Again." << endl;
							break;
						}
						break;
					}
					else
					{
						cout << endl << setw(31) << "Invalid entry, try again: ";
						getline(cin >> ws, input);
					}
					invalid_flag = false;
				}
				break;
			case 3:
				// Add advisee
				while (1)
				{
					bool success = false;
					bool exit = false;
					cout << setw(5) << "";
					cout << "Enter student id: ";
					getline(cin >> ws, input);
					try
					{
						success = advisor->addStudent(input);
					}
					catch (InvalidString &e)
					{
						cout << endl << setw(5 + e.message.size()) << e.message << endl;
					}
					if (success == true)
						break;
					else if (success == false)
					{
						cout << setw(5) << "";
						cout << "Try again? (Y/N): ";
						getline(cin >> ws, input);
						while (1)
						{
							transform(input.begin(), input.end(), input.begin(), ::toupper);
							if (input == "Y")
							{
								break;
							}
							else if (input == "N")
							{
								exit = true;
								break;
							}
							else
							{
								cout << setw(31) << "Invalid entry, try again: ";
								getline(cin >> ws, input);
							}
						}
					}
					if (exit == true)
					{
						break;
					}
				}
				break;
			case 4:
				// Delete advisee
				while (1)
				{
					bool success = false;
					bool exit = false;
					cout << setw(5) << "";
					cout << "Enter student id: ";
					cin >> input;
					try
					{
						success = advisor->deleteStudent(input);
					}
					catch (InvalidString &e)
					{
						cout << endl << setw(5 + e.message.size()) << e.message << endl;
					}
					if (success == true)
						break;
					else if (success == false)
					{
						cout << setw(5) << "";
						cout << "Try again? (Y/N): ";
						getline(cin >> ws, input);
						while (1)
						{
							transform(input.begin(), input.end(), input.begin(), ::toupper);
							if (input == "Y")
							{
								break;
							}
							else if (input == "N")
							{
								exit = true;
								break;
							}
							else
							{
								cout << setw(31) << "Invalid entry, try again: ";
								getline(cin >> ws, input);
							}
						}
					}
					if (exit == true)
					{
						break;
					}
				}
				break;
			case 5:
				// Move advisees by major
				while (1)
				{
					bool exit = false;
					bool found = true;
					cout << endl << setw(5) << "";
					cout << "Enter Major: ";
					getline(cin >> ws, input);
					cout << setw(5) << "";
					cout << "Enter Advisor ID: ";
					getline(cin >> ws, advisor_id);
					cout << setw(5) << "";
					cout << "Enter Authorization Code: ";
					getline(cin >> ws, authorization_code);
					try
					{
						advisor->moveStudents(input, advisor_id, authorization_code);
					}
					catch (InvalidString &e)
					{
						found = false;
						cout << endl << setw(5 + e.message.size()) << e.message << endl;
						cout << setw(5) << "";
						cout << "Try again? (Y/N): ";
						getline(cin >> ws, input);
						while (1)
						{
							transform(input.begin(), input.end(), input.begin(), ::toupper);
							if (input == "Y")
							{
								break;
							}
							else if (input == "N")
							{
								exit = true;
								break;
							}
							else
							{
								cout << setw(31) << "Invalid entry, try again: ";
								getline(cin >> ws, input);
							}
						}
					}
					if (exit == true || found == true)
					{
						break;
					}
				}
				break;
			case 6:
				// GPA average by major
				while (1)
				{
					bool exit = false;
					bool found = true;
					cout << endl << setw(5) << "";
					cout << "Input major: ";
					getline(cin >> ws, input);
					try
					{
						advisor->displayMajor(input);
					}
					catch (InvalidString &e)
					{
						found = false;
						cout << endl << setw(5 + e.message.size()) << e.message << endl;
						cout << setw(5) << "";
						cout << "Try again? (Y/N): ";
						getline(cin >> ws, input);
						while (1)
						{
							transform(input.begin(), input.end(), input.begin(), ::toupper);
							if (input == "Y")
							{
								break;
							}
							else if (input == "N")
							{
								exit = true;
								break;
							}
							else
							{
								cout << setw(31) << "Invalid entry, try again: ";
								getline(cin >> ws, input);
							}
						}
					}
					if (exit == true || found == true)
					{
						break;
					}
				}
				break;
			case 7:
				// Display all advisors
				advisor->displayAdvisors();
				break;
			case 8:
				//Search Student's Advisors;
				while (1)
				{
					bool exit = false;
					bool found = true;
					cout << endl << setw(5) << "";
					cout << "Enter Student's ID: ";
					getline(cin >> ws, input);
					try
					{
						advisor->findAdvisor(input);
					}
					catch (InvalidString &e)
					{
						found = false;
						cout << endl << setw(5 + e.message.size()) << e.message << endl;
						cout << setw(5) << "";
						cout << "Try again? (Y/N): ";
						getline(cin >> ws, input);
						while (1)
						{
							transform(input.begin(), input.end(), input.begin(), ::toupper);
							if (input == "Y")
							{
								break;
							}
							else if (input == "N")
							{
								exit = true;
								break;
							}
							else
							{
								cout << setw(31) << "Invalid entry, try again: ";
								getline(cin >> ws, input);
							}
						}
					}
					if (exit == true || found == true)
					{
						break;
					}
				}
				break;
			case 9:
				//Notes
				cout << endl << setw(5) << "";
				cout << "(1) View notes" << endl;
				cout << setw(5) << "";
				cout << "(2) Add notes" << endl << endl;
				cout << setw(27) << "Enter your selection: ";
				getline(cin >> ws, input);
				while (1)
				{
					bool valid = true;
					for (auto i : input)
					{
						if (!isdigit(i))
							valid = false;
					}
					if (valid == true)
					{
						num = stoi(input);
						if (num == 1)
						{
							while (1)
							{
								bool student_found = true;
								bool exit = false;
								cout << setw(5) << "";
								cout << "Enter Student's ID: ";
								getline(cin >> ws, student_id);
								try
								{
									advisor->displayNotes(student_id);
								}
								catch (InvalidString &e)
								{
									student_found = false;
									cout << endl << setw(5 + e.message.size()) << e.message << endl;
									cout << setw(5) << "";
									cout << "Try again? (Y/N): ";
									getline(cin >> ws, input);
									while (1)
									{
										transform(input.begin(), input.end(), input.begin(), ::toupper);
										if (input == "Y")
										{
											break;
										}
										else if (input == "N")
										{
											exit = true;
											break;
										}
										else
										{
											cout << setw(31) << "Invalid entry, try again: ";
											getline(cin >> ws, input);
										}
									}
								}
								if (exit == true || student_found == true)
								{
									break;
								}
							}
							break;
						}
						else if (num == 2)
						{
							bool retry = true;
							while (retry)
							{
								cout << setw(5) << "";
								cout << "Enter Student's ID: ";
								getline(cin >> ws, student_id);
								try
								{
									retry = advisor->add_new_note(student_id);
								}
								catch (InvalidString &e)
								{
									cout << endl << setw(5 + e.message.size()) << e.message << endl;
								}
							}
							break;
						}
					}
					else
					{
						cout << setw(31) << "Invalid entry, try again: ";
						getline(cin >> ws, input);
					}
				}
				break;
			case 10:
				cout << endl << endl << endl << "final practice: " << endl << endl;
				advisor->final_practice();
				break;
			default:
				cout << "Invalid Number, Try again" << endl;
				break;
			}
		}
		else
		{
			// should never get here since the user logged in successfully above 
		}
	}
	return 0;
}