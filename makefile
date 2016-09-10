CC      = g++
CXXFLAGS= -std=c++11 -Wall -Werror 
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lcurl
OFILES  = config.o hazecalc.o cmd.o tinyxml2.o filedl.o apiparser.o
MAINFILE= haze.o
TESTFILE= haze_test.o

all: haze

install: haze
	cp ./haze /usr/local/bin/

run: haze
	./haze

test: haze_test
	./haze_test

# Download the testing framework and XML parser if necessary.
$(TESTFILE): catch.hpp

catch.hpp:
	wget https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp

$(OFILES): tinyxml2.cpp tinyxml2.h

tinyxml2.cpp:
	wget https://raw.githubusercontent.com/leethomason/tinyxml2/master/tinyxml2.cpp

tinyxml2.h:
	wget https://raw.githubusercontent.com/leethomason/tinyxml2/master/tinyxml2.h

# All o files depend on config.h
$(MAINFILE): config.h
$(OFILES): config.h

# Building rules
haze: $(MAINFILE) $(OFILES)
	$(CC) -o $@ $^ $(LDFLAGS)

haze_test: $(TESTFILE) $(OFILES)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@

# Cleaning rules
.PHONY: clean

clean:
	rm -f haze test *.o
