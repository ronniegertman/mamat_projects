#include "ip.h"
#include "generic-string.h"
#include "string.h"
#include "string-array.h"
#include <string.h>
using namespace ip;

static const int BUFFER_SIZE = 32;
static unsigned int calculate_ip_address(StringArray words, int index);

ip(String& rule){
	rule->trim();
	StringArray words = rule->split(" =/.");

	//using override of == operator in GenericString
	if(words.getValue(0) == "src-ip"){
		this->dir = SRC;
	}else if(words.getValue(0) == "dst-ip"){
		this->dir = DST;
	}
 
 	int length = words.length();
	this->mask = words.getValue(length - 1)->to_integer(); //words[n] is genericString*
	this->address = calculate_ip_address(words, 1);
}

static unsigned int calculate_ip_address(StringArray words, int index){
	unsigned int ip = 0;
	for(int i=index, i<(index+3); i++){
		ip += words.getValue(i)->to_integer();
		ip <<= 8;
	}
	ip += words.getValue(index + 3)->to_integer(); // no need to shift LSByte
	return ip;
}

bool compare_ip_with_mask(unsigned int other_ip){
	return (other_ip >> (BUFFER_SIZE - this->mask)) == (this->address >> (BUFFER_SIZE - this->mask));
}

bool match(const GenericString &packet) const{
	packet->trim();
	StringArray packet_words = packet.split(",=. ");

	switch (this->dir){
		default:
		case SRC:
			unsigned int packet_src_ip = calculate_ip_address(packet_words, 1);
			return this->compare_ip_with_mask(packet_src_ip);

		break;
		case DST:
			unsigned int packet_dst_ip = calculate_ip_address(packet_words, 5);
			return this->compare_ip_with_mask(packet_dst_ip);
		break;
	}
}
