#ifndef STRING_H
#define STRING_H
#include "generic-string.h"
#include "string-array.h"
#include <string.h>

class String: public GenericString {
	char* data;
	int length;

public:
	String(const char* str);
	String (const String &str);
	GenericString& operator=(const char *str);
	~String();

	bool operator==(const char *str) const;
	bool operator==(const GenericString &other) const;
	
	StringArray split(const char *delimiters) const;
	int to_integer() const;
	GenericString& trim();

	String& as_string();
    const String& as_string() const;

    //getters
    int get_length() const;
    char* get_data() const;


};

GenericString* make_string(const char *str);
#endif
