#include "stdafx.h"
#include <iostream>
#include "hashTable.h"
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

const string inF = "C:\\Users\\nobodypunk\\Desktop\\C++\\HashTable\\a.txt";
const string outF = "C:\\Users\\nobodypunk\\Desktop\\C++\\HashTable\\b.txt";
const int ListSize = 10;
bool fileRead(hashTable& table)
{
	int count = 0;
	string data;
	ifstream inFile;
	inFile.open(inF.c_str());
	while (inFile >> data) {
		table.insert(data);
		count++;
	}
	inFile.close();
	return (count > 0);
}

void fileWrite(hashTable& table)
{
	ofstream outFile;
	outFile.open(outF.c_str());
	table.outputData(outFile, ListSize);
	outFile.close();
}



int main()
{
	hashTable check;
	if (fileRead(check)) {
		cout << "The data has been read from the file." << endl;
		cout << "Press <Enter>";
		cin.get();
		fileWrite(check);
		cout << "The data has been analyzed and put " << ListSize << " most common words into a file named " << outF << endl;
	}
	else
		cout << "No data was read! \n";
	return 0;
}

