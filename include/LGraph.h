#ifndef LGRAPH_H
#define LGRAPH_H

#include "Vertex.h"

#include <vector>
#include <string>

class LGraph {

private:
	std::string name;
	int id;
	std::set<int> start;
	std::set<int> finish;
	std::vector<Vertex> vertices;

public: 
	LGraph(
		std::string name,
		int id,
		std::set<int> start,
		std::set<int> finish,
		std::vector<Vertex> vertices
	);

	LGraph(){}

	std::vector<Vertex> getVertices();
	std::set<int> getFinish();
	int getId() {
		return id;
	}
	
};

#endif