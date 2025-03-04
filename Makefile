cc = gcc
C_FLAGS = -W -Wall -std=c89 -pedantic -O2
EXEC_FILES =

all :

clean :
	rm *.o $(EXEC_FILES)
