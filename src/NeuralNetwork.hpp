#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "Matrix.hpp"

class NeuralNetwork {
private:
	int inputNodes;
	int hiddenNodes;
	int outputNodes;
	double learningRate;
    Matrix wih;
    Matrix who;
	Matrix sigmoid(Matrix &m1);
	void updateWho(Matrix &outputErrors, Matrix &finalOutputs, Matrix &hiddenOutputs);
	void updateWih(Matrix &hiddenErrors, Matrix &hiddenOutputs, Matrix &inputs);
	void train(Matrix &inputs, Matrix &targets);
	Matrix query(Matrix &inputs);

public:
	NeuralNetwork(int inputNodes, int hiddenNodes, int outputNodes, double learningRate);
	~NeuralNetwork();
	int runTrain(char* filename, Matrix &inputs, Matrix &targets);
	double testEfficiency(char* filename, Matrix &inputs);
};

#endif