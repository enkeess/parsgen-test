#ifndef MARK_H
#define MARK_H

#include <string>

enum MarkType {
	OPEN,
	CLOSE,
	NONE
};

class Mark {
private:
	MarkType type;
	std::string label;
	
public: 
	Mark();
	Mark(MarkType type);
	Mark(MarkType type, std::string label);
	MarkType getType();
	std::string getLabel();
};
#endif