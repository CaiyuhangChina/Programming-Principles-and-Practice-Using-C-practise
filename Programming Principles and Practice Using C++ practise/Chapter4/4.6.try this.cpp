#include "std_lib_facilities.h"
int main()
{
	string dislike = "dislike";
	vector<string> words;
	for (string temp; cin >> temp;)
	{
		words.push_back(temp);
	}
	sort(words);
	for (int i = 0; i < words.size(); i++)
	{
		if (i == 0 || words[i] != words[i - 1]) {
			if (words[i] != dislike)
				cout << words[i] << '\t';
			else
				cout << "BLEEP\t";
		}
	}
	cout << '\n';
	keep_window_open();
}