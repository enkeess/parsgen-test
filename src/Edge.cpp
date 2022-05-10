#include "../include/Edge.h"

Edge::Edge(
	int to, std::string label, 
	Mark mark,
	std::vector<Direct> direct
) : 
	to(to),
	label(label),
	mark(mark),
	direct(direct){}

int Edge::getTo() {
	return to;
}

std::string Edge::getLabel() {
	return label;
}

Mark Edge::getMark() {
	return mark;
}

std::vector<Direct> Edge::getDirect() {
	return direct;
}