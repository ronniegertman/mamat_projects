#include "port.h"
#include "generic-string.h"
#include "string.h"
#include "string-array.h"
#include <string.h>
using namespace Port;

Port(String& rule){
	rule->trim();
	StringArray words = rule->split(" =/.");
	GenericString* first_word = words.getValue(0); //words[0] is genericString*, 
	//as_string returns String&
	if(first_word == "src-port"){
		this->dir = SRC;
	}else if(first_word == "dst-port"){
		this->dir = DST;
	}

	StringArray range = words.getValue(1)->as_string().split("-");
	this->high = range.getValue(1)->as_string().to_integer();
	this->low = range.getValue(0)->as_string().to_integer();
}

bool match(const GenericString &packet) const{
	packet->trim();
	StringArray packet_words = packet.split(",=. ");
	switch(this->dir){
		case SRC:
			int src_port = words.getValue(11)->to_integer();
			return (src_port >= this->low && src_port <= this->high);
		break;	
		case DST:
			int src_port = words.getValue(13)->to_integer();
			return (src_port >= this->low && src_port <= this->high);
		break;
	}
	return false;
}