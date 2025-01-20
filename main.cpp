#include "port.h"
#include "ip.h"
#include "input.h"
#include "string.h"

int main(int argc, char **argv){
	//first we figure out whether the rule is relates to a port or an ip
	String rule = String(argv[1]); //asuming argv[1] is the pointer to the rule
	rule.trim();
	if(rule.get_data()[4] == 'i'){ //each rule starts with src- or dst- followed by ____port or ____ip
		IP field = IP(rule);
	}
	else{
		Port field = Port(rule);
	}
	GenericField& ref = field;
	parse_input(ref);
}

