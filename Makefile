CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = app/temperature_controller
SOURCE = app/temperature_controller.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -f $(TARGET)

run:
	./$(TARGET)

.PHONY: all clean run

