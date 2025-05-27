CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -DPROGRAM_VERSION=\"tec-prog\" -D_GNU_SOURCE
LDFLAGS := $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)
INCLUDES := $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INCLUDE_DIR := include

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE := $(BIN_DIR)/main.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -I$(INCLUDE_DIR) -c $< -o $@

run: all
	./$(EXECUTABLE)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean run
