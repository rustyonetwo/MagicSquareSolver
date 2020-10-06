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
int** solvePuzzle(int** puzzle);
bool isCompletePuzzle(int** puzzle);
bool isValidPuzzle(int** puzzle);

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

	//Create a square 2d array containing the values in the file
	magicSquare = makeMagic(userFile, size);

	//Display the starting puzzle
	showMagic(magicSquare, size);

	//Solve the magic square using a recursive algorithm

	//Display the solved puzzle, or a message if no solution is possible
	showMagic(magicSquare, size);

	//Exit
	cout << endl;
	cout << "Thank you for playing Magic Square Solver!" << endl;
	cin.get();
}

//solve a magic square
int** solvePuzzle(int** puzzle)
{
	
	//Locate the first blank space in the puzzle.
		//In a loop over all potential candidates,
		//Drop in a candidate.
		//Make a recursive call to solvePuzzle() with the updated puzzle.
		//Got back a true ? Return true.
		//Otherwise, continue the loop(try the next candidate and make another recursive call)
		//Completed the loop ? None of them worked.Reset the candidate cell to blank and return false.

}

//test puzzle for completeness
bool isCompletePuzzle(int** puzzle, int size)
{
	bool result = true;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (puzzle[i][j] == 0)
			{
				result = false;
			}
		}
	}
	return result;
}

//test puzzle for validity
bool isValidPuzzle(int** puzzle)
{
	//declare local variables
	int size = 0;
	int magicConstant = 0;
	int acc = 0;

	//get size from length of first row
	size = sizeof(puzzle[0]);

	//get magic constant
	magicConstant = calcMagic(size);

	//test each column, row, and diagonal to see if it adds up to the magic number
	
	//columns
	for (int col = 0; col < size; col++)
	{
		acc = 0;
		for (int row = 0; row < size; row++)
		{
			acc += puzzle[row][col];
		}
		if (acc > magicConstant) return false;		
	}

	//rows
	for (int row = 0; row < size; row++)
	{
		acc = 0;
		for (int col = 0; col < size; col++)
		{
			acc += puzzle[row][col];
		}		
		if (acc > magicConstant) return false;
	}	

	//left diagonal
	acc = 0;
	for (int i = 0; i < size; i++)
	{
		acc += puzzle[i][i];
	}
	if (acc > magicConstant) return false;

	//right diagonal
	acc = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j > 0; j--)
		{
			acc += puzzle[i][j];
		}
	}
	if (acc > magicConstant) return false;

	//otherwise
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
	return ((size / 2) * ((size * size) + 1));
}

