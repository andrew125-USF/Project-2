#include "User.h"
#include "iomanip"

using namespace std;

User::User(string id, string password)
{
	this->id = id;
	pwd = password;
}

string User::get_id()
{
	return id;
}

string User::get_pwd()
{
	return pwd;
}

void User::print_my_info()
{
	cout << endl << setw(14) << "ID: " << get_id() << endl;
}

void User::print_welcome()
{
}