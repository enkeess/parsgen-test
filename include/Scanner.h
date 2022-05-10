#ifndef SCANNER_H
#define SCANNER_H

#include "LGraph.h"

#include <fstream>
#include <string>
#include <set>

#define BUFSIZE 255

class Scanner {
private:
	std::string lex;
    std::ifstream inputStreamFile;
    int fileSize;
	int fileShift;
    char buf[BUFSIZE];
	bool eof;

	const char* filename;

	int getWordMaxSize(const std::set<std::string>& possibleStr);
	int readIntoBuf(); 
	std::string getStrFromBuf(int maxsize);

	void closeFile();
	void openFile();

public:
	Scanner(const char* filename);
	Scanner() {}

	std::set<std::string> getLexeme(std::set<std::string> possibleStr);
	bool isEOF();
	void updateFileShift(std::string str);
};

#endif