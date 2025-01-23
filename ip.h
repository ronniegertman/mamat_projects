#ifndef IP_H
#define IP_H
#include "generic-field.h"
enum direction {SRC, DST};
class IP: public GenericField {
	enum direction dir;
	int mask;
	unsigned int address;
	bool compare_ip_with_mask(unsigned int other_ip) const;


public:
	IP(String& rule);
	~IP();
	bool match(const GenericString &packet) const;
};

#endif