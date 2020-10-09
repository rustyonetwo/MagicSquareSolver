// Gideon Keith-Stanley
// OCCC Fall 2020
// CS-2363 Online C++
// Magic Square Solver

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//Prototypes
void testFile(string file);
int countFile(string userFile);
int** makeMagic(string file, int length);
void showMagic(int** square, int size);
int calcMagic(int size);
bool solvePuzzle(int** puzzle, int size);
bool isCompletePuzzle(int** puzzle, int size);
bool isValidPuzzle(int** puzzle, int size);
bool testRow(int** puzzle, int row, int size);
bool testCol(int** puzzle, int col, int size);
bool testDiagonalLeft(int** puzzle, int size);
bool testDiagonalRight(int** puzzle, int size);

//Global memo declaration
bool* memo;

int main(int argc, char * argv[])
{
	//Declare variables
	string userFile = "";
	int size = 0;
	int** magicSquare;

	//Display a friendly greeting to the user
	cout << "Welcome to Magic Square Solver!" << endl << endl;

	//Prompt the user for a filename, if one wasn't an argument
	if (argc == 2)
	{
		userFile = argv[1];
	}
	else
	{
		cout << "Enter a file name: ";
		getline(cin, userFile);
		cout << endl;
	}

	//Attempt to open the file
	testFile(userFile);

	//Determine the dimensionality of the puzzle
	size = sqrt(countFile(userFile));

	//Initialize memo 
	int memoSize = (size * size) + 1;
	memo = new bool[memoSize];
	for (int b = 0; b < memoSize; b++)
	{
		memo[b] = false;
	}

	//Create a square 2d array containing the values in the file
	magicSquare = makeMagic(userFile, size);

	//Display the starting puzzle
	cout << "Starting puzzle: " << endl;
	showMagic(magicSquare, size);
	cout << endl << endl;

	//Solve the magic square using a recursive algorithm
	if (solvePuzzle(magicSquare, size) == true)
	{
		cout << "Solved puzzle: " << endl;
		showMagic(magicSquare, size);
		cout << endl << endl;
	}
	else
	{
		cout << "This puzzle cannot be solved." << endl;
	}

	//Exit
	cout << endl;
	cout << "Thank you for playing Magic Square Solver!" << endl;
	cin.get();
}

//solve a magic square
bool solvePuzzle(int** puzzle, int size)
{
	if (isCompletePuzzle(puzzle, size) == false)
	{
		//Locate the first blank space in the puzzle.
		for (int r = 0; r < size; r++)
		{
			for (int c = 0; c < size; c++)
			{												
				if (puzzle[r][c] == 0)
				{
					//In a loop over all potential candidates,
					for (int candidate = 1; candidate <= (size * size); candidate++)
					{
						//Drop in a candidate.
						if (memo[candidate] == false)
						{						
							puzzle[r][c] = candidate;
							memo[candidate] = true;

							//Make a recursive call to solvePuzzle() with the updated puzzle.
							if (solvePuzzle(puzzle, size) == true)
							{
								//Got back a true ? Return true.
								return true;
							}
							else
							{
								memo[candidate] = false;
							}
							
						}
						//Otherwise, continue the loop
					}
					//Completed the loop ? None of them worked.Reset the candidate cell to blank and return false.
					memo[puzzle[r][c]] = false;
					puzzle[r][c] = 0;
					return false;
				}
				else
				{
					memo[puzzle[r][c]] = true;
				}
			}
			//if (testRow(puzzle, r, size) == false) return false;
		}
	}
	else if (isCompletePuzzle(puzzle, size) == true)
	{
		return isValidPuzzle(puzzle, size);
	}
	else
	{
		return false;
	}
}

//test puzzle for completeness
bool isCompletePuzzle(int** puzzle, int size)
{	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (puzzle[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}

//test puzzle for validity
bool isValidPuzzle(int** puzzle, int size)
{
	//test each column, row, and diagonal to see if it adds up to the magic number	
	for (int i = 0; i < size; i++)
	{
		if (testRow(puzzle, i, size) == false || testCol(puzzle, i, size) == false || testDiagonalLeft(puzzle, size) == false || testDiagonalRight(puzzle, size) == false)
		{
			return false;
		}
	}
	return true;
}

//Test a filename to see if it can be read, if not throw an error and exit
void testFile(string file)
{
	ifstream fin;
	fin.open(file);
	if (!fin)
	{
		//Can expand this to ask for a new file name 
		cout << "ERROR opening file " << file << endl;
		cin.get();
		exit(EXIT_FAILURE);
	}
}

//Count the number of elements in a file
int countFile(string userFile)
{
    int counter = 0;
    string countHolder;

    ifstream fin;
    fin.open(userFile);

    while (!fin.eof())
    {
        fin >> countHolder;
        counter++;
    }
    return counter;
}

//Make a matrix from a file, knowing what it's dimensions are
int** makeMagic(string file, int length)
{
	ifstream fin;
	fin.open(file);
	int** result = new int* [length];
	for (int i = 0; i < length; i++)
	{
		result[i] = new int[length];

		for (int j = 0; j < length; j++)
		{
			fin >> result[i][j];
		}
	}
	return result;	
}

//display a magic square
void showMagic(int** square, int size)
{
	for (int r = 0; r < size; r++)
	{
		for (int c = 0; c < size; c++)
		{
			cout << setw(2) << square[r][c];
		}
		cout << endl;
	}
}

//Calculate the magic constant
int calcMagic(int size)
{
	//m = 1/2 n (n^2 +1)
	int m = 0;
	m = (size * size);
	m += 1;
	m *= size;
	m /= 2;
	return m;
}

#pragma region Puzzle Tests
bool testRow(int** puzzle, int row, int size)
{
	int accumulator = 0;
	int magic = calcMagic(size);
	for (int i = 0; i < size; i++)
	{
		accumulator += puzzle[row][i];
	}
	
	if (accumulator == magic)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool testCol(int** puzzle, int col, int size)
{
	int accumulator = 0;
	int magic = calcMagic(size);
	for (int i = 0; i < size; i++)
	{
		accumulator += puzzle[i][col];
	}
	if (accumulator == magic)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool testDiagonalLeft(int** puzzle, int size)
{
	int accumulator = 0;
	int magic = calcMagic(size);
	for (int i = 0; i < size; i++)
	{
		accumulator += puzzle[i][i];
	}
	if (accumulator == magic)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool testDiagonalRight(int** puzzle, int size)
{
	int accumulator = 0;
	int magic = calcMagic(size);
	for (int i = 0; i < size; i++)
	{
		//for (int j = size - 1; j > 0; j--)
		{
			accumulator += puzzle[i][size-1-i];
		}
	}
	if (accumulator == magic)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#pragma endregion
