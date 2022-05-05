#include "../include/Vertex.h"
#include <iostream>
Vertex::Vertex(
	std::string name,
	int id,
	std::vector<Edge> edges
) : 
	name(name),
	id(id),
	edges(edges){}

Vertex::Vertex(
	std::string name,
	int id,
	Edge edge
) : 
	name(name),
	id(id),
	edges({edge}){}


Vertex::Vertex(
	std::string name,
	int id
) : 
	name(name),
	id(id),
	edges({}){}


std::string Vertex::getName() {
	return name;
}


int Vertex::getId() {
	return id;
}

std::vector<Edge> Vertex::getEdges() {
	return edges;
}

std::set<std::string> Vertex::getPossibleStr() {
	std::set<std::string> res = {};

	for(auto& edge: this->edges) {
		res.insert(edge.getLabel());
	}

	return res;
}