#include "std_lib_facilities.h"
int main()
{
	cout << "Please enter your first name and age\n";
	string first_name; // string variable
	double ageYear; // integer variable
	cin >> first_name; // read a string
	cin >> ageYear; // read an integer
	cout << "Hello, " << first_name << " (age " << ageYear*12 << ")\n";
}