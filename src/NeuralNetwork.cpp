#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include "NeuralNetwork.hpp"
#include "Matrix.hpp"

using namespace std;

NeuralNetwork::NeuralNetwork(int inputNodes, int hiddenNodes, int outputNodes, double learningRate) {
	this->inputNodes = inputNodes;
	this->hiddenNodes = hiddenNodes;
	this->outputNodes = outputNodes;
	this->learningRate = learningRate;
    wih.init(hiddenNodes, inputNodes);
	wih.fill();
    who.init(outputNodes, hiddenNodes);
	who.fill();
}

NeuralNetwork::~NeuralNetwork() {
}

void NeuralNetwork::train(Matrix &inputs, Matrix &targets) {
    Matrix hiddenInputs = wih * inputs;
    Matrix hiddenOutputs = sigmoid(hiddenInputs);
    Matrix finalInputs = who * hiddenOutputs;
    Matrix finalOutputs = sigmoid(finalInputs);

    Matrix outputErrors = targets - finalOutputs;
    Matrix hiddenErrors = who.transpose() * outputErrors;

    updateWho(outputErrors, finalOutputs, hiddenOutputs);
    updateWih(hiddenErrors, hiddenOutputs, inputs);
}

void NeuralNetwork::updateWho(Matrix &outputErrors, Matrix &finalOutputs, Matrix &hiddenOutputs) {
    Matrix res1 = outputErrors.dottedMultiplication(finalOutputs);
    Matrix res2 = finalOutputs * (-1.0) + 1;
    Matrix res3 = res1.dottedMultiplication(res2);
    Matrix hiddenOutputsTranspose = hiddenOutputs.transpose();
    Matrix res4 = res3 * hiddenOutputsTranspose * learningRate;
    who += res4;
}

void NeuralNetwork::updateWih(Matrix &hiddenErrors, Matrix &hiddenOutputs, Matrix &inputs) {
    Matrix res1 = hiddenErrors.dottedMultiplication(hiddenOutputs);
    Matrix res2 = hiddenOutputs * (-1.0) + 1;
    Matrix res3 = res1.dottedMultiplication(res2);
    Matrix inputsTranspose = inputs.transpose();
    Matrix res4 = res3 * inputsTranspose * learningRate;
    wih += res4;
}

Matrix NeuralNetwork::query(Matrix &inputs) {
    Matrix hiddenInputs = wih * inputs;
    Matrix hiddenOutputs = sigmoid(hiddenInputs);
    Matrix finalInputs = who * hiddenOutputs;
    return sigmoid(finalInputs);
}

Matrix NeuralNetwork::sigmoid(Matrix &matrix) {
    float e = 2.7180;
    int rows = matrix.getRows();
    int cols = matrix.getCols();
    Matrix resMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            resMatrix[i][j] = 1 / (1 + pow(e, (matrix[i][j] * -1)));
        }
    }
    return resMatrix;
}

int NeuralNetwork::runTrain(char* filename, Matrix &inputs, Matrix &targets)
{
    FILE* trainingDataFile = fopen(filename, "r");
    if (trainingDataFile == NULL) {
        return -1;
    }
    char* str;
    char* allValues;
    char buff[3000];
    int correctLabel;

    int epochs = 5;
    for (int e = 0; e < epochs; e++) {
        fseek(trainingDataFile, 0, SEEK_SET);
        while (1) {
            str = fgets(buff, 3000, trainingDataFile);
            if (str == NULL) {
                break;
            }
            allValues = strtok(str, ",");

            correctLabel = atoi(allValues);
            for (int i = 0; i < outputNodes; i++) {
                targets[i][0] = 0.01;
            }
            targets[correctLabel][0] = 0.99;

            for (int i = 0; i < inputNodes; i++) {
                allValues = strtok(NULL, ",");
                inputs[i][0] = (atoi(allValues) / 255.0 * 0.99) + 0.01;
            }
            train(inputs, targets);
        }
        
    }
    fclose(trainingDataFile);
    return 0;
}

double NeuralNetwork::testEfficiency(char* filename, Matrix &inputs) {

    FILE* trainingDataFile = fopen(filename, "r");
    if (trainingDataFile == NULL) {
        return -1.0;
    }
    char* str;
    char* allValues;
    char buff[20000];

    int correctLabel;
    int curLabel;

    Matrix finalOutputs;

    double max;
    int count = 0;
    int countLabel = 0;

    while (count != 1) {
        str = fgets(buff, 20000, trainingDataFile);
        if (str == NULL) {
            break;
        }
        allValues = strtok(str, ",");

        correctLabel = atoi(allValues);

        for (int i = 0; i < inputNodes; i++) {
            allValues = strtok(NULL, ",");
            inputs[i][0] = (atoi(allValues) / 255.0 * 0.99) + 0.01;
        }

        finalOutputs = query(inputs);

        max = finalOutputs[0][0];   
        curLabel = 0;
        for (int i = 1; i < outputNodes; i++) {
            if (max < finalOutputs[i][0]) {
                curLabel = i;
                max = finalOutputs[i][0];
            }
        }
        cout << "Correct : " << correctLabel << endl;
        cout << "Output : " << curLabel << endl;
        finalOutputs.print();
        if (curLabel == correctLabel) {
            countLabel++;
        }
        count++;
    }

    fclose(trainingDataFile);

    return ((double)countLabel / (double)count) * 100.00;
}
