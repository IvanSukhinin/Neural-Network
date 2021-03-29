#include <iostream>
#include "NeuralNetwork.hpp"
#include "Matrix.hpp"

using namespace std;

int main() {
	int inputNodes = 784;
	int hiddenNodes = 88;
	int outputNodes = 10; 
	double learningRate = 0.3;
	NeuralNetwork n(inputNodes, hiddenNodes, outputNodes, learningRate);

	Matrix inputs(inputNodes, 1);
    Matrix targets(outputNodes, 1);
    char trainFile[100] = "./csv/mnist_train_100.csv\0";
	int fileFound = n.runTrain(trainFile, inputs, targets);
	if (fileFound == -1) {
		cout << "Error opening file" << endl;
		return 1;
	}
	char testFile[100] = "./csv/mnist_test_10.csv\0";
	double efficiency = n.testEfficiency(testFile, inputs);
	if (efficiency == -1.0) {
		cout << "Error opening file" << endl;
		return 1;
	}
	cout << "Efficiency: " << efficiency << "%" << endl;

	return 0;
}
