#include "port.h"
#include "ip.h"
#include "input.h"
#include "string.h"
#include <string.h>
#include <cstdio>

#define PORT_TYPE 1
#define NOT_PORT_TYPE 0

/**
 * @brief Determines whether the given rule refers to a port or an IP.
 * 
 * @param rule A C-style string representing the rule.
 * @return PORT_TYPE if the rule refers to a port, otherwise NOT_PORT_TYPE.
 */
int field_type(char* rule);

/**
 * @brief The main function to process a rule and parse input based on its type.
 * 
 * @param argc Argument count.
 * @param argv Argument vector where argv[1] is expected to be the rule.
 * @return Exit status code.
 */
int main(int argc, char **argv){
	// First, we figure out whether the rule relates to a port or an IP
	String rule = String(argv[1]); // Assuming argv[1] is the pointer to the rule
	rule.trim(); // Remove any leading/trailing whitespace
	GenericField *field;

	// Determine the type of field and instantiate the appropriate class
	if(field_type(rule.get_data()) == PORT_TYPE){ 
		field = new Port(rule);
	} else {
		field = new IP(rule);
	}

	GenericField& ref = *field;
	parse_input(ref); // Process the input based on the rule

	delete field; // Clean up dynamically allocated memory
}

/**
 * @brief Determines whether the rule refers to a port or an IP.
 * 
 * A rule must start with "dst-" or "src-" followed by either "port" or "ip".
 * Compares the first 8 characters to identify the rule type.
 * 
 * @param rule A C-style string representing the rule.
 * @return PORT_TYPE if the rule refers to a port, otherwise NOT_PORT_TYPE.
 */
int field_type(char* rule){
	if(strncmp(rule, "src-port", 8) == 0 || strncmp(rule, "dst-port", 8) == 0){ 
		return PORT_TYPE;
	} else {
		return NOT_PORT_TYPE;
	}
}
