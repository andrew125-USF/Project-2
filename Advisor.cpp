#include "Advisor.h"
#include "FileIO.h"

using namespace std;

vector<Advisor*> Advisor::advisors;
vector<Student*> Advisor::students;

Advisor::Advisor(string id, string password, string room_num, string phone) :User(id, password)
{
	this->room_num = room_num;
	this->phone = phone;
}

template <class T>
bool Advisor::IsFound(vector<T> myvec, string user_id)
{
	typename vector<T>::iterator it;
	for (it = myvec.begin(); it < myvec.end(); it++)
	{
		string upper_id = user_id;
		transform(upper_id.begin(), upper_id.end(), upper_id.begin(), ::toupper);
		if ((*it)->get_id() == upper_id)
			return true;
	}

	return false;
}

Student* Advisor::find_student(string id, string pwd)
{
	string upper_id = id;
	transform(upper_id.begin(), upper_id.end(), upper_id.begin(), ::toupper);
	vector<Student*> students = Advisor::students;
	auto it = find_if(students.begin(), students.end(), [=](Student* student)
	{
		string current_id = student->get_id();
		string current_pwd = student->get_pwd();
		return (current_id == upper_id && current_pwd == pwd);
	});
	if (it != students.end())
		return *it;
	else
		return nullptr;
}

Advisor* Advisor::find_advisor(string id, string pwd)
{
	string upper_id = id;
	transform(upper_id.begin(), upper_id.end(), upper_id.begin(), ::toupper);
	vector<Advisor*> advisors = Advisor::advisors;
	auto it = find_if(advisors.begin(), advisors.end(), [=](Advisor* advisor)
	{
		string current_id = advisor->get_id();
		string current_pwd = advisor->get_pwd();
		return (current_id == upper_id && current_pwd == pwd);
	});
	if (it != advisors.end())
		return *it;
	else
		return nullptr;
}

Advisor* Advisor::find_advisor(string advisor_id)
{
	string upper_id = advisor_id;
	transform(upper_id.begin(), upper_id.end(), upper_id.begin(), ::toupper);
	for (auto p : advisors)
	{
		if (p->get_id() == upper_id)
			return p;
	}
	return nullptr;
}

Student* Advisor::find_student(string student_id)
{
	string upper_id = student_id;
	transform(upper_id.begin(), upper_id.end(), upper_id.begin(), ::toupper);
	for (auto p : students)
	{
		if (p->get_id() == upper_id)
			return p;
	}
	return nullptr;
}

void Advisor::set_students(vector<Student*> student_list)
{
	students = student_list;
}

void Advisor::set_advisors(vector<Advisor*> advisor_list)
{
	advisors = advisor_list;
}

vector<Advisor*> Advisor::get_advisors()
{
	return advisors;
}

vector<Student*> Advisor::get_students()
{
	return students;
}

void Advisor::displayStudents_byMajor()
{
	map<string, vector<Student*>> majors;
	string user, time, the_gpa;

	for (auto student : advisees)
	{
		majors[student->get_Major()].push_back(student);
	}

	if (majors.empty())
	{
		cout << endl << setw(23) << "No students found!" << endl;
	}
	else
	{
		cout << endl << setw(5) << "";
		cout << "Students: " << endl;
		cout << setw(5) << "";
		cout << "( Major  :   ID    :  Hours  :  GPA )" << endl << endl;
		for (auto q : majors)
		{
			for (auto s : q.second)
			{
				cout << fixed << setw(5) << "";
				cout << setw(9) << left << q.first;
				cout << ":  " << s->get_id() << "  :   ";
				cout << setw(6) << left << s->get_hours();
				cout << ":  " << setprecision(2) << s->get_GPA();
				cout << right << endl;
			}
		}
	}
}

