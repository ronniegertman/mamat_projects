#ifndef IP_H
#define IP_H
#include "generic-field.h"

class ip: public GenericField {
	int flag; //0:src 1:dst
	int mask;
	unsigned int address;
public:
	ip(String& rule);
	~ip();
	bool match(const GenericString &packet) const;  
	bool handle_src_ip(const StringArray packet_words) const;
	bool handle_dst_ip(const StringArray packet_words) const;


};

#endif