#include "string.h"
#include <cstdlib>
#include <cctype>

// using namespace String;
//default constructor
String::String(const char* str)
{
	this->length = strlen(str);
	this->data = new char[length + 1];
	strcpy(data, str);
}

//copy constructor
String::String (const String &str)
{
	this->length = str.get_length();
	this->data = new char[length + 1];
	strcpy(data, str.get_data());
}

//destructor
String::~String(){
	delete[] this->data;
}

//getters
int String::get_length() const{
	return this->length;
}
char* String::get_data() const{
	return this->data;
}

//the text in str will be copied to this
GenericString& String::operator=(const char *str){
	delete[] this->data;
	if (str == NULL){
		this->data = NULL;
		this->length = 0;
		return *this;
	}
	int length = strlen(str);
	this->length = length;
	this->data = new char[length + 1];
	strcpy(this->data, str);
	return *this;
}

bool String::operator==(const char *str) const{
	if(str == NULL && this->data == NULL){
		return true;
	}
	//strcmp returns zero if equal
	return (strcmp(str, this->data) == 0);
}

bool String::operator==(const GenericString &other) const{
	//NULL?
	return (strcmp(other.as_string().get_data(), this->data) == 0);
}

int String::to_integer() const{
	return atoi(this->data);
}

GenericString& String::trim() {
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

String& String::as_string(){
	return dynamic_cast<String&>(*this);
}

const String& String::as_string() const{
	return dynamic_cast<const String&>(*this);
}

GenericString* make_string(const char *str){
	GenericString* s = new String(str);
	return s;
}

StringArray String::split(const char *delimiters) const{
	char *token = strtok(this->data, delimiters);
	StringArray strings;

	while(token != NULL){
		strings.addString(token);
		token = strtok(NULL, delimiters);

	}
	return strings; //pointer? destructor called? (to delete the linked list)
}






