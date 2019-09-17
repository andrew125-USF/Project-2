#include "FileIO.h"

using namespace std;

FileIO::FileIO()
{
}

void FileIO::set_up()
{
	open_students();
	open_advisors();
	open_notes();
	open_advisees();
	add_advisees_to_advisor();
}

void FileIO::open_students()
{
	ifstream inStu;
	string username;
	string pwd;
	string major;
	int hours;
	double gpa;
	string entry;
	int count = 0;

	//open student file
	inStu.open("Data_students.txt");

	if (!inStu)
		cout << "Student file could not open." << endl;

	//read from file
	while (inStu) {

		if (!getline(inStu, entry)) break;
		istringstream ss(entry);

		while (ss)
		{
			if (!getline(ss, entry, ',')) break;
			if (entry == "")
				entry = "N/A";

			if (count == 0)
				username = entry;
			else if (count == 1)
				pwd = entry;
			else if (count == 2)
				major = entry;
			else if (count == 3)
				hours = stoi(entry);
			else if (count == 4)
				gpa = stod(entry);
			count++;
		}
		students.push_back(new Student(username, pwd, major, hours, gpa));
		count = 0;
	}

	inStu.close();
}

void FileIO::open_advisors()
{
	string username;
	string pwd;
	string major;
	int count = 0;
	string room;
	string phone;
	string entry;
	ifstream inAdv;

	//open advisor file
	inAdv.open("Data_advisors.txt");

	if (!inAdv)
		cout << "Advisor file could not open." << endl;

	//read from file
	while (inAdv) {

		if (!getline(inAdv, entry)) break;
		istringstream ss(entry);

		while (ss)
		{
			if (!getline(ss, entry, ',')) break;
			if (entry == "")
				entry = "N/A";

			if (count == 0)
				username = entry;
			else if (count == 1)
				pwd = entry;
			else if (count == 2)
				room = entry;
			else if (count == 3)
				phone = entry;
			count++;
		}
		advisors.push_back(new Advisor(username, pwd, room, phone));
		count = 0;
	}
	inAdv.close();
}

void FileIO::open_notes()
{
	ifstream inNotes;
	string username;
	string entry;
	int i = 0;
	inNotes.open("Data_advisingNotes.txt");
	if (!inNotes)
		cout << "Notes file could not open." << endl;

	while (inNotes)
	{
		if (getline(inNotes, entry))
		{
			notes.push_back(entry);
			i++;
		}
	}
	inNotes.close();

	i = 0;
	for (auto p : notes)
	{
		auto found = p.find_first_of(")");
		username = p.substr(found + 2, 5);
		the_notes[username].push_back(p);
	}

	for (auto s : students)
	{
		string user = s->get_id();
		s->set_notes(the_notes[user]);
	}
}

void FileIO::open_advisees()
{
	string username;
	string entry;
	int count = 0;
	ifstream inAdvisees;
	inAdvisees.open("Data_advisees.txt");
	if (!inAdvisees)
		cout << "Advisee file could not open." << endl;

	while (inAdvisees) {

		if (!getline(inAdvisees, entry)) break;
		istringstream ss(entry);

		while (ss)
		{
			if (!getline(ss, entry, ',')) break;
			if (count == 0)
				username = entry;
			else
				advisees[username].push_back(entry);
			count++;
		}
		if (count == 1)
		{
			advisees[username].push_back("N/A");
		}
		count = 0;
	}

	inAdvisees.close();
}

void FileIO::add_advisees_to_advisor()
{
	Student* student;

	for (Advisor* advisor : advisors)
	{
		vector<string> student_ids = advisees[advisor->get_id()];
		for (string id : student_ids)
		{
			auto it = find_if(students.begin(), students.end(), [=](Student* student) { return student->get_id() == id; });
			if (it != students.end())
			{
				student = *it;
				advisor->addStudent(student);
			}
		}
	}
}

string FileIO::log_in(string user_type)
{
	string username;
	string pwd;
	username = "";
	pwd = "";
	cout << endl << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl;
	cout << setw(30) << "Log-in" << endl;
	cout << setw(5) << "";
	cout << "_____________________________________________" << endl;
	cout << setw(15) << "Username: ";
	getline(cin >> ws, username);
	cout << setw(15) << "Password: ";
	getline(cin >> ws, pwd);
	User* user = nullptr;
	if (user_type == "ST")
		user = Advisor::find_student(username, pwd);
	if (user_type == "AD")
		user = Advisor::find_advisor(username, pwd);
	if (user != nullptr)
	{
		cout << endl << endl;
		user->print_welcome();
		return user->get_id();
	}
	else
	{
		return "";
	}

	return username;
}

void FileIO::rewrite_notes()
{
	fstream file;
	file.open("Data_advisingNotes.txt", ios::out);
	if (!file.is_open())
	{
		cout << "Notes file could not open." << endl;
		return;
	}
	vector<Student*> the_students = Advisor::get_students();
	map<string, vector<string>> write_notes;
	string write, user;
	for (auto s : the_students)
	{
		user = s->get_id();
		vector<string> set_of_notes = s->get_notes();
		for (auto k : set_of_notes)
		{
			write_notes[user].push_back(k);
		}
	}

	for (auto w : write_notes)
	{
		for (auto n : w.second)
		{
			write = n + '\n';
			file << write;
		}
	}

	file.close();
}

void FileIO::rewrite_students()
{
	string write;
	fstream file;
	file.open("Data_students.txt", ios::out);
	if (!file.is_open())
	{
		cout << "Student file could not open." << endl;
		return;
	}

	vector<Student*> students = Advisor::get_students();
	for (auto student : students)
	{
		write = student->get_id();
		write += "," + student->get_pwd();
		if (student->get_Major() == "N/A")
			write += ",";
		else
			write += "," + student->get_Major();
		//if statement
		write += "," + to_string(student->get_hours());
		stringstream txt;
		txt << fixed << setprecision(2) << student->get_GPA();
		write += "," + txt.str() + '\n';
		file << write;
	}
	file.close();
}

void FileIO::rewrite_advisees()
{
	fstream file;
	file.open("Data_advisees.txt", ios::out);
	if (!file.is_open())
	{
		cout << "Advisee file could not open." << endl;
		return;
	}

	vector<Advisor*> advisors = Advisor::get_advisors();
	for (auto advisor : advisors)
	{
		string write;
		write = advisor->get_id();

		vector<Student*> advisees = advisor->get_advisees();
		for (auto advisee : advisees)
		{
			//searches outter loop keys
			if (advisee->get_id() == "N/A")
				break;
			write += "," + advisee->get_id();
		}
		write += '\n';
		file << write;
	}

	file.close();
}

vector<Student*> FileIO::get_students()
{
	return students;
}

vector<Advisor*> FileIO::get_advisors()
{
	return advisors;
}

map<string, vector<string>> FileIO::get_note_list()
{
	return the_notes;
}

map<string, vector<string>> FileIO::get_advisees_list()
{
	return advisees;
}