CC=g++
FLAGS=-std=c++0x
TARGETS := testResultsMap

TARGETS := $(patsubst %,$(TAG)%,$(TARGETS))

all : $(TARGETS)

$(TAG)% : %.cpp ../ResultsMap.h ../AnyType.h ../ResultsMap.cpp
	$(CC) $< -o $@ $(FLAGS) ../ResultsMap.cpp

clean:
	rm -f $(TARGETS)
