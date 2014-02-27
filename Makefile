SOURCES = main.cpp raytracer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = raytracer

CC = g++
RM = rm -f
CCFLAGS = -Wall
LDFLAGS = -I /lib/Eigen

ifeq ($(OS), Windows_NT)
    RM = del -f
else
    UNAME_S := $(shell uname -s)
    UNAME_P := $(shell uname -p)
	
	ifeq ($(UNAME_S), Linux)
        
    endif
endif


all: $(SOURCES) $(EXECUTABLE)
build: clean $(EXECUTABLE)
clean: 
	$(RM) $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
.cpp.o:
	$(CC) $(CCFLAGS) -c $< -o $@
 


