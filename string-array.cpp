#include "string-array.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief Default constructor for StringArray.
 * 
 * Initializes an empty StringArray with size set to 0.
 */
StringArray::StringArray(){
    this->size = 0;
}

/**
 * @brief Copy constructor for StringArray.
 * 
 * Creates a deep copy of another StringArray instance.
 * 
 * @param other The StringArray instance to copy from.
 */
StringArray::StringArray(const StringArray& other){
    this->size = other.size;
    for (GenericString* str : other.array) {
        if (str) {
            GenericString* string = new String(str->as_string()); // Calls copy constructor of String
            this->array.push_back(string);
        } else {
            this->array.push_back(nullptr);
        }
    }
}

/**
 * @brief Destructor for StringArray.
 * 
 * Releases the memory allocated for the GenericString objects in the array.
 */
StringArray::~StringArray(){
    for (GenericString* str : this->array) {
        delete str; 
    }
}

/**
 * @brief Prints the contents of the StringArray.
 * 
 * Displays the length of the array and its elements.
 */
void StringArray::Print(){
    printf("print length of %d\n", this->length());
    for (int i = 0; i < this->length(); i++) {
        printf("%s ", this->getValue(i)->as_string().get_data()); 
    }
    printf("\n");
}

/**
 * @brief Adds a new string to the StringArray.
 * 
 * @param str The C-style string to be added.
 */
void StringArray::addString(const char* str){
    GenericString* string = new String(str);
    array.push_back(string);
}

/**
 * @brief Retrieves the value at a specific index in the StringArray.
 * 
 * @param index The index of the desired element.
 * @return A pointer to the GenericString at the specified index.
 */
GenericString* StringArray::getValue(const int index) const{
    return this->array[index];
}

/**
 * @brief Returns the number of elements in the StringArray.
 * 
 * @return The size of the array.
 */
int StringArray::length() const{
    return array.size();
}
