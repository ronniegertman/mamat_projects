#include "string-array.h"
#include <string.h>

StringArray::StringArray(){
	this->size = 0;
}

StringArray::StringArray(const StringArray& other){
	this->size = other.size;
	for (GenericString* str : other.array) {
            if (str) {
            	GenericString* string = new String(str->as_string()); //string copy constructor called bli neder
                this->array.push_back(string);
            } else {
                this->array.push_back(nullptr);
            }
        }
}

StringArray::~StringArray(){
  	for (GenericString* str : this->array) {
    	delete str; 
	}
}

void StringArray::addString(const char* str){
	GenericString* string = new String(str);
	array.push_back(string);

}

GenericString* StringArray::getValue(const int index) const{
	return this->array[index];
}

int StringArray::length() const{
	return array.size();
}