void Advisor::displayRange(Advisor* the_advisor, string minS, string maxS)
{
	int flag = 0;

	for (int i = 0; i < minS.length(); i++)
	{
		if (!(minS[i] >= '0' && minS[i] <= '9' || minS[i] == '.' || minS[i] == '-'))
		{
			InvalidString error;
			error.message = "Error: Can not contain string";
			error.text = minS;
			throw error;
		}
		if (minS[i] == '.')
		{
			InvalidString error;
			error.message = "Error: Must be a whole number";
			error.text = minS;
			throw error;
		}
	}

	for (int j = 0; j < maxS.length(); j++)
	{
		if (!(maxS[j] >= '0' && maxS[j] <= '9' || maxS[j] == '.' || maxS[j] == '-'))
		{
			InvalidString error;
			error.message = "Error: Can not contain string";
			error.text = maxS;
			throw error;
		}
		if (maxS[j] == '.')
		{
			InvalidString error;
			error.message = "Error: Must be a whole number";
			error.text = maxS;
			throw error;
		}
	}

	int min = stoi(minS);
	int max = stoi(maxS);

	if (min < 0)
	{
		InvalidInt error;
		error.message = "Error: Range can not be less than 0";
		error.num = min;
		throw error;
	}

	if (max < 0)
	{
		InvalidInt error;
		error.message = "Error: Range can not be less than 0";
		error.num = max;
		throw error;
	}

	if (min > max)
	{
		InvalidRange error;
		error.message = "Error: Min can not be larger Max";
		error.invalidmin = min;
		error.invalidmax = max;
		throw error;
	}

	for (auto b : advisees)
	{
		if (b->get_hours() <= max && b->get_hours() >= min)
			flag = 1;
	}
	if (flag == 0)
	{
		cout << endl << setw(23) << "No students found!" << endl;
	}
	else if (flag == 1)
	{
		cout << endl << setw(14) << "Students:" << endl;
		for (auto b : advisees)
		{
			if (b->get_hours() <= max && b->get_hours() >= min)
			{
				b->print_my_info();
				cout << endl;
			}
		}
	}
}

void Advisor::displayStudents_byid()
{
	map<string, vector<Student*>> ids;

	for (auto student : advisees)
	{
		ids[student->get_id()].push_back(student);
	}

	if (ids.empty())
	{
		cout << endl << setw(23) << "No students found!" << endl;
	}
	else
	{
		cout << endl << setw(14) << "Students:" << endl;
		cout << setw(5) << "";
		cout << "(   ID   :  Major  :  Hours  :  GPA )" << endl << endl;
		for (auto q : ids)
		{
			for (auto k : q.second)
			{
				cout << fixed;
				cout << setw(5) << "";
				cout << setw(9) << left << k->get_id();
				cout << ":  " << setw(7) << k->get_Major() << ":   ";
				cout << setw(6) << k->get_hours();
				cout << ":  " << setprecision(2) << k->get_GPA();
				cout << right << endl;
			}
		}
	}
}

void Advisor::displayStudents_byhours()
{
	map<int, vector<Student*>> times;
	string user, maj, the_gpa;

	for (auto student : advisees)
	{
		times[student->get_hours()].push_back(student);
	}

	if (times.empty())
	{
		cout << endl << setw(23) << "No students found!" << endl;
	}
	else
	{
		cout << endl << setw(14) << "Students:" << endl;
		cout << setw(5) << "";
		cout << "( Hours  :   ID    :  Major  :  GPA )" << endl << endl;
		for (auto q : times)
		{
			for (auto s : q.second)
			{
				cout << fixed;
				cout << setw(5) << "";
				cout << setw(9) << left << s->get_hours();
				cout << ":  " << s->get_id() << "  :   ";
				cout << setw(6) << left << s->get_Major();
				cout << ":  " << setprecision(2) << s->get_GPA();
				cout << right << endl;
			}
		}
	}
}

void Advisor::displayStudents(int sort_type)
{
	switch (sort_type)
	{
	case 1:
		displayStudents_byid();
		break;

	case 2:
		displayStudents_byMajor();
		break;

	case 3:
		displayStudents_byhours();
		break;

	default:
		break;
	}
}

