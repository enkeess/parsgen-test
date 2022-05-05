#ifndef EDGE_H
#define EDGE_H


#include "Mark.h"
#include <string>
#include <vector>


class Edge {
private:
	int to;
	std::string label;
	std::vector<Mark> mark;
	std::vector<std::string> trace;

public: 
	Edge(
		int to, std::string label, 
		std::vector<Mark> mark,
		std::vector<std::string> trace
	);

	Edge(
		int to,
		std::string label,
		std::vector<Mark> mark
	);

	Edge(){};


	int getTo();
	std::string getLabel();
	std::vector<Mark> getMark();
	std::vector<std::string> getTrace();
};

#endif