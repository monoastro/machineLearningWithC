CXX		:= gcc
CXX_FLAGS 	:= -Wall -Wextra -std=c99 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lm
EXECUTABLE	:= main


run: $(BIN)/$(EXECUTABLE)
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/linearRegression.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)
