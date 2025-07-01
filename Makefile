CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRCS = Graph.cpp Algorithms.cpp
OBJS = $(SRCS:.cpp=.o)

MAIN = main
TEST = test

all: $(MAIN)

$(MAIN): $(OBJS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST): $(OBJS) test.o
	$(CXX) $(CXXFLAGS) -o $@ $^

valgrindTest: $(TEST)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST)

valgrindMain: $(MAIN)
	valgrind --leak-check=full --show-leak-kinds=all ./$(MAIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(MAIN) $(TEST)
