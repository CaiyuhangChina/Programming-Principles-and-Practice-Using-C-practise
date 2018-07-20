#include "std_lib_facilities.h"

class Token
{
public:
	char kind;
	double value;
};

class Token_stream
{
public:
	Token get();
	void putback(Token token);
private:
	bool full;
	Token buffer;
};


double expression();
double term();
double primary();



Token_stream token_stream;
vector<Token> tokens;

int main()
try {
	double val = 0;
	while (cin)
	{
		Token t = token_stream.get();
		if(t.kind=='q')break;
		if (t.kind == ';')cout << "=" << val << endl;
		else token_stream.putback(t);
		val = expression();
	}
		
	keep_window_open();
}
catch (exception& e) {
	cerr << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "exception \n";
	keep_window_open();
	return 2;
}


double expression()
{
	double left = term();
	Token token = token_stream.get();
	while (true)
		switch (token.kind)
		{
		case '+':
			left += term();
			token = token_stream.get();
			break;
		case '-':
			left -= term();
			token = token_stream.get();
			break;
		default:
			token_stream.putback(token);
			return left;
		}
}

double term()
{
	double left = primary();
	Token token = token_stream.get();
	while (true)
	{

		switch (token.kind)
		{
		case '*':
			left *= primary();
			token = token_stream.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			token = token_stream.get();
			break;
		}
		default:
			token_stream.putback(token);
			return left;
			break;
		}
	}
}

double primary()
{
	Token token = token_stream.get();
	switch (token.kind)
	{
	case '(':
	{
		double d = expression();
		token = token_stream.get();
		if (token.kind != ')') error("')' expected!");
		return d;
	}
	case '8':
		return token.value;
	default:
		error("primary expected");
		break;
	}
}


Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;
	switch (ch)
	{
	case 'q':
	case ';':
	case '+':case'-':case '*':case '/':case '(':case ')':
		return Token{ ch }; break;
	case '.':
	case '0':case'1':case '2':case '3':case'4':case'5':case'6':case'7':case'8':case '9':
	{
		cin.putback(ch);
		double d;
		cin >> d;
		return Token{ '8',d };
	}
	default:
		error("Bad token");
	}
}

void Token_stream::putback(Token token)
{
	if (full)error("putback() into a full buffer");
	full = true;
	buffer = token;
}
