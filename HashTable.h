#pragma once
using namespace std;
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

class hashTable
{
public:
	hashTable(unsigned s = 650);
	~hashTable();
	void insert(string word);
	bool find(string word);
	void print();
	void outputData(ofstream& outFile, int listSize);
private:
	struct ListNode
	{
		string data;
		int freq;
		ListNode *next;
	};
	hashTable(const hashTable& h);
	int hashKey(string word);
	bool insertElem(string word, ListNode* entryNode);
	bool isEmpty(ListNode* elem);
	void collisionFix(ListNode*& position);
	bool format(string& word);
	bool filter(string word);
	void sort(ListNode*& list);
	void swap(ListNode& elemA, ListNode& elemB);
	ListNode *array;
	int size; 
	int count;
};
