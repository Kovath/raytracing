# CONFIGURATION
PROJECT := raytracer

CC := g++
CCFLAGS := -Ilib -Wall
LDFLAGS := 

SRCFOLDER := src
OBJFOLDER := obj






# processing stuff
#SRC := $(wildcard $(SRCFOLDER)/*.cpp)
SRC := src/main.cpp src/raytracer.cpp
OBJ := $(addprefix $(OBJFOLDER)/, $(notdir $(SRC:.cpp=.o)))


.PHONY: all clean build
all: $(PROJECT)

clean:
ifeq ($(OS), Windows_NT)
	del /F $(OBJFOLDER)\*.o $(PROJECT)
else
	$(RM) $(OBJFOLDER)/*.o $(PROJECT)
endif
	
build: clean all
	
	

	
	
# compile targets
$(PROJECT): $(OBJ)
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS) 
$(OBJFOLDER)/%.o: $(SRCFOLDER)/%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@
