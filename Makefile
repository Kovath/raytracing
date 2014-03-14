# CONFIGURATION
PROJECT := raytracer
TESTBUILD := rtester 

CC := g++
CCFLAGS := -Ilib -Wall -O3
LDFLAGS := 

SRCFOLDER := src
OBJFOLDER := obj
TESTFOLDER := test

# processing stuff
SRC := $(wildcard $(SRCFOLDER)/*.cpp)
OBJ := $(addprefix $(OBJFOLDER)/, $(notdir $(SRC:.cpp=.o)))
TEST := $(wildcard $(TESTFOLDER)/*.cpp)
TESTOBJ := $(filter-out obj/main.o, $(OBJ)) $(addprefix $(TESTFOLDER)/, $(notdir $(TEST:.cpp=.o)))

ifeq ($(OS), Windows_NT)
	RM = del /F
	DELETEOBJS = $(OBJFOLDER)\*.o $(TESTFOLDER)\*.o
else
	RM = rm -f
	DELETEOBJS = $(OBJFOLDER)/*.o $(TESTFOLDER)/*.o
endif

.PHONY: all clean build
all: $(PROJECT)

clean:
	$(RM) $(DELETEOBJS) $(PROJECT) $(TESTBUILD)
	
build: clean all
	
test: $(TESTBUILD)
	
# compile test build
$(TESTBUILD): $(TESTOBJ)
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS) 
$(TESTFOLDER)/%.o: $(TESTFOLDER)/%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@
	
# compile targets
$(PROJECT): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)
$(OBJFOLDER)/%.o: $(SRCFOLDER)/%.cpp
	$(CC) $(CCFLAGS) -o $@ -c $< $(LDFLAGS)
