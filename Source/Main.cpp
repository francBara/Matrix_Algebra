#include <iostream>
#include <vector>
#include "Matrix.h"
//#include "MatList.cpp"

Matrix inputMatrix();
int numsLength(std::string);
int * getNumbers(std::string);
void copyMatrix(Matrix, Matrix);

int main()
{
	bool on = true;
	std::string menu;
	std::string matName;
	int tmpRows;
	int tmpColumns;
	std::vector<Matrix> matrixes;
	int i,j;

	std::cout << "MATRIX\n";

	i = 0;

	while (on)
	{
		std::cout << "1. | Input and save a matrix to work on\n";
		std::cout << "2. | Generate a random matrix\n";
		std::cout << "3. | Shows current saved matrixes\n";
		std::cout << "4. | Calculate the determinant of a saved matrix\n";
		std::cout << "0. | Quit\n";

		std::cin >> menu;

		if (menu == "1")
		{
			std::cout << "Insert numbers separated by spaces, press enter to add new rows and type an empty space to confirm\n";
			matrixes.push_back(inputMatrix());

			std::cout << "Insert a name for the matrix\n";
			std::cin >> matrixes.back().name;
			system("clear");
		}
		else if (menu == "2")
		{
			std::cout << "Insert matrix rows:\n";
			std::cin >> tmpRows;
			std::cout << "Insert matrix columns\n";
			std::cin >> tmpColumns;
			
			matrixes.push_back(Matrix(tmpRows, tmpColumns));

			std::cout << "Insert a name for the matrix\n";
			std::cin >> matrixes.back().name;

			matrixes.back().randomGenerate();

			system("clear");
		}
		else if (menu == "3")
		{
			std::cout << "SAVED MATRIXES\n";
			for (i = 0; i < matrixes.size(); i++)
			{
				std::cout << "---\n";
				std::cout << matrixes[i].name << "\n\n";
				matrixes[i].printMatrix();
				if (matrixes[i].calcedDet)
				{
					std::cout << "Determinant: " << matrixes[i].det << "\n";
				}
				std::cout << "---\n";
			}
			std::cout << "\n";
		}
		else if (menu == "4")
		{
			std::cout << "Insert the name of the matrix\n";
			std::cin >> matName;
			for (i = 0; i < matrixes.size(); i++)
			{
				if (matrixes[i].name == matName)
				{
					std::cout << matrixes[i].Determinant() << "\n";
					break;
				}
			}
			std::cout << "\n";
		}
		else if (menu == "0")
		{
			on = false;
			system("clear");
		}
		else
		{
			system("clear");
		}
	}
}

Matrix inputMatrix()
{
	std::vector <int *> mat;
	int * tmp = nullptr;
	int rows, cols;
	int i,j;

	std::string row;
	
	std::cin.ignore();
	std::getline(std::cin, row);

	cols = numsLength(row);

	mat.push_back(getNumbers(row));

	rows = 1;

	while (row != " ")
	{
		std::getline(std::cin, row);
		if (numsLength(row) != cols)
		{
			std::cout << "Rows must have the same length\n";
		}
		else
		{
			mat.push_back(getNumbers(row));
			rows++;
		}
	}

	Matrix nuMatrix(rows, cols);

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			nuMatrix.matrix[i][j] = mat[i][j];
		}
	}

	for (i = 0; i < rows; i++)
	{
		delete[] mat[i]; 	
	}

	return nuMatrix;
}

int * getNumbers(std::string row)
{
	int * arr = nullptr;
	bool check = true;
	int len = 0;
	int dec;
	int i,j;

	len = numsLength(row);

	arr = new int [len];
	check = true;
	dec = 1;
	j = len-1;

	for (i = row.length()-1; i >= 0; i--)
	{
		if (row[i] == ' ' && check)
		{
			dec = 1;
			j--;
			check = false;
		}
		else if (row[i] != ' ')
		{
			arr[j] = arr[j] + (row[i] - '0') * dec;
			dec = dec * 10;
			check = true;
		}
	}

	return arr;
}

int numsLength(std::string row)
{
	int check = true;
	int len = 0;
	int i;

	for (i = 0; i < row.length(); i++)
	{
		if (check && row[i] != ' ')
		{
			len++;
			check = false;
		}
		else if (row[i] == ' ')
		{
			check = true;
		}
	}

	return len;
}

void copyMatrix(Matrix mat1, Matrix mat2)
{
	int i,j;
	std::cout << "DEBUG\n";
	mat1.printMatrix();
	mat2.printMatrix();
	std::cout << "DEBUG\n";
}
