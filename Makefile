CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 
CCLINK = gcc
LDFLAGS = -L. -linput
RM = rm -rf 
EXEC = firewall.exe

$(EXEC):

libfirewall.so: ip.o port.o string.o 
	$(CXX) -shared -o libfirewall.so ip.o port.o string.o -L.

string-array.o: string-array.cpp string-array.h generic-string.h
	$(CXX) $(CXXFLAGS) -cpp string-array.cpp -o string-array.o

string.o: string.cpp string.h generic-string.h
	$(CXX) $(CXXFLAGS) -cpp string.cpp -o string.o

ip.o: ip.cpp ip.h generic-field.h
	$(CXX) $(CXXFLAGS) -cpp ip.cpp -o ip.o

port.o: port.cpp port.h generic-field.h
	$(CXX) $(CXXFLAGS) -cpp port.cpp -o port.o



libgrades.so: grades.o
	$(CC) -shared -o libgrades.so grades.o -L. -llinked-list

grades.o: grades.c grades.h
	$(CC) $(CFLAGS) -c grades.c
	
clean:
	$(RM) grades.o libgrades.so