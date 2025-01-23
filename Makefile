CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -fPIC
CCXLINK = g++
RM = rm -rf 
EXEC = firewall.exe

all: $(EXEC)

$(EXEC): main.o libfirewall.so libinput.so
	$(CCXLINK) $(CXXFLAGS) main.o -L. -lfirewall -linput

main.o: main.cpp ip.h port.h string.h 
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

libfirewall.so: ip.o port.o string.o string-array.o
	$(CCXLINK) -shared -o libfirewall.so ip.o port.o string.o string-array.o

string-array.o: string-array.cpp string-array.h generic-string.h
	#need to recompile String?
	$(CXX) $(CXXFLAGS) -c string-array.cpp -o string-array.o

string.o: string.cpp string.h generic-string.h string-array.h
	$(CXX) $(CXXFLAGS) -c string.cpp -o string.o

ip.o: ip.cpp ip.h generic-field.h string.h
	$(CXX) $(CXXFLAGS) -c ip.cpp -o ip.o

port.o: port.cpp port.h generic-field.h string.h
	$(CXX) $(CXXFLAGS) -c port.cpp -o port.o
	
clean:
	$(RM) *.o libfirewall.so $(EXEC)