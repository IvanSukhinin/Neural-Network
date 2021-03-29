.PHONY: all clean install uninstall

CC := g++
CFLAGS := -Wall -Werror
NN := ./bin/main
BUILD_DIR := ./build
INSTALL_PATH := /usr/local/bin

all: $(NN)

$(NN): $(BUILD_DIR)/main.o $(BUILD_DIR)/NeuralNetwork.o $(BUILD_DIR)/Matrix.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/NeuralNetwork.o $(BUILD_DIR)/Matrix.o -o $(NN)

$(BUILD_DIR)/main.o: src/main.cpp src/NeuralNetwork.cpp src/NeuralNetwork.hpp
	$(CC) $(CFLAGS) -c src/main.cpp -o $(BUILD_DIR)/main.o 

$(BUILD_DIR)/NeuralNetwork.o: src/NeuralNetwork.cpp src/NeuralNetwork.hpp
	$(CC) $(CFLAGS) -c src/NeuralNetwork.cpp -o $(BUILD_DIR)/NeuralNetwork.o

$(BUILD_DIR)/Matrix.o: src/Matrix.cpp src/Matrix.hpp  src/NeuralNetwork.cpp src/NeuralNetwork.hpp src/main.cpp
	$(CC) $(CFLAGS) -c src/Matrix.cpp -o $(BUILD_DIR)/Matrix.o 

clean:
	rm -rf $(BUILD_DIR)/*.o $(NN)

install: 
	install bin/main $(INSTALL_PATH)

uninstall:
	rm -rf $(INSTALL_PATH)/main
