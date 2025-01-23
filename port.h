#ifndef PORT_H
#define PORT_H
#include "generic-field.h"
enum direction {SRC, DST};
class Port: public GenericField{
	enum direction dir;
	int low;
	int high;
	int extract_port_from_packet(StringArray packet_words) const;
public:
	Port(String& rule);
	~Port();
	bool match(const GenericString &packet) const;
};
#endif