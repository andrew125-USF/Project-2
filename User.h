#ifndef USER_h
#define USER_h

#include <string>
#include <iostream>

using namespace std;

//Exception Handling
struct InvalidDouble
{
	string message;
	double dnum;
};

struct InvalidInt
{
	string message;
	int num;
};

struct InvalidString
{
	string message;
	string text;
};

struct InvalidRange
{
	string message;
	int invalidmin;
	int invalidmax;
};

class User {
private:
	string id;
	string pwd;
	int count = 0;
public:
	//Constructor
	User(string id, string password);

	//Getters
	string get_id();
	string get_pwd();

	//Overrides
	virtual void print_my_info();
	virtual void print_welcome();
};


#endif
