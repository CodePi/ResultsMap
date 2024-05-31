FLAGS=-std=c++0x
TARGETS := testResultsMap

all : $(TARGETS)

% : %.cpp ../ResultsMap.h ../AnyType.h ../ResultsMap.cpp
	$(CXX) $< -o $@ $(FLAGS) ../ResultsMap.cpp

clean:
	rm -f $(TARGETS)
