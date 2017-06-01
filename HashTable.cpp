// HashTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashTable.h"

hashTable::hashTable(unsigned s)
{
	size = s;
	count = 0;
	array = new ListNode[size];
	for (int i = 0; i < size; i++) {
		array[i].freq = 0;
		array[i].next = NULL;
	}
}

hashTable::~hashTable()
{
	ListNode *head;
	ListNode *del;
	for (int i = 0; i < size; i++) {
		head = array[i].next;
		del = head;
		while (head != NULL) {
			head = head->next;
			delete del;
			del = head;
		}
	}
	delete[] array;
}

void hashTable::insert(string word)
{
	if (format(word)) {
		if (!filter(word)) {
			ListNode *position = &array[hashKey(word)];
			while (!insertElem(word, position))
				collisionFix(position);
		}
	}
	return;
}

bool hashTable::find(string word)
{
	ListNode *position = &array[hashKey(word)];
	while (!isEmpty(position) && position->data != word)
		collisionFix(position);
	return !isEmpty(position);
}

void hashTable::print()
{
	ListNode *traverse;
	for (int i = 0; i < size; i++) {
		traverse = &array[i];
		if (!isEmpty(traverse)) {
			while (traverse != NULL) {
				cout << traverse->data << " " << traverse->freq << "\n";
				traverse = traverse->next;
			}
		}
	}
}

void hashTable::outputData(ofstream& outFile, int listSize)
{
	ListNode *traverse;
	ListNode *list = new ListNode[count];
	int j = 0;
	for (int i = 0; i < size; i++) {
		traverse = &array[i];
		if (!isEmpty(traverse)) {
			while (traverse != NULL) {
				list[j] = *traverse;
				j++;
				traverse = traverse->next;
			}
		}
	}
	sort(list);
	for (int i = 0; i < listSize; i++)
		outFile << list[i].data << " " << list[i].freq << "\n";
}

int hashTable::hashKey(string word)
{
	const char ZERO = 'a';
	int num = 0;
	for (unsigned i = 0; i < word.length(); i++)
		if (word.at(i) > ZERO)
			num += (int)word.at(i) - (int)ZERO;
	num += word.length();
	num %= size;
	return num;
}

bool hashTable::insertElem(string word, ListNode* entryNode)
{
	if (isEmpty(entryNode)) {
		entryNode->data = word;
		entryNode->freq = 1;
		entryNode->next = NULL;
		count++;
		return true;
	}
	else if (entryNode->data == word) {
		entryNode->freq++;
		return true;
	}
	return false;

}

bool hashTable::isEmpty(ListNode* elem)
{
	return elem->freq == 0;
}

void hashTable::collisionFix(ListNode*& position)
{
	if (position->next != NULL)
		position = position->next;
	else {
		position->next = new ListNode;
		position = position->next;
		position->freq = 0;
	}
}

bool hashTable::format(string& word)
{
	const char Lower = 'A';
	const char Upper = 'z';
	const char MidLower= 'Z';
	const char MidUpper = 'a';
	char *tmp;

	int j = 0;
	int start = 0;
	int end = word.length() - 1;
	while (start < (int)word.length() &&
		(word.at(start) < Lower || word.at(start) > Upper ||
		(word.at(start) > MidLower && word.at(start) < MidUpper)))
		start++;
	while (end >= 0 &&
		(word.at(end) < Lower || word.at(end) > Upper ||
		(word.at(end) > MidLower && word.at(end) < MidUpper)))
		end--;

	if (start > end)
		return false;

	tmp = new char[end - start + 2];
	for (int i = start; i <= end; i++) {
		tmp[j] = tolower(word.at(i));
		j++;
	}
	tmp[end - start + 1] = '\0';
	word = tmp;
	delete[] tmp;
	tmp = NULL;
	return true;
}

bool hashTable::filter(string word)
{
	const string FilterWords = "filter.txt";
	bool check = false;
	string common;
	ifstream inFile;

	inFile.open(FilterWords.c_str());
	while (!check && inFile >> common) {
		if (word == common)
			check = true;
	}
	inFile.close();
	return check;
}

void hashTable::sort(ListNode*& list)
{
	int max;
	int replace;
	for (int i = 0; i < count; i++) {
		max = list[i].freq;
		replace = i;
		for (int j = i; j < count; j++) {
			if (list[j].freq > max) {
				max = list[j].freq;
				replace = j;
			}
		}
		swap(list[i], list[replace]);
	}
}

void hashTable::swap(ListNode& elemA, ListNode& elemB)
{
	ListNode tmp = elemA;
	elemA = elemB;
	elemB = tmp;
}
