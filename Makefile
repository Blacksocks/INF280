CC = g++
CXXFLAGS = -O2 -std=c++11 -Werror -Wall -Wextra -pedantic
NUMBER = 6823
SRC = $(NUMBER)_CountingSubstreengs.cpp
EXE = $(subst .cpp,,$(SRC))
INPUT = file_$(NUMBER)

.PHONY : all run compil clean

all: run clean

compil: $(EXE)

run: $(EXE)
	./$(EXE) < $(INPUT)

clean:
	rm -f $(EXE)
