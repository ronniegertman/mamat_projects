#include <string.h>
#include "string.h"


using namespace String;
//default constructor
String(const char* str = "")
: length(strlen(str)), data(new char[length + 1])
{
	strcpy(data, str);
}

//copy constructor
String (const String &str)
: length(str.getLength()), data(new char[length +1])
{
	strcpy(data, str.getData());
}

//destructor
~String(){
	delete[] this->data;
}

//getters
int getLength() const{
	return this->length;
}
char* getData() const{
	return this->data;
}

String& operator=(const char *str){
	delete[] this->data;
	if (str == NULL){
		this->data = NULL;
		this->length = 0;
		return NULL;
	}
	int length = strlen(str);
	this->length = length;
	this->data = new char[length + 1];
	strcpy(this->data, str);
	return *this;
}

bool operator==(const char *str) const{
	if(str == NULL && this->data == NULL){
		return true;
	}
	//strcmp returns zero if equal
	return (strcmp(str, this->data) == 0);
}

bool operator==(const String &other) const{
	return (strcmp(other.data, this->data) == 0);
}

int to_integer() const{
	return atoi(this->data);
}

String& trim() {
	//find beginning and end indexes that don't contain spaces
    int start = 0;
    while (isspace(this->data[start])) {
        start++;
    }

    int end = strlen(this->data) - 1;
    while (end >= start && isspace(this->data[end])) {
        end--;
    }

    //check if string is empty after trimming
    if (start > end) {
        delete[] this->data;
        this->length = 0;
        this->data = new char[1];
        this->data[0] = '\0';
        return *this;
    }

    //memory allocation of the new sized string
    int newLength = end - start + 1;
    char* temp = new char[newLength + 1];
    memmove(temp, this->data + start, newLength);
    temp[newLength] = '\0';

    //replacing the old data with the trimmed data
    delete[] this->data;
    this->data = temp;
    this->length = newLength;

    return *this;
}

String& as_string(){
	return dynamic_cast<String&>(GenericString);
}

const String& as_string() const{
	return dynamic_cast<String&>(GenericString);
}

GenericString* make_string(const char *str){
	GenericString* s = new String(str);
	return s;
}

StringArray split(const char *delimiters) const{
	char *token = strtok(this->data, delimiters);
	StringArray strings;

	while(token != NULL){
		strings.addString(token);
		token = strtok(NULL, delimiters);

	}
	return strings; //pointer? destructor called? (to delete the linked list)
}






