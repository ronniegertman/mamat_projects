#include "string-array.h"
#include <string.h>
using namespace StringArray;

StringArray(){
	this->size = 0;
}

StringArray(const StringArray& other){
	this-> size = other.size;
	for (GenericString* str : other.strings) {
            if (str) {
            	GenericString* string = new String(str->as_string()); //string copy constructor called bli neder
                strings.push_back(string);
            } else {
                strings.push_back(nullptr);
            }
        }
}

~StringArray(){
  	for (GenericString* str : this->array) {
    	delete str; 
	}
}

void addString(const char* str){
	GenericString* string = new String(str);
	array.push_back(string);

}

GenericString* getValue(const int index) const{
	return this->array[index];
}