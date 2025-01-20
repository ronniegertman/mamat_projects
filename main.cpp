#include "port.h"
#include "ip.h"
#include "input.h"
#include "string.h"

#define PORT_TYPE 1
#define NOT_PORT_TYPE 0

int field_type(char* rule); //determines whether the rule refers to ip or port

int main(int argc, char **argv){
	//first we figure out whether the rule is relates to a port or an ip
	String rule = String(argv[1]); //asuming argv[1] is the pointer to the rule
	rule.trim();
	if(field_type(rule.get_data()) == PORT_TYPE){ 
		Port field = Port(rule);
	}
	else{
		IP field = IP(rule);
	}
	GenericField& ref = field;
	parse_input(ref);
}

int field_type(char* rule){
	// a rule must start with dst- or src- followed by either port ot ip
	// we compare the first 8 characters
	if(strncmp(rule, "src-port", 8) == 0 || strncmp(rule, "dst-port", 8) == 0){ 
		return PORT_TYPE
	}
	else{
		return NOT_PORT_TYPE
	}
}