#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "matrix.h"

using namespace std;

const int MAXSIZE = 100;
const int MAXMATRICIES = 20;

template <typename T>
list<T>::list() {
	//no first link
	this->first = NULL;
}
template <typename T>
void list<T>::additem(T d, string _name) {
	link<T>* newlink = new link<T>;
	newlink -> data = d;
	newlink -> name = _name;
	newlink -> next = this->first;
	this->first = newlink;
}

template <typename T>
void list<T>::display() {
	link<T>* current = this->first;
	while( current != NULL ) {
		cout << current -> name << " =\n";
		current -> data.print();
		current = current -> next;
	}
}
//**************************************************************//

matrix::matrix(int _row, int _column) {
	row = _row;
	column = _column;
	mat = new float* [row];
	for (int i=0; i<row; i++) {
		mat[i] = new float[column];
	}
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			*(*(mat + i) + j) = 0.0;
		}
	}
}

matrix::matrix(int _row, int _column, float initalValue) {
	row = _row;
	column = _column;
	mat = new float* [row];
	for (int i=0; i<row; i++) {
		mat[i] = new float[column];
	}
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			*(*(mat + i) + j) = initalValue;
		}
	}
}

matrix::matrix(int _row, int _column, MatrixType type) {
	row = _row;
	column = _column;
	mat = new float* [row];
	for (int i=0; i<row; i++) {
		mat[i] = new float[column];
	}
	switch(type) {
		case Identity :
			for (int i=0; i<row; i++) {
				for (int j=0; j<column; j++) {
					if(i == j) {
						*(*(mat + i) + j) = 1.0;
					} else {
						*(*(mat + i) + j) = 0.0;
					}
				}
			}
		break;
		case Random :
			for (int i=0; i<row; i++) {
				for (int j=0; j<column; j++) {
					srand(rand());
					*(*(mat + i) + j) = rand()%10;
				}
			}
		break;
	}
}

int matrix::Row() {
	return row;
}

int matrix::Column() {
	return column;
}

void matrix::print() {
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			cout << setw(8) << *(*(mat + i) + j);
		}
		cout << endl;
	}
}

void matrix::set(int _row, int _column, int value) {
	*(*(mat + _row) + _column) = value;
}

float matrix::get(int _row, int _column) {
	return *(*(mat + _row) + _column);
}

matrix matrix::operator + (matrix _mat) {
	matrix result(this -> row, this -> column);
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			result.set(i, j, this -> get(i, j) + _mat.get(i, j));
		}
	}
	return result;
}

matrix matrix::operator - (matrix _mat) {
	matrix result(this -> row, this -> column);
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			result.set(i, j, this -> get(i, j) - _mat.get(i, j));
		}
	}
	return result;
}

bool matrix::operator == (matrix _mat) {
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			if(this -> get(i, j) != _mat.get(i, j))
				return false;
		}
	}
	return true;
}

bool matrix::operator != (matrix _mat) {
	return !(*this == _mat);
}

matrix matrix::operator * (matrix _mat) {
	matrix result(this -> Row(), _mat.Column());
	for (int i=0; i<result.Row(); i++) {
		for (int j=0; j<result.Column(); j++) {
			for (int s=0; s<column; s++) {
				result.set(i, j, result.get(i, j) + ((this -> get(i, s)) * _mat.get(s, j)));
			}
		}
	}
	return result;
}

bool matrix::IsSquare() {
	if(row == column)
		return true;
	return false;
}

bool matrix::IsIdentity() {
	if (!IsSquare()) return false;
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			if(i == j) {
				if(*(*(mat + i) + j) != 1) return false;
			} else {
				if(*(*(mat + i) + j) != 0) return false;
			}
		}
	}
	return true;
}

bool matrix::IsIdempotent() {
	if(!IsSquare()) return false;
	if ((*this) == ((*this) * (*this))) return true;
	return false;
}

bool matrix::IsSymmetric() {
	if(!IsSquare()) return false;
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			if(get(i, j) != get(j, i)) return false;
		}
	}
	return true;
}

bool matrix::IsUpperTriangle() {
	if(!IsSquare()) return false;
	for (int i=1; i<row; i++) {
		for (int j=0; j<i; j++) {
			 if(get(i, j) != 0) return false;
		}
	}
	return true;
}

bool matrix::IsLowerTriangle() {
	if(!IsSquare()) return false;
	for (int i=0; i<row-1; i++) {
		for (int j=i+1; j<column; j++) {
			 if(get(i, j) != 0) return false;
		}
	}
	return true;
}

void matrix::fill(float value) {
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			*(*(mat + i) + j) = value;
		}
	}
}

void matrix::operator * (float value) {
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			*(*(mat + i) + j) = get(i, j) * value;
		}
	}
}

void matrix::operator / (float value) {
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			*(*(mat + i) + j) = get(i, j) / value;
		}
	}
}

float matrix::maxElement() {
	int max = get(0,0);
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			if(get(i, j) > max) max = get(i, j);
		}
	}
	return max;
}

float matrix::minElement() {
	int min = get(0,0);
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			if(get(i, j) < min) min = get(i, j);
		}
	}
	return min;
}

float matrix::determinant() {
	if(!IsSquare()) return 0;
	float result = 0;
	if(row == 2) return get(0,0) * get(1,1) - get(1,0) * get(0,1);
	else {
		for (int s=0; s< this -> Column(); s++) {
			matrix m((this -> Row()) -1, (this -> Column()) -1);
			for(int i=0; i<m.Row(); i++) {
				for (int j=0; j<m.Column(); j++) {
					if(j >= s) {
						m.set(i, j, this -> get(i+1, j+1));
					} else m.set(i, j, this -> get(i+1, j));
				}
			}
			result += (this -> get(0, s)) *  pow(-1, s) * m.determinant();
		}
	}
	return result;
}

void matrix::toString(string* result) {
	stringstream ss;
	for (int i=0; i<row; i++) {
		for (int j=0; j<column; j++) {
			 ss << get(i, j) << '|';
		}
		ss << '\n';
	}
	*result = ss.str();
}



