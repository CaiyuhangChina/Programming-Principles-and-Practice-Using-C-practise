#include "std_lib_facilities.h"

int main() {
	for (char c = 'a'; c <= 'z'; c++) {
		cout << c << '\t' << (int)c << endl;
	}
	keep_window_open();
}