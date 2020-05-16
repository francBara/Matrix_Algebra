#include "Matrix.h"

Matrix::Matrix()
{
	rows = 0;
	columns = 0;
}

Matrix::Matrix(int r, int c)
{
	int i;
	
	matrix = new Fract * [r];

	for (i = 0; i < r; i++)
	{
		matrix[i] = new Fract [c]; 	
	}

	rows = r;
	columns = c;
}

void Matrix::init(int r, int c)
{
	int i;

	matrix = new Fract * [r];

	for (i = 0; i < r; i++)
	{
		matrix[i] = new Fract [c];
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
			matrix[i][j].print();
			std::cout << " ";
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
			matrix[i][j].num = rand() % 100;
		}
	}	
}

Fract Matrix::Determinant()
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
				matrix[i][j].num = 1;
			}
			else
			{
				//matrix[i][j].num = 0;
			}
		}
	}
}

Fract Matrix::calcDeterminant(int ind, int * minorQueue)
{
	Fract tot(0);
	Fract tmpDet;
	int tmpI, tmpJ;
	bool foundCheck = false;
	int i;

	//When it's a single element the determinant is the element itself
	if (rows - ind == 1)
	{
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
	//Square algorithm
	else if (rows - ind == 2)
	{
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

		tot = matrix[ind][activeColumns[0]].per(matrix[ind+1][activeColumns[1]]);
		tot = tot.sub(matrix[ind][activeColumns[1]].per(matrix[ind+1][activeColumns[0]]));
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

		tot = matrix[ind][activeColumns[0]].per(matrix[ind+1][activeColumns[1]].per(matrix[ind+2][activeColumns[2]]));
		tot = tot.add(matrix[ind][activeColumns[1]].per(matrix[ind+1][activeColumns[2]].per(matrix[ind+2][activeColumns[0]])));
		tot = tot.add(matrix[ind][activeColumns[2]].per(matrix[ind+1][activeColumns[0]].per(matrix[ind+2][activeColumns[1]])));
		tot = tot.sub(matrix[ind+2][activeColumns[0]].per(matrix[ind+1][activeColumns[1]].per(matrix[ind][activeColumns[2]])));
		tot = tot.sub(matrix[ind+2][activeColumns[1]].per(matrix[ind+1][activeColumns[2]].per(matrix[ind][activeColumns[0]])));
		tot = tot.sub(matrix[ind+2][activeColumns[2]].per(matrix[ind+1][activeColumns[0]].per(matrix[ind][activeColumns[1]])));
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
		
			//std::cout << "\n";

			tmpDet = calcDeterminant(ind+1, minorQueue);

			//std::cout << "CURRENT IND: " << ind << std::endl;

			if ((tmpI + tmpJ) % 2 == 0)
			{
				//std::cout << "Summing current " << det << " to " << matrix[ind][i] << " multiplied per " << tmpDet << std::endl;
				tot = tot.add(matrix[ind][i].per(tmpDet));
			}
			else
			{
				//std::cout << "Current " << det << " subtracted by " << matrix[ind][i] << " multiplied per " << tmpDet << std::endl;
				tot = tot.sub(matrix[ind][i].per(tmpDet));				
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

	Matrix transpMatrix(columns, rows);

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			transpMatrix.matrix[j][i] = matrix[i][j];
		}
	}

	return transpMatrix;
}

Fract Matrix::Cofactor(int r, int c)
{
	Matrix tmpMatrix(rows-1, columns-1);
	Fract cof;
	int i,j,h,k;

	for (i = 0, h = 0; i < rows; i++)
	{
		if (i != r)
		{
			for (j = 0, k = 0; j < columns; j++)
			{
				if (j != c)
				{
					tmpMatrix.matrix[h][k] = matrix[i][j];
					k++;
				}	
			}
			h++;
		}
	}
	
	cof = tmpMatrix.Determinant();

	if ((r+c) % 2 != 0)
		cof.inverse();
	
	tmpMatrix.free();

	return cof;
}

Matrix Matrix::CofactorMatrix()
{
	Matrix nu_mat(rows, columns);
	int i,j;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			nu_mat.matrix[i][j] = Cofactor(i,j);
		}
	}

	return nu_mat;
}

Matrix Matrix::Inverse()
{
	Matrix adj = CofactorMatrix().Transposed();

	adj.scalarDivide(Determinant());

	return adj;	
}

void Matrix::scalarDivide(Fract s)
{
	int i,j;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			matrix[i][j] = matrix[i][j].div(s);
		}
	}
}
