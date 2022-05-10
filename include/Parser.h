#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include <vector>
#include <stack>

#define DEFAULT_GRAPH_ID 0
#define DEFAULT_STATE_ID 1

class Parser {
private:
	Vertex curVertex;
	LGraph curGraph;

	std::stack<int> graphsStack; 
	std::stack<Mark> bracketTrace;  

	std::vector<LGraph> graphs;
	Scanner scanner;
	std::set<std::string> getLexeme(Vertex v);
	void updateBracketTrace(Mark m);

public: 
	Parser(const char* filename, std::vector<LGraph> graphs);
	bool run();
};

#endif