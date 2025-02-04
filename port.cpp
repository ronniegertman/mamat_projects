#include "port.h"
#include "generic-string.h"
#include "string.h"
#include "string-array.h"
#include <string.h>

/**
 * @brief Constructs a Port object by parsing the given rule string.
 * 
 * @param rule A string representing the rule to be parsed (e.g., "src-port=1000-2000").
 */
Port::Port(String& rule){
	rule.trim();
	StringArray words = rule.split(" =/.");
	GenericString* direction_port = words.getValue(0); // words[0] is GenericString*

	// Determine the direction (source or destination port)
	if(*direction_port == "src-port"){
		this->dir = SRC;
	}else if(*direction_port == "dst-port"){
		this->dir = DST;
	}

	// Extract port range
	StringArray range = words.getValue(1)->split("-");
	this->low = range.getValue(0)->to_integer();
	this->high = range.getValue(1)->to_integer();
}

/**
 * @brief Extracts the port from the provided packet words based on the direction.
 * 
 * @param packet_words StringArray containing the split parts of the packet.
 * @return The extracted port number as an integer.
 */
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
}

/**
 * @brief Matches the port in the provided packet with the stored port range.
 * 
 * @param packet A GenericString representing the packet containing port information.
 * @return true if the packet's port falls within the stored range, false otherwise.
 */
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
