#ifndef IP_H
#define IP_H
#include "generic-field.h"
class IP: public GenericField {
	enum direction {SRC, DST} dir;
	int mask;
	unsigned int address;
	bool compare_ip_with_mask(unsigned int other_ip) const;


public:
	IP(String& rule);
	~IP(){};
	bool match(const GenericString &packet) const;
};

#endif