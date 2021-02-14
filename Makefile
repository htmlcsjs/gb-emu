CXXFLAGS = -Wall -g -static -o2 -std=c++17
LDFLAGS = 

all: main

main: ram.o logging.o cpu.o
	$(CXX) $(CXXFLAGS) -o $@.out $@.cpp $^ $(LDFLAGS)

test:
	$(CXX) $(CXXFLAGS) -o $@.out $@.cpp $^ $(LDFLAGS)

install:
	cp main.out /usr/local/bin/gb-emu

ram.o: ram.cpp
logging.o: logging.cpp
cpu.o: cpu.cpp

clean:
	$(RM) main.out
	$(RM) ram.o
	$(RM) logging.o
	$(RM) cpu.o
	$(RM) test.out
