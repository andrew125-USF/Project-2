#ifndef ADVISOR_H
#define ADVISOR_H
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include "User.h"
#include "Student.h"

using namespace std;

class Advisor : public User
{
private:
	// all the students and advisors
	static vector<Student*> students;
	static vector<Advisor*> advisors;

	// advisees of this advisor
	vector<Student*> advisees;

	string name;
	string phone;
	string room_num;
	string key;

	//Display students
	void displayStudents_byid();
	void displayStudents_byMajor();
	void displayStudents_byhours();

public:
	//Constructors
	Advisor(string id, string password, string room_num, string phone);

	// Function template to find any vector of students or advisors
	template <class T>
	bool IsFound(vector<T> myvec, string user_id);

	//get and set the list of students and advisors
	static void set_students(vector<Student*> student_list);
	static void set_advisors(vector<Advisor*> advisor_list);
	static vector<Advisor*> get_advisors();
	static vector<Student*> get_students();

	//find a student or advisor from list of students and advisors
	static Student* find_student(string id, string pwd);
	static Advisor* find_advisor(string id, string pwd);
	static Advisor* find_advisor(string advisor_id);
	static Student* find_student(string student_id);

	//Getters
	string get_room_num();
	string get_phone();

	//Display advisees
	void displayStudents(int sort_type);
	void findStudent(Advisor* the_advisor, string major, string minhour, string maxhour);

	//Find an advisee
	void findStudent(string student_id);
	void findStudent_byMajor(string major);
	void findStudent(double GPA);
	void displayRange(Advisor* the_advisor, string minS, string maxS);

	//view, add, and save notes
	void displayNotes(string student_id);
	bool add_new_note(string student_id);

	//add or delete student soley by ID
	bool addStudent(string student_id);
	void addStudent(Student* student);
	bool deleteStudent(string student_id);
	vector<Student*> get_advisees();

	//move collection of students based on major
	void moveStudents(string major, string advisor_id, string authorization_code);

	//find advisor of student who isnt your advisee
	void findAdvisor(string student_id);

	//display all advisors
	void displayAdvisors();

	//displays a count of advisees in a specific major and the average GPA
	void displayMajor(string major);

	//overrides
	void print_my_info() override;
	void print_welcome() override;
	void final_practice();
};

#endif //ADVISOR_H