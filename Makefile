CXXFLAGS = -Wall -g -static -o2 -std=c++17
LDFLAGS = 

all: main

main: ram.o logging.o
	$(CXX) $(CXXFLAGS) -o $@.out $@.cpp $^ $(LDFLAGS)

ram.o: logging.o ram.cpp
logging.o: logging.cpp

test:
	$(CXX) $(CXXFLAGS) -o $@.out $@.cpp $^ $(LDFLAGS)

install:
	cp main.out /usr/local/bin/gb-emu

clean:
	$(RM) main.out
	$(RM) ram.o
	$(RM) logging.o
	$(RM) test.out
