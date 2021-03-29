#include <iostream>
#include "Matrix.hpp"

using namespace std;

Matrix::Matrix() {
	matrix = nullptr;
}

Matrix::Matrix(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	allocateMemory();
}

Matrix::Matrix(const Matrix &m) {
	this->rows = m.rows;
	this->cols = m.cols;
	allocateMemory();
	copyMatrix(m.matrix);
}

Matrix::~Matrix() {
    for (int i = 0; i < rows && matrix != nullptr; i++) {
    	delete [] matrix[i];
    }
    delete [] matrix;
}

void Matrix::init(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	allocateMemory();
}

void Matrix::allocateMemory() {
    matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
    	matrix[i] = new double[cols];
    }
}

void Matrix::copyMatrix(double** const m) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = m[i][j];
		}
	}
}

void Matrix::fill() {
	srand(time(NULL));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = dRand(0.1, 0.99);
		}
	}
}

double Matrix::dRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin) - 0.5;
}

void Matrix::print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << i << ") " << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

Matrix Matrix::transpose() {
	Matrix m(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[j][i] = matrix[i][j];
        }
    }

    return m;
}

void Matrix::matrixSwap(Matrix &m) {
	swap(rows, m.rows);
	swap(cols, m.cols);
	swap(matrix, m.matrix);
}

Matrix& Matrix::operator=(Matrix const &m) {
	if (this == &m) {
    	return *this;
    }
	Matrix(m).matrixSwap(*this);
	return *this;
} 

Matrix Matrix::operator*(Matrix &matrix2) {
	int cols2 = matrix2.getCols();
    Matrix resMatrix(rows, cols2);

    double temp = 0.0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols; k++) {
                temp += matrix[i][k] * matrix2[k][j];
            }
            resMatrix[i][j] = temp;
            temp = 0.0;
        }
    }

    return resMatrix;
}

Matrix Matrix::operator*(double digit) {
    Matrix resMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        	resMatrix[i][j] = matrix[i][j] * digit;
        }
    }

    return resMatrix;
}

Matrix Matrix::operator-(Matrix &matrix2) {
    Matrix resMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        	resMatrix[i][j] = matrix[i][j] - matrix2[i][j];
        }
    }

    return resMatrix;
}

Matrix Matrix::operator+(Matrix &matrix2) {
    Matrix resMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        	resMatrix[i][j] = matrix[i][j] + matrix2[i][j];
        }
    }

    return resMatrix;
}

Matrix Matrix::operator+(double digit) {
    Matrix resMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        	resMatrix[i][j] = matrix[i][j] + digit;
        }
    }

    return resMatrix;
}

Matrix Matrix::operator+=(Matrix &matrix2) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        	matrix[i][j] = matrix[i][j] + matrix2[i][j];
        }
    }

    return *this;
}

double* Matrix::operator[](int index) {
    return matrix[index];
}

int Matrix::getRows() {
	return rows;
}

int Matrix::getCols() {
	return cols;
}

Matrix Matrix::dottedMultiplication(Matrix &matrix2) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        	matrix[i][j] = matrix[i][j] * matrix2[i][j];
        }
    }

    return *this;
}
