#ifndef VERTEX_H
#define VERTEX_H

// #include "STATE_NAME.h"
#include "Edge.h"

#include <string>
#include <set>
#include <vector>

class Vertex {
private:
	std::string name;
	int id;
	std::vector<Edge> edges;

public: 
	Vertex(std::string name, int id, std::vector<Edge> edges);
	Vertex(std::string name, int id, Edge edge);
	Vertex(std::string name, int id);
	Vertex(){}
	
	std::string getName();
	int getId();
	std::vector<Edge> getEdges();
	std::set<std::string> getPossibleStr();
};

#endif