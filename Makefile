# CONFIGURATION
PROJECT := raytracer

CC := g++
CCFLAGS := -Ilib -Wall
LDFLAGS := 

SRCFOLDER := src
OBJFOLDER := obj


# processing stuff
SRC := $(wildcard $(SRCFOLDER)/*.cpp)
OBJ := $(addprefix $(OBJFOLDER)/, $(notdir $(SRC:.cpp=.o)))

ifeq ($(OS), Windows_NT)
	RM = del /F
	DELETEOBJS = $(OBJFOLDER)\*.o
else
	RM = rm -f
	DELETEOBJS = $(OBJFOLDER)/*.o
endif






.PHONY: all clean build
all: $(PROJECT)

clean:
	$(RM) $(DELETEOBJS) $(PROJECT)
	
build: clean all


# compile targets
$(PROJECT): $(OBJ)
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS) 
$(OBJFOLDER)/%.o: $(SRCFOLDER)/%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@
