#include "std_lib_facilities.h"
class Token
{
public:
	char kind;
	int value;
};

Token get_token();
double expression();
double term();
double primary();



vector<Token> tokens;

int main()
{
	while (cin)
	{
		Token t = get_token();
		tokens.push_back(t);
	}
}