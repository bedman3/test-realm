CC = g++
CFLAGS = -g
CLINK = -lpthread

CC_FILE := $(wildcard *.cc) 
CPP_FILE := $(wildcard *.cpp)
CODE_FILE := $(CC_FILE)$(CPP_FILE)
OBJ_FILE := $(wildcard *.o)

print-%:
	@echo '$*=$($*)'

all: test

$(OBJ): %.o: $(CODE_FILE)

test: $(OBJ_FILE)
	$(CC) $(CFLAGS) -o test $(OBJ_FILE) $(CLINK) 
	
clean:
	rm -f *.o
	rm -f test


