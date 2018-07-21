#include "std_lib_facilities.h"
class Token
{
public:
	Token(char kind):kind(kind) {};
	Token(char kind, double value) :kind(kind), value(value) {};
	Token(char kind, string name) :kind(kind), name(name) {};
	char kind;
	double value;
	string name;
};

class Token_stream
{
public:
	Token get();
	void putback(Token token);
	void ignore(char c);
private:
	bool full;
	Token buffer=0;
};

class Variable
{
public:
	string var;
	double val;
};

double expression();
double statement();
double term();
double primary();
double declaration();
double get_value(string var);
void calculate();
void clean_up_mess();
bool is_declared(string var);
double define_name(string var, double val);



const char number = '8';//if a kind of value is '8',it is a number
const char quit = 'q';
const char print = ';';
const char let = 'l';
const char name = 'n';
const string prompt = ">";
const string result = "=";
const string declkey = "let";

vector<Variable> var_table;

Token_stream token_stream;
vector<Token> tokens;

int main()
try 
{
	calculate();
	keep_window_open();
	return 0;
}
catch (exception& e) {
	cerr << e.what() << '\n';
	keep_window_open("~~");
	return 1;
}
catch (...) {
	cerr << "exception \n";
	keep_window_open("~~");
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

double statement()
{
	Token token = token_stream.get();
	switch (token.kind)
	{
	case let:
		return declaration();
	default:
		token_stream.putback(token);
		return expression();
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
		case '%':
		{
			double d = primary();
			if (d == 0) error("divided by zero");
			left = fmod(left, d);
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

	case number:
		return token.value;
	case name:
		return get_value(token.name);
	case '+':
		return primary();
	case '-':
		return -primary();
	default:
		error("primary expected");
		break;
	}
}

double declaration()
{
	Token token = token_stream.get();
	if (token.kind != name) error("name expected in declartion");
	string var_name = token.name;
	Token token2 = token_stream.get();
	if (token2.kind != '=')error("= missing in declaration of " + var_name);
	double d = expression();
	define_name(var_name, d);
	return d;
}

double get_value(string var)
{
	if (is_declared(var))
	{
		for (const auto v : var_table)
		{
			if (v.var == var)
			{
				return v.val;
			}
		}
	}
	else
	{
		error("undeclared variable " + var);
	}
}

void calculate()
{
	while (cin)
	{
		try {
			cout << prompt;
			Token t = token_stream.get();
			while (t.kind == print)
				t = token_stream.get();
			if (t.kind == quit)
			{
				keep_window_open();
				return;
			}
			token_stream.putback(t);
			cout << "=" << statement() << endl;
		}
		catch (exception & e)
		{
			cerr << e.what() << endl;
			clean_up_mess();
		}
	}
}

void clean_up_mess()
{
	token_stream.ignore(print);
}

bool is_declared(string var)
{
	for (const auto &v : var_table)
	{
		if (v.var == var)
		{
			return true;
		}
	}
	return false;
}

double define_name(string var, double val)
{
	if (is_declared(var))
	{
		error(var + " defined twice!");
	}
	else
	{
		var_table.push_back(Variable{var, val});
		return val;
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
	case quit:
	case print:
	case '+':
	case'-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '=':
		return Token{ ch }; break;
	case '.':
	case '0':case'1':case '2':case '3':case'4':case'5':case'6':case'7':case'8':case '9':
	{
		cin.putback(ch);
		double d;
		cin >> d;
		return Token{ number,d };
	}
	default:
		if (isalpha(ch))
		{
			string s{};
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.putback(ch);
			if (s == declkey) return Token(let);
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::putback(Token token)
{
	if (full)error("putback() into a full buffer");
	full = true;
	buffer = token;
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;
	char ch;
	while (cin >> ch)
	{
		if (ch == c)
		{
			return;
		}
	}
}
