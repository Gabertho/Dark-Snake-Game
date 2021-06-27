CXX		  := g++
CXX_FLAGS := -Wall -Wextra -Wno-unused-parameter -std=c++17 -ggdb

SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system 
EXECUTABLE	:= main

MKDIR_P = mkdir -p

.PHONY: directories

all: directories $(BIN)/$(EXECUTABLE)

directories: ${BIN}

${BIN}:
	${MKDIR_P} ${BIN}

run: clean all
	clear
	.$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*


