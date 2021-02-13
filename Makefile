CXXFLAGS = -Wall -g -static -o2 -std=c++17
LDFLAGS = 

all: main

main: ram.o
	$(CXX) $(CXXFLAGS) -o $@.out $@.cpp $^ $(LDFLAGS)

ram.o: ram.cpp

test:
	$(CXX) $(CXXFLAGS) -o $@.out $@.cpp $^ $(LDFLAGS)

install:
	cp main.out /usr/local/bin/gb-emu

clean:
	$(RM) main.out
	$(RM) ram.o
	$(RM) test.out
