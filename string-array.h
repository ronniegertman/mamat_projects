#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H

#include "generic-string.h"
#include <vector>
#include "string.h"

class StringArray{
	int size;
	std::vector<GenericString*> array;

public:
	StringArray();
	StringArray(const StringArray& other);
	~StringArray();

	void addString(const char* str);
	GenericString* getValue(const int index) const;
	int length() const;
};

#endif
