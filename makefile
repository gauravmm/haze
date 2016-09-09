CC      = g++
CXXFLAGS= -std=c++11 -Wall -Werror 
LDFLAGS = 
OFILES  = haze.o config.o

all: haze
	$(info $$CFLAGS is [${CFLAGS}])


run: haze
	./haze

# All o files depend on config.h
$(OFILES): config.h

haze: $(OFILES)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) -c $(CXXFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f haze *.o
