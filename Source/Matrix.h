#ifndef MATRIX_H
#define MATRIX_H

#include "Fract.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class Matrix
{	

	public:
		Fract ** matrix;
		int rows;
		int columns;
		std::string name;
		Fract det;
		bool calcedDet = false;

	public:
		Matrix();
		Matrix(int, int);
		void init(int, int);
		void free();
		void printMatrix();
		void randomGenerate();
		void getIdentity();
		Fract Determinant();
		Matrix Transposed();
		Matrix CofactorMatrix();
		Matrix Inverse();
		void scalarDivide(Fract);
		void scalarMultiply(Fract);
		Matrix addMatrix(Matrix);
		Matrix subMatrix(Matrix);
		Matrix multMatrix(Matrix);

	private:
		Fract calcDeterminant(int, int *);
		Fract Cofactor(int, int);
};

#endif
