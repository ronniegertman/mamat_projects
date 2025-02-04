#include "string.h"
#include <cstdlib>
#include <cctype>

/**
 * @brief Default constructor for the String class.
 * 
 * @param str A C-style string to initialize the String object.
 */
String::String(const char* str)
{
	this->length = strlen(str);
	this->data = new char[length + 1];
	strcpy(data, str);
}

/**
 * @brief Copy constructor for the String class.
 * 
 * @param str The String object to copy from.
 */
String::String(const String &str)
{
	this->length = str.get_length();
	this->data = new char[length + 1];
	strcpy(data, str.get_data());
}

/**
 * @brief Destructor for the String class to deallocate dynamic memory.
 */
String::~String(){
	delete[] this->data;
}

/**
 * @brief Gets the length of the string.
 * 
 * @return The length of the string.
 */
int String::get_length() const{
	return this->length;
}

/**
 * @brief Gets the data of the string.
 * 
 * @return A pointer to the character data of the string.
 */
char* String::get_data() const{
	return this->data;
}

/**
 * @brief Assignment operator to copy text from a C-style string to this String object.
 * 
 * @param str The C-style string to copy from.
 * @return Reference to the current GenericString object.
 */
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

/**
 * @brief Equality operator to compare with a C-style string.
 * 
 * @param str The C-style string to compare with.
 * @return true if the strings are equal, false otherwise.
 */
bool String::operator==(const char *str) const{
	if(str == NULL && this->data == NULL){
		return true;
	}
	return (strcmp(str, this->data) == 0);
}

/**
 * @brief Equality operator to compare with another GenericString object.
 * 
 * @param other The GenericString object to compare with.
 * @return true if the strings are equal, false otherwise.
 */
bool String::operator==(const GenericString &other) const{
	return (strcmp(other.as_string().get_data(), this->data) == 0);
}

/**
 * @brief Converts the string to an integer.
 * 
 * @return The integer representation of the string.
 */
int String::to_integer() const{
	return atoi(this->data);
}

/**
 * @brief Trims leading and trailing whitespace from the string.
 * 
 * @return Reference to the current GenericString object.
 */
GenericString& String::trim() {
	int start = 0;
	while (isspace(this->data[start])) {
		start++;
	}

	int end = strlen(this->data) - 1;
	while (end >= start && isspace(this->data[end])) {
		end--;
	}

	if (start > end) {
		delete[] this->data;
		this->length = 0;
		this->data = new char[1];
		this->data[0] = '\0';
		return *this;
	}

	int newLength = end - start + 1;
	char* temp = new char[newLength + 1];
	memmove(temp, this->data + start, newLength);
	temp[newLength] = '\0';

	delete[] this->data;
	this->data = temp;
	this->length = newLength;

	return *this;
}

/**
 * @brief Returns a reference to this String object.
 * 
 * @return Reference to this String object.
 */
String& String::as_string(){
	return dynamic_cast<String&>(*this);
}

/**
 * @brief Returns a constant reference to this String object.
 * 
 * @return Constant reference to this String object.
 */
const String& String::as_string() const{
	return dynamic_cast<const String&>(*this);
}

/**
 * @brief Factory function to create a new GenericString object.
 * 
 * @param str The C-style string to initialize the GenericString.
 * @return Pointer to the newly created GenericString object.
 */
GenericString* make_string(const char *str){
	GenericString* s = new String(str);
	return s;
}

/**
 * @brief Splits the string into substrings based on the given delimiters.
 * 
 * @param delimiters A C-style string containing delimiter characters.
 * @return A StringArray containing the split substrings.
 */
StringArray String::split(const char *delimiters) const{
	char *token = strtok(this->data, delimiters);
	StringArray strings;

	while(token != NULL){
		strings.addString(token);
		token = strtok(NULL, delimiters);
	}
	return strings;
}
