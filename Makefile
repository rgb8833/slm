CXX = g++
CXXFLAGS = -Wall -std=c++17 -pedantic
TARGET = slm
SRC = src/main.cpp src/LanguageModel.cpp src/TextGenerator.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
	
.PHONY: all clean