void Advisor::findStudent(Advisor* the_advisor, string major, string minhour, string maxhour)
{
	int flag = 0;

	for (auto m : major)
	{
		if (!isalpha(m))
		{
			InvalidString error;
			error.message = "Error: Invalid Major.";
			throw error;
			return;
		}
	}

	for (int i = 0; i < minhour.length(); i++)
	{
		if (!(minhour[i] >= '0' && minhour[i] <= '9' || minhour[i] == '.' || minhour[i] == '-'))
		{
			InvalidString error;
			error.message = "Error: Can not contain string.";
			error.text = minhour;
			throw error;
			return;
		}
		if (minhour[i] == '.')
		{
			InvalidString error;
			error.message = "Error: Must be a whole number.";
			error.text = minhour;
			throw error;
			return;
		}
	}

	for (int j = 0; j < maxhour.length(); j++)
	{
		if (!(maxhour[j] >= '0' && maxhour[j] <= '9' || maxhour[j] == '.' || maxhour[j] == '-'))
		{
			InvalidString error;
			error.message = "Error: Can not contain string.";
			error.text = maxhour;
			throw error;
			return;
		}
		if (maxhour[j] == '.')
		{
			InvalidString error;
			error.message = "Error: Must be a whole number.";
			error.text = maxhour;
			throw error;
			return;
		}
	}


	int min = stoi(minhour);
	int max = stoi(maxhour);

	if (min < 0)
	{
		InvalidInt error;
		error.message = "Error: Range can not be less than 0.";
		error.num = min;
		throw error;
		return;
	}

	if (max < 0)
	{
		InvalidInt error;
		error.message = "Error: Range can not be less than 0.";
		error.num = max;
		throw error;
		return;
	}

	if (min > max)
	{
		InvalidRange error;
		error.message = "Error: Min can not be larger Max.";
		error.invalidmin = min;
		error.invalidmax = max;
		throw error;
		return;
	}

	for (auto b : advisees)
	{
		if (b->get_Major() == major)
		{
			if (b->get_hours() <= max && b->get_hours() >= min)
				flag = 1;
		}
	}

	if (flag == 0)
	{
		cout << endl << setw(23) << "No students found!" << endl;
	}
	else if (flag == 1)
	{
		cout << endl << setw(14) << "Students:" << endl;
		for (auto b : advisees)
		{
			if (b->get_Major() == major)
			{
				if (b->get_hours() <= max && b->get_hours() >= min)
				{
					b->print_my_info();
					cout << endl;
				}
			}
		}
	}

}

void Advisor::findStudent_byMajor(string major)
{
	bool found = false;
	for (auto m : major)
	{
		if (!isalpha(m))
		{
			InvalidString error;
			error.message = "Invalid Major!";
			throw error;
		}
	}

	for (auto student : advisees)
	{
		if (student->get_Major() == major)
		{
			found = true;
			cout << endl;
			student->print_my_info();
		}
	}

	if (found == false)
	{
		InvalidString error;
		error.message = "No students found!";
		throw error;
	}
}

void Advisor::findStudent(string student_id)
{
	if (student_id.substr(0, 2) != "ST")
	{
		InvalidString error;
		error.message = "Student ID must begin with 'ST'.";
		throw error;
		return;
	}
	for (auto g : student_id.substr(2, 3))
	{
		if (!isdigit(g))
		{
			InvalidString error;
			error.message = "Invalid student ID.";
			throw error;
			return;
		}
	}

	if (!IsFound(advisees, student_id))
	{
		InvalidString error;
		error.message = "No students found!";
		throw error;
		return;
	}

	for (auto student : advisees)
	{
		if (student->get_id() == student_id)
		{
			cout << endl;
			student->print_my_info();
			return;
		}
	}
}

void Advisor::findStudent(double GPA)
{
	bool found = false;
	for (auto student : advisees)
	{
		if (student->get_GPA() == GPA)
		{
			cout << fixed;
			cout << endl << setw(5) << "";
			cout << "ID: " << student->get_id() << endl;
			cout << setw(5) << "";
			cout << "Major: " << student->get_Major() << endl;
			cout << setw(5) << "";
			cout << "Total Hours: " << student->get_hours() << endl;
			cout << setw(5) << "";
			cout << "GPA: " << setprecision(2) << student->get_GPA() << endl;
			found = true;
		}
	}
	if (found == false)
		cout << endl << setw(23) << "No students found!" << endl;
	// if we got this far, the student was NOT found!
}

void Advisor::displayNotes(string student_id)
{
	bool student_found = false;
	transform(student_id.begin(), student_id.end(), student_id.begin(), ::toupper);

	if (student_id.substr(0, 2) != "ST")
	{
		InvalidString error;
		error.message = "Student ID must begin with 'ST'.";
		throw error;
		return;
	}
	for (auto g : student_id.substr(2, 3))
	{
		if (!isdigit(g))
		{
			InvalidString error;
			error.message = "Invalid student ID.";
			throw error;
			return;
		}
	}
	for (auto p : advisees)
	{
		if (p->get_id() == student_id)
			student_found = true;
	}
	if (student_found == false)
	{
		InvalidString error;
		error.message = "Student not found!";
		throw error;
		return;
	}
	bool is_empty = true;
	vector<string> the_notes;
	for (auto p : advisees)
	{
		if (p->get_id() == student_id)
		{
			the_notes = p->get_notes();
			if (!the_notes.empty())
			{
				cout << endl << setw(5) << "";
				cout << "Notes: " << endl;
			}
			for (auto n : the_notes)
			{
				is_empty = false;
				cout << setw(5) << "";
				cout << n << endl;
			}
		}
	}

	if (is_empty)
	{
		cout << endl << setw(5) << "";
		cout << student_id << " has no notes." << endl;
	}

}

