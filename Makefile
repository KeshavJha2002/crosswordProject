# The variable CXX specifies which C++ compiler will be used.
# (because different systems may use different compilers)
CXX=g++

# The variable CXXFLAGS specifies compiler options
#   -c :    Only compile (don't link)
#   -Wall:  Enable all warnings about C++ programming
CXXFLAGS=-c -Wall -std=c++11

# All of the .hpp header files to use as dependencies
HEADERS=showf.hpp checkf.hpp updatef.hpp substring.hpp clue.hpp createArray.hpp readTF.hpp play.hpp

# All of the object files to produce as intermediary work
OBJECTS=client.o play.o readTF.o showf.o updatef.o createArray.o

# The final program to build
EXECUTABLE=crossword

# --------------------------------------------

build : $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $<
run:
	./$(EXECUTABLE)

clean:
	rm -rf *.o $(EXECUTABLE)
