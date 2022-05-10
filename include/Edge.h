#ifndef EDGE_H
#define EDGE_H

#include "Mark.h"
#include "Direct.h"
#include <string>
#include <vector>

class Edge {
private:
	int to;
	std::string label;
	Mark mark;
	std::vector<Direct> direct;

public: 
	Edge(
		int to, std::string label, 
		Mark mark,
		std::vector<Direct> direct
	);

	Edge(){};

	int getTo();
	std::string getLabel();
	Mark getMark();
	std::vector<Direct> getDirect();
};

#endif