CXX = clang++
CXXFLAGS = -std=c++17 -Wall -g -fopenmp
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -fopenmp

SRCS = main.cpp Grid.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
