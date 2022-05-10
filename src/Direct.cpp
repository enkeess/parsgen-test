#include "../include/Direct.h"

Direct::Direct(
	std::string label, 
	Mark mark
) : 
	label(label),
	mark(mark){}

std::string Direct::getLabel() {
	return label;
}

Mark Direct::getMark() {
	return mark;
}
