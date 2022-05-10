#ifndef DIRECT_H
#define DIRECT_H

#include "Mark.h"
#include <string>

class Direct {
private:
	std::string label;
	Mark mark;
public:
	Direct(std::string label, Mark mark);
	
	std::string getLabel();
	Mark getMark();
};

#endif