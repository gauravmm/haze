CC      = g++
CXXFLAGS= -std=c++11 -Wall -Werror 
LDFLAGS = 
OFILES  = config.o hazecalc.o cmd.o
MAINFILE= haze.o
TESTFILE= haze_test.o

all: haze

run: haze
	./haze

test: haze_test
	./haze_test

# Download the testing framework if necessary.
$(TESTFILE): catch.hpp

catch.hpp:
	wget https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp

# All o files depend on config.h
$(MAINFILE): config.h
$(OFILES): config.h

# Building rules
haze: $(MAINFILE) $(OFILES)
	$(CC) -o $@ $^ $(LDFLAGS)

haze_test: $(TESTFILE) $(OFILES)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) -c $(CXXFLAGS) $< -o $@

# Cleaning rules
.PHONY: clean

clean:
	rm -f haze test *.o
