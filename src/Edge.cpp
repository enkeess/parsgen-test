#include "../include/Edge.h"

Edge::Edge(
	int to, std::string label, 
	std::vector<Mark> mark,
	std::vector<std::string> trace
) : 
	to(to),
	label(label),
	mark(mark),
	trace(trace){}

Edge::Edge(
	int to,
	std::string label,
	std::vector<Mark> mark
) : 
	to(to),
	label(label),
	mark(mark),
	trace({}){}

int Edge::getTo() {
	return to;
}

std::string Edge::getLabel() {
	return label;
}

std::vector<Mark> Edge::getMark() {
	return mark;
}

std::vector<std::string> Edge::getTrace() {
	return trace;
}