#ifndef IP_H
#define IP_H
#include "generic-field.h"
enum direction {SRC, DST};
class ip: public GenericField {
	enum direction dir;
	int mask;
	unsigned int address;

	bool handle_src_ip(const StringArray packet_words) const;
	bool handle_dst_ip(const StringArray packet_words) const;

public:
	ip(String& rule);
	~ip();
	bool match(const GenericString &packet) const;
};

#endif