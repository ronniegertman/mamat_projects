#include "ip.h"
#include "generic-string.h"
#include "string.h"
#include "string-array.h"
#include <string.h>

using namespace ip;
ip(String& rule){
	rule->trim();
	StringArray words = rule->split(" =/.");
	char* first_word = words.getValue(0)->as_string().get_data(); //words[0] is genericString*, 
	//as_string returns String&
	
	if(strcmp(first_word, "src-ip") == 0){
		this->flag = 0;
	}else if(strcmp(first_word, "dst-ip") == 0){
		this->flag = 1;
	}
 
	int dont_care = words.getValue(words.length() - 1)->as_string().to_integer(); //words[n] is genericString*
	//as string returns String&
	this->dont_care = dont_care;
	unsigned int ip = 0;

	for(int i=1; i<4; i++){
		unsigned int number = words.getValue(i)->as_string().to_integer();
		ip = ip + number;
		ip = ip << 8;

	}
	ip = ip + words.getValue(4)->as_string().to_integer(); //no need to shift the bits of LSByte
	this->address = ip >> (32 - this->dont_care);

}

bool match(const GenericString &packet) const{
	packet->trim();
	StringArray packet_words = packet->split(",=. ");

	if(this->flag == 0){ //handle src ip
		char* first_word = packet_words.getValue(0)->as_string().get_data();
		if(strcmp(first_word, "src-ip") != 0){
			return false;
		}
		//copy constructor and destructor?
		return handle_src_ip(packet_words);

	} 
	if(this->flag == 1){ //handle dst ip
		char* dst_word = packet_words.getValue(5)->as_string().get_data();
		if(strcmp(dst_word, "dst-ip") != 0){
			return false;
		}
		return handle_dst_ip(packet_words);
	}
	return flase;
}

bool handle_src_ip(const StringArray packet_words) const{
	unsigned int ip;
	for(int i=1; i<4; i++){
		unsigned int number = packet_words.getValue(i)->as_string().to_integer();
		ip = ip + number;
		ip = ip << 8;

	}
	ip = ip + words.getValue(4)->as_string().to_integer(); //no need to shift the bits of LSByte
	ip = (ip >> (32 - this->dont_care))
	return (ip == this->address);
}

bool handle_dst_ip(const StringArray packet_words) const{
	unsigned int ip;
	for(int i=6; i<9; i++){
		unsigned int number = packet_words.getValue(i)->as_string().to_integer();
		ip = ip + number;
		ip = ip << 8;

	}
	ip = ip + words.getValue(9)->as_string().to_integer(); //no need to shift the bits of LSByte
	ip = (ip >> (32 - this->dont_care))
	return (ip == this->address);
}