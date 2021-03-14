CXXFLAGS = -Wall -g -static -std=c++17
LDFLAGS = 
VPATH = src

all: gb-emu.out

logging.o: logging.cpp

cpu.o: cpu.cpp 

opcodes.o: opcodes.cpp

ram.o: ram.cpp 

utils.o: utils.cpp

gb-emu.out: main.cpp logging.o opcodes.o cpu.o ram.o utils.o
	$(CXX) $(CXXFLAGS) -o gb-emu.out $^ $(LDFLAGS)

install: main.cpp
	cp gb-emu.out /usr/local/bin/gb-emu

clean:
	$(RM) main.out
	$(RM) logging.o
	$(RM) cpu.o
	$(RM) opcodes.o
	$(RM) ram.o
	$(RM) utils.o
