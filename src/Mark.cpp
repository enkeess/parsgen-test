#include "../include/Mark.h"

Mark::Mark() {
	this->type = NONE;
	this->label = "";
}

Mark::Mark(MarkType type) {
	this->type = type;
	this->label = "";
}

Mark::Mark(MarkType type, std::string label) {
	this->type = type;
	this-> label = label;
}

MarkType Mark::getType() {
	return this->type;
}

std::string Mark::getLabel() {
	return this->label;
}