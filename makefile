CXX=gcc
CXXFLAGS=-g -std=c++11 -Wall -pedantic -lstdc++
BIN=assignment4
LDFLAGS=-L./lib/mac -lassignment4
SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
INC=-I./include
all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN) $^
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)
