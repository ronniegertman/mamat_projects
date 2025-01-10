#CC     = gcc
#CFLAGS = -Wall -g -std=c99 -fPIC -I.
#CCLINK = gcc
#LDFLAGS = -L. -llinked-list	
#RM = rm -rf 
#
#
##$(EXEC): $(OBJS)
##	$(CCLINK) $(CFLAGS) -o $(EXEC) $(OBJS)
#
#libgrades.so: grades.o
##	$(CCLINK) -shared grades.o -o libgrades.so
#	$(CC) -shared grades.o -o libgrades.so -L. -llinked-list
#
#grades.o: grades.c grades.h liblinked-list.so
#	$(CC) $(CFLAGS) -c grades.c -o grades.o 
#	
#clean:
#	$(RM) grades.o libgrades.so

CC     = gcc
CFLAGS = -Wall -g -std=c99 -fPIC
CCLINK = gcc
LDFLAGS = -L. -llinked-list	
RM = rm -rf 

libgrades.so: grades.o
	$(CC) -shared -o libgrades.so grades.o -L. -llinked-list

grades.o: grades.c grades.h
	$(CC) $(CFLAGS) -c grades.c
	
clean:
	$(RM) grades.o libgrades.so