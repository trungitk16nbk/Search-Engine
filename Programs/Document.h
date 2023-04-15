#pragma once
#include <iostream>
#include <string>
using namespace std;
struct document {
	int index;
	double cosine_Similarity;
};
struct node {
	document doc;
	node* next;
	node* prev;
};
struct List_document {
	node* h;
	node* t;
};
void AddTail(List_document& l, document& Data);
void RemoveAll(List_document& l);
void quickSort_docList(List_document& l);