bool Advisor::add_new_note(string student_id)
{
	int day, month, year;
	string full_note = "", note;
	vector<string> student_notes;
	bool student_found = false;

	transform(student_id.begin(), student_id.end(), student_id.begin(), ::toupper);

	if (student_id.substr(0, 2) != "ST")
	{
		InvalidString error;
		error.message = "Student ID must begin with 'ST'.";
		throw error;
		return false;
	}
	for (auto g : student_id.substr(2, 3))
	{
		if (!isdigit(g))
		{
			InvalidString error;
			error.message = "Invalid student ID.";
			throw error;
			return false;
		}
	}

	for (auto p : advisees)
	{
		if (p->get_id() == student_id)
			student_found = true;
	}

	if (student_found)
	{
		Student* student = Advisor::find_student(student_id);
		cout << setw(5) << "";
		cout << "Enter note: ";
		getline(cin >> ws, note);

		time_t raw_time = time(0);
		tm now;
		localtime_s(&now, &raw_time);

		year = now.tm_year + 1900;
		month = now.tm_mon + 1;
		day = now.tm_mday;

		full_note = "(" + get_id() + " " + to_string(month) + "/" + to_string(day) + "/" + to_string(year) + ") " + student_id + " " + note;

		student->add_new_note(full_note);

		return false;
	}
	else
	{
		string input;
		cout << endl << setw(5) << "";
		cout << "Student not found!" << endl;
		while (1)
		{
			cout << setw(5) << "";
			cout << "Try again? (Y/N): ";
			getline(cin >> ws, input);
			if (input == "Y" || input == "y")
			{
				cout << endl;
				return true;
			}
			else if (input == "N" || input == "n")
			{
				cout << endl;
				return false;
			}
			else
			{
				cout << endl << setw(5) << "";
				cout << "Invalid input!" << endl;
			}
		}
	}
	return false;

}

vector<Student*> Advisor::get_advisees()
{
	return advisees;
}

bool Advisor::addStudent(string student_id)
{
	transform(student_id.begin(), student_id.end(), student_id.begin(), ::toupper);

	if (student_id.substr(0, 2) != "ST")
	{
		InvalidString error;
		error.message = "Student ID must begin with 'ST'.";
		throw error;
		return false;
	}
	for (auto g : student_id.substr(2, 3))
	{
		if (!isdigit(g))
		{
			InvalidString error;
			error.message = "Invalid student ID.";
			throw error;
			return false;
		}
	}
	Student* student = Advisor::find_student(student_id);

	if (student == NULL)
	{
		cout << setw(27) << "No such student found!" << endl;
		return false;
	}
	else
	{
		string input;
		cout << endl;
		student->print_my_info();
		cout << endl << setw(5) << "";
		cout << "Is this correct? (Y/N): ";
		getline(cin >> ws, input);
		while (1)
		{
			if (input == "Y" || input == "y")
			{
				break;
			}
			else if (input == "N" || input == "n")
			{
				return false;
				break;
			}
			else
			{
				cout << endl << setw(31) << "Invalid entry, try again: ";
				getline(cin >> ws, input);
			}
		}
	}

	// student cannot be added if he / she already has an advisor
	Advisor* advisor = student->get_advisor();

	if (advisor == NULL)
	{
		addStudent(student);
		cout << endl << setw(5) << "";
		cout << student->get_id() << " was added." << endl;
	}
	else
	{
		if (advisor->get_id() == get_id())
		{
			string input;
			string note = "***DOUBLE ADVISING REJECTED";
			int year, month, day;
			time_t raw_time = time(0);
			tm now;
			localtime_s(&now, &raw_time);

			year = now.tm_year + 1900;
			month = now.tm_mon + 1;
			day = now.tm_mday;

			string full_note = "(" + this->get_id() + " " + to_string(month) + "/" + to_string(day) + "/" + to_string(year) + ")" + " " + student->get_id() + " " + note;

			student->add_new_note(full_note);

			cout << endl << setw(5) << "";
			cout << student->get_id() << " is already your advisee!" << endl;
			cout << setw(5) << "";
			cout << "Try again? (Y/N): ";
			getline(cin >> ws, input);
			while (1)
			{
				if (input == "Y" || input == "y")
				{
					return false;
					break;
				}
				else if (input == "N" || input == "n")
				{
					return true;
					break;
				}
				else
				{
					cout << endl << setw(31) << "Invalid entry, try again: ";
					getline(cin >> ws, input);
				}
			}
		}
		else
		{
			string input;
			cout << setw(5) << "";
			cout << student->get_id() << " already has an advisor!" << endl;
			cout << setw(5) << "";
			cout << "Try again? (Y/N): ";
			getline(cin >> ws, input);
			while (1)
			{
				if (input == "Y" || input == "y")
				{
					return false;
					break;
				}
				else if (input == "N" || input == "n")
				{
					return true;
					break;
				}
				else
				{
					cout << endl << setw(31) << "Invalid entry, try again: ";
					getline(cin >> ws, input);
				}
			}
		}
	}

	FileIO::rewrite_advisees();
	return true;
}

