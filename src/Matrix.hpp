#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
	int rows;
	int cols;
	double **matrix;
	double dRand(double fMin, double fMax);
	void allocateMemory();
	void copyMatrix(double** const m);
	void matrixSwap(Matrix &m);

public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(const Matrix &m);
	~Matrix();
	void init(int rows, int cols);
	void fill();
	void print();
	Matrix transpose();
	Matrix& operator=(Matrix const &m);
	Matrix operator+=(Matrix &m2);
	Matrix operator*(Matrix &m2);
	Matrix operator-(Matrix &m2);
	Matrix operator+(Matrix &m2);
	Matrix operator+(double digit);
	Matrix operator*(double digit);
	double* operator[](int index);
	int getRows();
	int getCols();
	Matrix dottedMultiplication(Matrix &m2);
};

#endif