CC     = gcc
CFLAGS = -Wall -g -std=c99
CCLINK = gcc
OBJS   = main.o student.o stack.o
EXEC = prog.exe
RM = rm -rf 


$(EXEC): $(OBJS)
	$(CCLINK) $(CFLAGS) -o $(EXEC) $(OBJS)

#main: $(OBJS)
#	$(CCLINK) $(CFLAGS) -o main $(OBJS)

main.o: main.c common.h student.h stack.h
	$(CC) $(CFLAGS) -c main.c -o main.o

stack.o: stack.c stack.h common.h
	$(CC) $(CFLAGS) -c stack.c -o stack.o

student.o: student.c student.h common.h
	$(CC) $(CFLAGS) -c student.c -o student.o
	
clean:
	$(RM) $(EXEC) $(OBJS)