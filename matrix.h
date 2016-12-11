#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
class link{
    private:
	//pointer to first link
	link<T>* first;

    public:
	string name;
	T data;
	link<T>* next;
};
template <typename T>
class list {
    public:
    list();
    void additem(T d, string _name);
    void display();
};
enum MatrixType{
    Identity,
	Random
};
class matrix {
    // Private members
	private:
	int row, column; // rows and columns of the matrix
	float ** mat; // array of array of pointers for the matrix

    public:
    matrix(int _row = 2, int _column = 2);
	// Constructor makes all values initialValue
	matrix(int _row, int _column, float initialValue);
	// Constructor makes matrix with specific type
	matrix(int _row, int _column, MatrixType type);
	// Row and Column getters
	int Row();
	int Column();
	// printing the matrix
	void print();
	// Set value to number
	void set(int _row, int _column, int value);
	// Get value
	float get(int _row, int _column);
	// Add two matrices
	matrix operator + (matrix _mat);
	// Subtract two matrices
	matrix operator - (matrix _mat);
	// Compare two matrices
	bool operator == (matrix _mat);
	bool operator != (matrix _mat);
	// Multiply two matrices
	matrix operator * (matrix _mat);
	// Boolean checkers
	bool IsSquare();
	bool IsIdentity();
	bool IsIdempotent();
	bool IsSymmetric();
	bool IsUpperTriangle();
	bool IsLowerTriangle();
	// Fill the matrix with number
	void fill(float value);
	// Mul the matrix with number
	void operator * (float value);
	// Devide the matrix by number
	void operator / (float value);
	// Get max element of the matrix
	float maxElement();
	// Get min element of the matrix
	float minElement();
	// Get determinant of the matrix
	float determinant();
	// Convert matrix to string
	void toString(string* result);
};

#endif // MATRIX_H_INCLUDED
