#include "ip.h"
#include "generic-string.h"
#include "string.h"
#include "string-array.h"
#include <string.h>

using namespace ip;
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
	this->address = calculate_ip_address(words, 1) >> (32 - this->mask);
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

bool match(const GenericString &packet) const{
	packet->trim();
	StringArray packet_words = packet.split(",=. ");

	switch (this->dir){
		default:
		case SRC:
			packet_src_ip = calculate_ip_address(packet_words, 1) >> (32 - this->mask);
			return packet_src_ip == this->address;

		break;
		case DST:
			packet_dst_ip = calculate_ip_address(packet_words, 5) >> (32 - this->mask);
			return packet_dst_ip == this->address;
		break;
	}
}

	// if(this->flag == 0){ //handle src ip
	// 	char* first_word = packet_words.getValue(0)->as_string().get_data();
	// 	if(strcmp(first_word, "src-ip") != 0){
	// 		return false;
	// 	}
	// 	//copy constructor and destructor?
	// 	return handle_src_ip(packet_words);
	// } 

	// if(this->flag == 1){ //handle dst ip
	// 	char* dst_word = packet_words.getValue(5)->as_string().get_data();
	// 	if(strcmp(dst_word, "dst-ip") != 0){
	// 		return false;
	// 	}
	// 	return handle_dst_ip(packet_words);
	// }
	// return false;

// bool handle_src_ip(const StringArray packet_words) const{
// 	unsigned int ip;
// 	for(int i=1; i<4; i++){
// 		unsigned int number = packet_words.getValue(i)->as_string().to_integer();
// 		ip = ip + number;
// 		ip = ip << 8;

// 	}
// 	ip = ip + words.getValue(4)->as_string().to_integer(); //no need to shift the bits of LSByte
// 	ip = (ip >> (32 - this->mask))
// 	return (ip == this->address);
// }

// bool handle_dst_ip(const StringArray packet_words) const{
// 	unsigned int ip;
// 	for(int i=6; i<9; i++){
// 		unsigned int number = packet_words.getValue(i)->as_string().to_integer();
// 		ip = ip + number;
// 		ip = ip << 8;

// 	}
// 	ip = ip + words.getValue(9)->as_string().to_integer(); //no need to shift the bits of LSByte
// 	ip = (ip >> (32 - this->mask))
// 	return (ip == this->address);
// }