// read and write a first name
#include "std_lib_facilities.h"
int main()
{
	cout << "Enter the name of the person you want to write to\n";
	string first_name; // first_name is a variable of type string
	cin >> first_name; // read characters into first_name
	cout << "Enter the name of the person you want to write to\n";
	string friend_name;
	cin >> friend_name;
	cout << "Enter m if the friend is male else enter f\n";
	char friend_sex;
	cin >> friend_sex;
	cout << "Enter the age of the person you want to write to\n";
	int friend_age;
	cin >> friend_age;
	if (friend_age < 0 || friend_age>110)
	{
		simple_error("You are kidding!");
	}
	cout << "Dear " << first_name << ",\n";
	cout << "How are you?\n";
	cout << "Have you seen friend_name lately ?\n";
	cout << "¡°If you see " << friend_name << "please ask " << (friend_sex == 'm' ? "him" : "her") << " to call me.\n";
	if (friend_age < 12)
	{
		cout << "Next year you will be " << friend_age + 1 << " !\n";
	}
	else if (friend_age == 17)
	{
		cout << "Next year you will be able to vote.\n";
	}
	else if (friend_age > 70) {
		cout << "I hope you are enjoying retirement.\n";
	}
	cout << "Yours sincerely C\n";
	keep_window_open();
}