void Advisor::addStudent(Student* student)
{
	// set the student's advisor to me (this advisor)
	student->set_advisor(this);

	// add the student
	advisees.push_back(student);
}

bool Advisor::deleteStudent(string student_id)
{
	transform(student_id.begin(), student_id.end(), student_id.begin(), ::toupper);

	if (student_id.substr(0, 2) != "ST")
	{
		InvalidString error;
		error.message = "Student ID must begin with 'ST'.";
		throw error;
		return false;
	}
	for (auto g : student_id.substr(2, 3))
	{
		if (!isdigit(g))
		{
			InvalidString error;
			error.message = "Invalid student ID.";
			throw error;
			return false;
		}
	}
	Student* student = Advisor::find_student(student_id);

	bool is_advisee = false;

	for (auto p : advisees)
	{
		if (p->get_id() == student_id)
		{
			is_advisee = true;
		}
	}

	if (student == NULL || is_advisee == false)
	{
		//display error message if student doesn't exist and return false since the student was not added
		cout << endl << setw(5) << "";
		cout << "No such student found!" << endl;
		return false;
	}

	string input;
	cout << endl;
	student->print_my_info();
	cout << endl << setw(5) << "";
	cout << "Is this correct? (Y/N): ";
	getline(cin >> ws, input);
	while (1)
	{
		if (input == "Y" || input == "y")
		{
			break;
		}
		else if (input == "N" || input == "n")
		{
			cout << endl << setw(5) << "";
			cout << "Try again? (Y/N): ";
			getline(cin >> ws, input);
			while (1)
			{
				if (input == "Y" || input == "y")
				{
					return false;
					break;
				}
				else if (input == "N" || input == "n")
				{
					return true;
					break;
				}
				else
				{
					cout << endl << setw(31) << "Invalid entry, try again: ";
					getline(cin >> ws, input);
				}
			}
			break;
		}
		else
		{
			cout << endl << setw(31) << "Invalid entry, try again: ";
			getline(cin >> ws, input);
		}
	}
	student->set_advisor(nullptr);

	// delete the student from the advisee list
	vector<Student*>::iterator newEnd = remove(advisees.begin(), advisees.end(), student);
	advisees.erase(newEnd, advisees.end());

	cout << endl << setw(5) << "";
	cout << student->get_id() << " was deleted." << endl;
	FileIO::rewrite_advisees();
	return true;
}

void Advisor::moveStudents(string major, string advisor_id, string authorization_code)
{
	transform(advisor_id.begin(), advisor_id.end(), advisor_id.begin(), ::toupper);
	Student* current_student;
	int year, month, day;
	string note;

	if (authorization_code != "ENB#342")
	{
		InvalidString error;
		error.message = "Incorrect authorization code!";
		throw error;
		return;
	}
	if (advisor_id.substr(0, 2) != "AD")
	{
		InvalidString error;
		error.message = "Advisor ID must begin with 'AD'.";
		throw error;
		return;
	}
	for (auto g : advisor_id.substr(2, advisor_id.size() - 2))
	{
		if (!isdigit(g))
		{
			InvalidString error;
			error.message = "Error: Invalid advisor ID.";
			throw error;
			return;
		}
	}
	for (auto m : major)
	{
		if (!isalpha(m))
		{
			InvalidString error;
			error.message = "Error: Invalid major.";
			throw error;
			return;
		}
	}

	if (!IsFound(advisors, advisor_id))
	{
		InvalidString error;
		error.message = "Advisor not found.";
		throw error;
		return;
	}

	Advisor* new_advisor = Advisor::find_advisor(advisor_id);


	if (get_id() == advisor_id)
	{
		InvalidString error;
		error.message = "Error: Advisor did not change.";
		throw error;
		return;
	}

	for (vector<Student*>::iterator it = advisees.begin(); it != advisees.end();)
	{
		transform(major.begin(), major.end(), major.begin(), ::toupper);
		current_student = *it;
		string current_major = current_student->get_Major();
		transform(current_major.begin(), current_major.end(), current_major.begin(), ::toupper);
		if (current_major == major)
		{
			current_student->set_advisor(nullptr);
			// remove the student from this advisor
			it = advisees.erase(it);

			// add the student to the new advisor
			new_advisor->addStudent(current_student);

			time_t raw_time = time(0);
			tm now;
			localtime_s(&now, &raw_time);

			year = now.tm_year + 1900;
			month = now.tm_mon + 1;
			day = now.tm_mday;

			note = "(" + advisor_id + " " + to_string(month) + "/" + to_string(day) + "/" + to_string(year) + ") " +
				current_student->get_id() + " *** ADVISOR CHANGED FROM " + get_id() + " to " + new_advisor->get_id();

			current_student->add_new_note(note);
			cout << endl << setw(5) << "";
			cout << "Students were successfully moved." << endl;
		}
		else
			++it;
	}

	FileIO::rewrite_advisees();
}

