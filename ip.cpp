#include "ip.h"
#include "generic-string.h"
#include "string.h"
#include "string-array.h"
#include <string.h>
#include <stdio.h>

static const int BUFFER_SIZE = 32;

/**
 * @brief Calculates the IP address from the given words starting at a specific index.
 * 
 * @param words StringArray containing the split parts of the IP address.
 * @param index The starting index from which the IP address parts are considered.
 * @return The calculated IP address as an unsigned integer.
 */
static unsigned int calculate_ip_address(StringArray words, int index);

/**
 * @brief Constructs an IP object by parsing the given rule string.
 * 
 * @param rule A string representing the rule to be parsed (e.g., "src-ip=192.168.1.1/24").
 */
IP::IP(String& rule){
	rule.trim();	
	StringArray words = rule.split(" =/.");

	// Using override of == operator in GenericString
	if(*(words.getValue(0)) == "src-ip"){
		this->dir = SRC;
	}else if(*(words.getValue(0)) == "dst-ip"){
		this->dir = DST;
	}

	int length = words.length();
	this->mask = words.getValue(length - 1)->to_integer(); // words[n] is GenericString*
	this->address = calculate_ip_address(words, 1);
}

/**
 * @brief Calculates the IP address from the given words starting at a specific index.
 * 
 * @param words StringArray containing the split parts of the IP address.
 * @param index The starting index from which the IP address parts are considered.
 * @return The calculated IP address as an unsigned integer.
 */
static unsigned int calculate_ip_address(StringArray words, int index){
	unsigned int ip = 0;
	for(int i = index; i < (index + 3); i++){
		ip += words.getValue(i)->as_string().to_integer();
		ip <<= 8;
	}
	ip += words.getValue(index + 3)->to_integer(); // No need to shift LSByte
	return ip;
}

/**
 * @brief Compares the provided IP address with the stored address using the mask.
 * 
 * @param other_ip The IP address to compare.
 * @return true if the masked parts of both IPs match, false otherwise.
 */
bool IP::compare_ip_with_mask(unsigned int other_ip) const{
	return (other_ip >> (BUFFER_SIZE - this->mask)) == (this->address >> (BUFFER_SIZE - this->mask));
}

/**
 * @brief Matches the IP address in the provided packet with the stored IP address and mask.
 * 
 * @param packet A GenericString representing the packet containing IP information.
 * @return true if the packet's IP matches the stored IP and mask, false otherwise.
 */
bool IP::match(const GenericString &packet) const{
	if(packet.as_string().get_data()[0] == '\0'){
		return false;
	}
	String copied_packet(packet.as_string());
	copied_packet.trim();
	StringArray packet_words = copied_packet.split(",=. /");

	if(this->dir == SRC){
		unsigned int packet_src_ip = calculate_ip_address(packet_words, 1);
		return this->compare_ip_with_mask(packet_src_ip);
	}

	unsigned int packet_dst_ip = calculate_ip_address(packet_words, 6);
	return this->compare_ip_with_mask(packet_dst_ip);
}
