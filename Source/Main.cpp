#include <iostream>
#include <vector>
#include <ctime>
#include "Fract.h"
#include "Matrix.h"

Matrix inputMatrix();
void showMatrices(std::vector<Matrix>);
int numsLength(std::string);
Fract * getNumbers(std::string);
bool searchMatrix(std::vector<Matrix>, std::string);
std::vector<Matrix> saveMatrix(Matrix, std::vector<Matrix>);

int main()
{
	bool on = true;
	std::string menu;
	std::string matName;
	Matrix tmpMatrix;
	int tmpRows;
	int tmpColumns;
	std::vector<Matrix> matrices;
	std::string tmpName;
	int tmpTime;
	int tmpNum;
	int i,j;

	system("clear");

	while (on)
	{
		std::cout << "MATRIX\n";

		std::cout << "1. | Input and save a matrix to work on\n";
		std::cout << "2. | Generate a random matrix\n";
		std::cout << "3. | Generate an identity matrix\n";
		std::cout << "4. | Shows current saved matrices\n";
		std::cout << "5. | Calculate the determinant of a saved matrix\n";
		std::cout << "6. | Calculate the transposed of a saved matrix\n";
		std::cout << "7. | Calculate the inverse of a saved matrix\n";
		std::cout << "8. | Calculate the cofactor of a saved matrix\n";
		std::cout << "9. | Multiply a saved Matrix by a scalar number\n";
		std::cout << "10. | Divide a saved matrix by a scalar number\n";
		std::cout << "11. | Sum two saved matrices\n";
		std::cout << "12. | Subract two saved matrices\n";
		std::cout << "0. | Quit\n";

		std::cin >> menu;

		if (menu == "1")
		{
			std::cout << "Insert numbers separated by spaces, press enter to add new rows and type an empty space to confirm\n";
			matrices.push_back(inputMatrix());

			std::cout << "Insert a name for the matrix:\n";
			while (true)
			{
				std::cin >> tmpName;
				if (!searchMatrix(matrices, tmpName))
					break;
				else
					std::cout << "Name already in use, please insert another one\n";
			}

			matrices.back().name = tmpName;

			system("clear");
		}
		else if (menu == "2")
		{
			std::cout << "Insert matrix rows:\n";
			std::cin >> tmpRows;
			std::cout << "Insert matrix columns:\n";
			std::cin >> tmpColumns;
			
			matrices.push_back(Matrix(tmpRows, tmpColumns));

			std::cout << "Insert a name for the matrix:\n";

			while (true)
			{
				std::cin >> tmpName;
				if (!searchMatrix(matrices, tmpName))
					break;
				else
					std::cout << "Name already in use, please insert another one\n";
			}

			matrices.back().randomGenerate();
			matrices.back().name = tmpName;

			system("clear");
		}
		else if (menu == "3")
		{
			std::cout << "Insert matrix dimension:\n";
			std::cin >> tmpRows;

			matrices.push_back(Matrix(tmpRows, tmpRows));

			std::cout << "Insert a name for the matrix:\n";
			while (true)
			{
				std::cin >> tmpName;

				if (!searchMatrix(matrices, tmpName))
				{
					break;
				}	
				else
				{
					std::cout << "Name already in use, please insert another one\n";
				}
			}

			matrices.back().getIdentity();
			matrices.back().name = tmpName;
			system("clear");
		}
		else if (menu == "4")
		{
			system("clear");
			showMatrices(matrices);
		}
		else if (menu == "5" || menu == "6" || menu == "7" || menu == "8" || menu == "9" || menu == "10" || menu == "11" || menu == "12")
		{
			system("clear");

			showMatrices(matrices);

			while (true)
			{

				std::cout << "Insert the name of the matrix, or type 'BACK'\n";
				std::cin >> matName;

				if (searchMatrix(matrices, matName))
				{
					for (i = 0; i < matrices.size(); i++)
					{
						if (matrices[i].name == matName)
							break;
					}
					if (menu == "5")
					{
						if (matrices[i].rows == matrices[i].columns)
						{
							tmpTime = time(NULL);
							std::cout << "Determinant: ";

							matrices[i].Determinant().print();
							std::cout << "\n";

							tmpTime = time(NULL) - tmpTime;
				
							if (tmpTime != 0)
							{
								std::cout << "Calculated in " << tmpTime << " seconds\n";
							}
							break;
						}
						else
						{
							std::cout << "The matrix must be a square\n";
						}
					}
					else if (menu == "6")
					{
						tmpMatrix = matrices[i].Transposed();
						std::cout << matName << " transposed:\n";
						tmpMatrix.printMatrix();
						matrices = saveMatrix(tmpMatrix, matrices);
						break;
					}
					else if (menu == "7")
					{
						if (matrices[i].rows == matrices[i].columns)
						{
							if (matrices[i].Determinant().num != 0)
							{
								tmpMatrix = matrices[i].Inverse();
								std::cout << matName << " inverse:\n";
								tmpMatrix.printMatrix();
								matrices = saveMatrix(tmpMatrix, matrices);
							}
							else
							{
								std::cout << "The determinant of the matrix must be different from 0\n";
							}
						}
						else
						{
							std::cout << "The matrix must be a square\n";
						}
						break;
					}
					else if (menu == "8")
					{
						tmpMatrix = matrices[i].CofactorMatrix();
						std::cout << matName <<" cofactor:\n";
						tmpMatrix.printMatrix();
						matrices = saveMatrix(tmpMatrix, matrices);
						break;
					}
					else if (menu == "9")
					{
						std::cout << "Type the scalar:\n";
						std::cin >> tmpNum;
						matrices[i].scalarMultiply(tmpNum);
						system("clear");
						break;
					}
					else if (menu == "10")
					{
						std::cout << "Type the scalar:\n";
						std::cin >> tmpNum; 
						matrices[i].scalarDivide(tmpNum);
						system("clear");
						break;
					}
					else if (menu == "11")
					{
						system("clear");
						showMatrices(matrices);
						std::cout << "Insert the name of the second matrix to sum:\n";
						std::cin >> matName;
						while (matName != "BACK" && !searchMatrix(matrices, matName))
						{
							std::cout << "The matrix doesn't exist, please insert another one or type 'BACK'\n";
							std::cin >> matName;
						}
						if (matName == "BACK")
							break;
						for (j = 0; j < matrices.size() && matrices[j].name != matName; j++)
							;
						matrices.push_back(matrices[i].addMatrix(matrices[j]));
						std::cout << "Insert a name for the new matrix\n";
						std::cin >> matName;

						while (searchMatrix(matrices, matName))
						{
							std::cout << "Name already in use, please insert another one\n";
							std::cin >> matName;
						}

						matrices.back().name = matName;

						system("clear");
						break;	
					}
					else if (menu == "12")
					{
						system("clear");
						showMatrices(matrices);
						std::cout << "Insert the name of the matrix to subtract:\n";
						std::cin >> matName;
						while (matName != "BACK" && !searchMatrix(matrices, matName))
						{
							std::cout << "The matrix doesn't exist, please insert another one or type 'BACK'\n";
							std::cin >> matName;
						}
						if (matName == "BACK")
							break;
						for (j = 0; j < matrices.size() && matrices[j].name != matName; j++)
							;
						matrices.push_back(matrices[i].subMatrix(matrices[j]));
						std::cout << "Insert a name for the new matrix\n";
						std::cin >> matName;

						while (searchMatrix(matrices, matName))
						{
							std::cout << "Name already in use, please insert another one\n";
							std::cin >> matName;
						}

						matrices.back().name = matName;

						system("clear");
						break;	
					}
				}
				else if (matName == "BACK")
				{
					system("clear");
					break;
				}
				else
				{
					std::cout << "This matrix doesn't exist\n\n";
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

void showMatrices(std::vector<Matrix> mats)
{
	int i,j;

	std::cout << "SAVED MATRIXES\n";
	for (i = 0; i < mats.size(); i++)
	{
		for (j = 0; j < mats[i].name.size(); j++)
			std::cout << "-";
		std::cout << "\n";
		std::cout << mats[i].name << "|\n";
		std::cout << "-----\n";
		mats[i].printMatrix();
		if (mats[i].calcedDet)
		{
			std::cout << "\nDeterminant: ";
			mats[i].det.print();
			std::cout << "\n";
		}
		std::cout << "-----\n\n";
	}
	std::cout << "\n";
}

Matrix inputMatrix()
{
	std::vector <Fract *> mat;
	int * tmp = nullptr;
	int rows, cols;
	int i,j;

	std::string row;
	
	std::cin.ignore();
	std::getline(std::cin, row);

	rows = 0;
	cols = numsLength(row);

	while (row != " ")
	{
		if (numsLength(row) != cols)
		{
			std::cout << "Rows must have the same length\n";
		}
		else
		{
			mat.push_back(getNumbers(row));
			rows++;
		}
		std::getline(std::cin, row);
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

Fract * getNumbers(std::string row)
{
	Fract * arr = nullptr;
	bool check = true;
	int len = 0;
	int dec;
	int i,j;

	len = numsLength(row);

	arr = new Fract [len];
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
		else if (row[i] == '-')
		{
			arr[j].inverse();
		}
		else
		{
			arr[j].num = arr[j].num + (row[i] - '0') * dec;
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

std::vector<Matrix> saveMatrix(Matrix mat, std::vector<Matrix> matrices)
{
	std::string choice;
	std::string matName;

	std::cout << "Do you want to save the matrix? (y/n)\n";
	while (true)
	{
		std::cin >> choice;

		if (choice == "y" || choice == "Y" || choice == "yes")
		{
			
			std::cout << "Insert a name for the matrix:\n";
			while (true)
			{
				std::cin >> matName;
				if (!searchMatrix(matrices, matName))
				{
					break;
				}
				else
				{
					std::cout << "Name already in use, please insert another one\n";
				}
			}
			mat.name = matName;
			matrices.push_back(mat);
			system("clear");
			break;
		}
		else if (choice == "n" || choice == "N" || choice == "no")
		{
			mat.free();
			system("clear");
			break;
		}
		else
		{
			std::cout << "Please insert a valid command\n";
		}
	}
	return matrices;
}

bool searchMatrix(std::vector<Matrix> mats, std::string matName)
{
	int i;

	for (i = 0; i < mats.size(); i++)
	{
		if (mats[i].name == matName)
		{
			return true;
		}
	}

	return false;
}
