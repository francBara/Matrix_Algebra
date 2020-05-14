#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Matrix.h"
#include "ArrayUtils.h"

Matrix::Matrix()
{
	rows = 0;
	columns = 0;
}

Matrix::Matrix(int r, int c)
{
	int i;
	
	matrix = new int * [r];

	for (i = 0; i < r; i++)
	{
		matrix[i] = new int [c]; 	
	}

	rows = r;
	columns = c;
}

void Matrix::init(int r, int c)
{
	int i;

	matrix = new int * [r];

	for (i = 0; i < r; i++)
	{
		matrix[i] = new int [c];
	}	

	rows = r;
	columns = c;
}

void Matrix::free()
{
	int i;

	for (i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void Matrix::printMatrix()
{
	int i,j;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void Matrix::randomGenerate()
{
	int i,j;

	srand(time(NULL));

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			matrix[i][j] = rand() % 100;
		}
	}	
}

int Matrix::Determinant()
{
	if (calcedDet)
	{
		//std::cout << "Already done it!\n";
		return det;
	}
		
	int * minorQueue = new int [rows-1];
	det = calcDeterminant(0, minorQueue);
	calcedDet = true;
	delete[] minorQueue;
	return det;
}

void Matrix::getIdentity()
{
	int i,j;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			if (i == j)
			{
				matrix[i][j] = 1;
			}
			else
			{
				matrix[i][j] = 0;
			}
		}
	}
}

int Matrix::calcDeterminant(int ind, int * minorQueue)
{
	int tot = 0;
	int tmpDet;
	int tmpI, tmpJ;
	bool foundCheck = false;
	int i;

	if (rows - ind == 1)
	{
		//std::cout << "Single element\n";
		for (i = 0; i < columns; i++)
		{
			if (!isIn(minorQueue, ind, i))
			{
				//std::cout << "The determinant is " << matrix[ind][i] << std::endl;
				//std::cout << "\n";
				return matrix[ind][i];
			}
		}
	}
	else if (rows - ind == 2)
	{
		//std::cout << "Square algorithm\n";
		int * activeColumns = new int [2];
		int j;
		for (i = 0, j = 0; i < columns; i++)
		{
			if (!isIn(minorQueue, ind, i))
			{
				activeColumns[j] = i;
				j++;
			}
		}

		tot = matrix[ind][activeColumns[0]] * matrix[ind+1][activeColumns[1]];
		tot = tot - matrix[ind][activeColumns[1]] * matrix[ind+1][activeColumns[0]];
		delete[] activeColumns;
		return tot;
	}
	//Sarrus algorithm
	else if (rows - ind == 3)
	{
		//std::cout << "Sarrus algorithm\n";
		int * activeColumns = new int [3];
		int j;
		for (i = 0, j = 0; i < columns; i++)
		{
			if (!isIn(minorQueue, ind, i))
			{
				activeColumns[j] = i;
				j++;
			}	
		}

		tot = matrix[ind][activeColumns[0]] * matrix[ind+1][activeColumns[1]] * matrix[ind+2][activeColumns[2]];
		tot = tot + matrix[ind][activeColumns[1]] * matrix[ind+1][activeColumns[2]] * matrix[ind+2][activeColumns[0]];
		tot = tot + matrix[ind][activeColumns[2]] * matrix[ind+1][activeColumns[0]] * matrix[ind+2][activeColumns[1]];
		tot = tot - matrix[ind+2][activeColumns[0]] * matrix[ind+1][activeColumns[1]] * matrix[ind][activeColumns[2]];
		tot = tot - matrix[ind+2][activeColumns[1]] * matrix[ind+1][activeColumns[2]] * matrix[ind][activeColumns[0]];
		tot = tot - matrix[ind+2][activeColumns[2]] * matrix[ind+1][activeColumns[0]] * matrix[ind][activeColumns[1]];
		delete[] activeColumns;
		return tot;
	}

	tmpI = 1;
	tmpJ = 1;

	for (i = 0; i < columns; i++)
	{
		//Check if the current index is canceled
		if (!isIn(minorQueue, ind, i))
		{
			//std::cout << "Calculating the determinant of " << matrix[ind][i] << "\n";
			//std::cout << "Current row: " << ind << std::endl;
			minorQueue[ind] = i;
			//std::cout << "Canceled columns:\n";
			
			for (int j = 0; j < ind; j++)
			{
				//std::cout << minorQueue[j] << std::endl;
			}
		
			//std::cout << "\n";

			tmpDet = calcDeterminant(ind+1, minorQueue);

			//std::cout << "CURRENT IND: " << ind << std::endl;

			if ((tmpI + tmpJ) % 2 == 0)
			{
				//std::cout << "Summing current " << det << " to " << matrix[ind][i] << " multiplied per " << tmpDet << std::endl;
				tot = tot + matrix[ind][i] * tmpDet;
			}
			else
			{
				//std::cout << "Current " << det << " subtracted by " << matrix[ind][i] << " multiplied per " << tmpDet << std::endl;
				tot = tot - matrix[ind][i] * tmpDet;				
			}
			tmpJ++;
		}
	}

	//std::cout << "\n";

	return tot;
}

Matrix Matrix::Transposed()
{
	int i,j;

	Matrix transpMatrix(rows, columns);

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			transpMatrix.matrix[j][i] = matrix[i][j];
		}
	}

	return transpMatrix;
}
