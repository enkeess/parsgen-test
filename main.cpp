#include <iostream>
using namespace std;

#include "include/Parser.h"
#include "include/Dependencies.h"

int main(int argc, char* argv[]) { 
	try {
		Parser p("input.txt", _graphs);
		p.run();
	}
	catch(const char* str) {
		cout << str << "\n";
	}
	catch (...) {
		cout << "Something wrong\n";
	}

	return 0;
}