#include "Document.h"
bool checkEmpty(List_document l) {
	return (!l.h || !l.t) ? 1 : 0;
}
node* FindI(List_document& l, int index) {
	if (index < 0) return NULL;
	if (checkEmpty(l)) return NULL;


	for (node* i = l.h; i; i = i->next) {
		if (index == 0) return i;
		index--;
	}
	return NULL;
}
int sizeOfList(List_document& l) {
	node* t;
	int res = 0;
	for (t = l.h; t; t = t->next)
		res++;
	return res;
}
node* Data_to_Node(document Data) {
	node* tmp = new node[1];
	tmp->doc.cosine_Similarity = Data.cosine_Similarity;
	tmp->doc.index = Data.index;
	tmp->next = NULL;
	tmp->prev = NULL;
	return tmp;
}
void AddHead(List_document& l, document& Data) {

	node* n = Data_to_Node(Data);
	if (checkEmpty(l)) {
		l.h = n;
		l.t = n;
		return;
	}

	node* lastHead = l.h;
	n->next = l.h;
	l.h = n;
	lastHead->prev = n;
}
void AddTail(List_document& l, document& Data) {
	if (checkEmpty(l)) { AddHead(l, Data); return; }
	node* n = Data_to_Node(Data);
	node* lastTail = l.t;
	lastTail->next = n;
	n->prev = lastTail;
	l.t = n;
}
void AddAfterI(List_document& l, document Data, int index) {
	if (index < 0) return;
	if (checkEmpty(l)) { AddHead(l, Data); return; }
	node* n = Data_to_Node(Data);
	node* prev_i = FindI(l, index - 1);
	if (!prev_i) return;
	if (!prev_i->next) {
		AddTail(l, Data); return;
	}
	node* node_i = prev_i->next;

	prev_i->next = n;
	node_i->prev = n;

	n->next = node_i;
	n->prev = prev_i;
}

void RemoveHead(List_document& l) {
	if (checkEmpty(l)) return;
	if (l.h->next == NULL) {
		delete l.h;
		l.h = NULL; l.t = NULL;
		return;
	}
	node* pDel = l.h;
	pDel->next->prev = NULL;
	l.h = l.h->next;
	delete pDel;
	pDel = NULL;
}
void RemoveAll(List_document& l) {
	if (checkEmpty(l)) return;
	while (l.h != NULL) RemoveHead(l);
}

// Quick Sort...
void swap_forList(document& d1, document& d2) {
	document tmp;
	tmp = d1;
	d1 = d2;
	d2 = tmp;
}
node* partition(node* h, node* t)
{
	document d = t->doc;
	node* i = h->prev;
	for (node* j = h; j != t; j = j->next)
	{
		if (j->doc.cosine_Similarity >= d.cosine_Similarity)
		{
			i = (i == NULL) ? h : i->next;
			swap(i->doc,j->doc);
		}
	}
	i = (i == NULL) ? h : i->next; 
	swap(i->doc, t->doc);
	return i;
}

void quickSort(node* h,node* t)
{
	if (t != nullptr && h != t && h != t->next)
	{

		node* pi = partition(h,t);
		quickSort(h, pi->prev);
		quickSort(pi->next, t);
		pi = nullptr;
	}
}
void quickSort_docList(List_document& l){
	if (checkEmpty(l)) return;
	quickSort(l.h,l.t);

}