CC = g++
CXXFLAGS = -O2 -std=c++11 -Werror -Wall -Wextra -pedantic
SRC = 2433.cpp
EXE = $(subst .cpp,,$(SRC))
INPUT = file_2433

.PHONY : all run compil clean

all: run clean

compil: $(EXE)

run: $(EXE)
	./$(EXE) < $(INPUT)

clean:
	rm -f $(EXE)