void Advisor::findAdvisor(string student_id)
{
	transform(student_id.begin(), student_id.end(), student_id.begin(), ::toupper);

	if (student_id.substr(0, 2) != "ST")
	{
		InvalidString error;
		error.message = "Student ID must begin with 'ST'.";
		throw error;
		return;
	}
	for (auto g : student_id.substr(2, 3))
	{
		if (!isdigit(g))
		{
			InvalidString error;
			error.message = "Invalid student ID.";
			throw error;
			return;
		}
	}

	Student* student = NULL;
	Advisor* advisor = NULL;

	student = Advisor::find_student(student_id);

	if (student == NULL)
	{
		cout << setw(5) << "";
		cout << "No such student found!" << endl;
		return;
	}

	advisor = student->get_advisor();

	if (advisor == NULL)
	{
		cout << setw(5) << "";
		cout << student->get_id() << " does not have an advisor." << endl;
		return;
	}

	cout << setw(5) << "";
	cout << "Student " << student_id << " has advisor: " << advisor->get_id();
}

void Advisor::displayAdvisors()
{
	cout << endl << setw(5) << "";
	cout << "Advisors: " << endl;
	for (auto p : advisors)
	{
		p->print_my_info();
		cout << endl;
	}
	cout << endl;

}

void Advisor::displayMajor(string major)
{
	//display number of advisees in that major and the average GPA
	transform(major.begin(), major.end(), major.begin(), ::toupper);

	for (auto m : major)
	{
		if (!isalpha(m))
		{
			InvalidString error;
			error.message = "Error: Invalid Major.";
			throw error;
			return;
		}
	}

	double sum = 0;
	double iter = 0;

	for (auto student : advisees)
	{
		string input = student->get_Major();
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (input == major)
		{
			iter++;
			sum += student->get_GPA();
		}
	}
	if (iter >= 1)
	{
		cout << fixed;
		cout << endl << setw(5) << "";
		cout << iter << " student(s) with major " << major << endl;
		cout << setw(5) << "";
		cout << "Average GPA: " << setprecision(2) << (sum / iter) << endl;
	}
	else
	{
		cout << setw(5) << "";
		cout << "There are no students with that major.";
	}
}

string Advisor::get_room_num()
{
	return room_num;
}
string Advisor::get_phone()
{
	return phone;
}

void Advisor::print_my_info()
{
	cout << setw(5) << "";
	cout << "Advisor ID: " << get_id() << endl;
	cout << setw(5) << "";
	cout << "Phone number: " << get_phone() << endl;
	cout << setw(5) << "";
	cout << "Room number: " << get_room_num() << endl;
}

void Advisor::print_welcome()
{
	cout << setw(34) << "Welcome, Advisor " << get_id() << endl;
}

void Advisor::final_practice()
{
	//#3 on final exam practice
	for_each(students.begin(), students.end(), [=](Student *temp) 
	{
		if (temp->get_hours() > 84)
		{
			cout << endl << "Student: ";
			cout << endl << fixed << setprecision(2) << temp->get_id() << endl << temp->get_GPA();
			double gpa = temp->get_GPA();
			gpa += gpa * 0.1;
			temp->set_GPA(gpa);
			cout << endl << temp->get_GPA();
		}
	});
}