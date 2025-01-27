#include "port.h"
#include "generic-string.h"
#include "string.h"
#include "string-array.h"
#include <string.h>


Port::Port(String& rule){
	rule.trim();
	StringArray words = rule.split(" =/.");
	GenericString* direction_port = words.getValue(0); //words[0] is genericString*, 
	//as_string returns String&
	if(*direction_port == "src-port"){
		this->dir = SRC;
	}else if(*direction_port == "dst-port"){
		this->dir = DST;
	}

	StringArray range = words.getValue(1)->split("-");

	this->low = range.getValue(0)->to_integer();
	this->high = range.getValue(1)->to_integer();
}


int Port::extract_port_from_packet(StringArray packet_words) const{
	switch(this->dir){
		default:
		case SRC:
			return packet_words.getValue(11)->to_integer();
		break;	
		case DST:
			return packet_words.getValue(13)->to_integer();
		break;
	}
};

bool Port::match(const GenericString &packet) const{
	if(packet.as_string().get_data()[0] == '\0'){
		return false;
	}
	String copied_packet(packet.as_string());
	copied_packet.trim();
	StringArray packet_words = copied_packet.split(",=. ");
	int port = this->extract_port_from_packet(packet_words);
	return (port >= this->low) && (port <= this->high);
}