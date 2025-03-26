CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

TARGET = ising_model
SRCS = main.cpp IsingModel1D.cpp IsingModel2d.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean