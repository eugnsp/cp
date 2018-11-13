CXX = g++-7.1.0
#CFLAGS = -Wall -Wextra -Wpedantic -std=c++11 -O0 -ggdb -D_DEBUG -I..
CFLAGS = -Wall -Wextra -Wpedantic -std=c++11 -O2 -DNDEBUG -I..
GEN = generate.pl

SRCS = $(wildcard src/*.cpp)
PROGS = $(patsubst %.cpp,%,$(SRCS))
OUTS = $(patsubst %.cpp,%.out,$(SRCS))

all: $(PROGS)

out: $(OUTS)

%: %.cpp
	$(CXX) $(CFLAGS) -o $@ $<

%.out: %.cpp
	$(GEN) $<

clean:
	rm -f $(PROGS)
	rm -f $(OUTS)