#include port.h
#include ip.h
//are there more needed?
#include <libinput.h>
//is that needed?


int main(int argc, char **argv){
	//first we figure out whether the rule is relates to a port or an ip
	GenericString rule = String(argv[1]); //asuming argv[1] is the pointer to the rule
	rule.trim();
	if(rule.get_data()[4] == 'i'){ //each rule starts with src- or dst- followed by ____port or ____ip
		ip field(rule); //is this good? maybe should make the i in ip class capital
	}
	else{
		Port field(rule);
	}
	GenericField& ref = field;
	parse_input(field);
}