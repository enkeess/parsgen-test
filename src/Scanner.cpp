#include "../include/Scanner.h"
#include <iostream>

Scanner::Scanner(const char* filename) {
	this->filename = filename;

	std::cout<< "filename: " << filename << '\n';
	eof = false;
	openFile();
	fileShift = 0;

	inputStreamFile.seekg(0, inputStreamFile.end);
	fileSize = inputStreamFile.tellg();
	inputStreamFile.seekg(0, inputStreamFile.beg);
}

void Scanner::openFile() {
	inputStreamFile.open(filename);
	if(!inputStreamFile.is_open()) {
		throw "File reading error";
	}
}

void Scanner::closeFile() {
	inputStreamFile.close();
}

int Scanner::getWordMaxSize(const std::set<std::string>& possibleStr) {
    int maxSize = -1;
    int curLength = -1;
    int i = 0;
    for(auto& str:  possibleStr) {
        curLength = str.length();
        maxSize = curLength > maxSize ? curLength : maxSize; 
    }

    return maxSize;
}


std::string Scanner::getStrFromBuf(int maxsize) {
    std::string str = "";
	
	int length = maxsize;
	int bufSlice = 0;
	int bufFill = readIntoBuf();

	while(length > 0 && bufFill > 0) {
		bufSlice = length > bufFill ? bufFill : length;
		length -= bufSlice;
		str += std::string(buf, buf + bufSlice);
		bufFill = readIntoBuf();
	}

    return str;
}


std::set<std::string> Scanner::getLexeme(std::set<std::string> possibleStr) {
	std::string str = getStrFromBuf(getWordMaxSize(possibleStr));
	std::set<std::string> res = {};

	for(auto& word: possibleStr) {
        if(str.find(word) == 0) {
            res.insert(word);
        }
    }

	return res;
}

int Scanner::readIntoBuf() {
	if(isEOF()) {
		return 0;
	}

	int start = inputStreamFile.tellg();
	start = start >= 0 ? start : fileSize;

	!inputStreamFile.eof() && inputStreamFile.read(buf, BUFSIZE);
	if(inputStreamFile.eof()) {
		closeFile();
	}
	
	int end = inputStreamFile.tellg();
	end = end > 0 ? end : fileSize;

	return end - start;
};

void Scanner::updateFileShift(std::string str) {
	if(inputStreamFile.eof()) {
		openFile();
	}

	fileShift += str.length();

	if(fileShift == fileSize) {
		eof = true;
	}

	inputStreamFile.seekg(fileShift, inputStreamFile.beg);
}

bool Scanner::isEOF() {
	return eof;
}