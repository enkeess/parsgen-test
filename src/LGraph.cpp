#include "../include/LGraph.h"

LGraph::LGraph(
	std::string name,
	int id,
	std::set<int> start,
	std::set<int> finish,
	std::vector<Vertex> vertices
) :
	name(name),
	id(id),
	start(start),
	finish(finish),
	vertices(vertices){}

std::vector<Vertex> LGraph::getVertices() {
	return vertices;
}

std::set<int> LGraph::getFinish() {
	return finish;
}