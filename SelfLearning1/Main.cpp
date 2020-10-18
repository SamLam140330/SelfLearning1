#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string>

using namespace std;

#define N 20

// search for a word in the input file, return true if found
bool lookup(const char filename[], const char word[])
{
	string fileData;
	ifstream readFile;
	readFile.open(filename);
	while (getline(readFile, fileData))
	{
		if (word == fileData)
		{
			readFile.close();
			return true;
		}
	}
	readFile.close();
	return false;
}

// delete a word in the input file
// the result should not contain blank lines
void delete_word(const char filename[], const char word[])
{
	string fileData;
	bool wordExist = false;
	int renameResult;
	ifstream readFile;
	readFile.open(filename);
	while (getline(readFile, fileData))
	{
		if (word != fileData)
		{
			ofstream creatFile;
			creatFile.open("temp.txt", ofstream::app);
			creatFile << fileData << endl;
			creatFile.close();
		}
		else
		{
			wordExist = true;
		}
	}
	readFile.close();
	remove(filename);
	renameResult = rename("temp.txt", filename);
	if (renameResult == 1)
	{
		cout << "Something went wrong!" << endl;
		exit(1);
	}
	if (wordExist == true)
	{
		cout << "The word successfully deleted!" << endl;
	}
	else
	{
		cout << "The word does not exist!" << endl;
		cout << "No data is deleted!" << endl;
	}
}

// insert a word in the input file such that the words are in ascending order
// it should not insert duplicate word
void insert_word(const char filename[], const char word[])
{
	string fileData;
	bool wordExist = false;
	ifstream readFile;
	readFile.open(filename);
	while (getline(readFile, fileData))
	{
		if (word == fileData)
		{
			wordExist = true;
		}
	}
	readFile.close();
	if (wordExist == true)
	{
		cout << "The word already exist!" << endl;
		cout << "No data is added!" << endl;
	}
	else
	{
		cout << "The word successfully added!" << endl;
		ofstream writeFile;
		writeFile.open(filename, ifstream::app);
		writeFile << word << endl;
		writeFile.close();
	}
}

int main(int argc, char** argv)
{
	const char filename[] = "words.txt";
	char choice;
	char word[N];
	bool checkFile = true;

	while (true)
	{
		if (checkFile == true)
		{
			ifstream readFile;
			readFile.open(filename);
			if (readFile.is_open())
			{
				cout << "File exist, great" << endl;
			}
			else
			{
				cout << "File does not exist" << endl;
				cout << "Creating one..." << endl;
				ofstream creatFile;
				creatFile.open(filename);
				creatFile.close();
			}
			readFile.close();
			checkFile = false;
		}

		cout << "1 for lookup; 2 for insertion; 3 for deletion; q for quit: ";
		cin >> choice;

		if (choice == '1')
		{
			cout << "Please enter the word you want to search for: ";
			cin >> word;
			if (lookup(filename, word))
			{
				cout << "The word \"" << word << "\" is found!" << endl;
			}
			else
			{
				cout << "The word \"" << word << "\" is not found!" << endl;
			}
		}
		else if (choice == '2')
		{
			cout << "Please enter the word you want to insert: ";
			cin >> word;
			insert_word(filename, word);
		}
		else if (choice == '3')
		{
			cout << "Please enter the word you want to delete: ";
			cin >> word;
			delete_word(filename, word);
		}
		else if (choice == 'q')
		{
			break;
		}
		else
		{
			cout << "Invalid input. Please input again." << endl;
		}
		cout << endl;
	}
	return(0);
}
