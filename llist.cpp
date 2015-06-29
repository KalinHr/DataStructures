#include "stdafx.h"
#include "assert.h"
#include "iostream"
using namespace std;

template <typename T = int>
struct elem_link
{
	T inf;
	elem_link<T> *link;
};

template <typename T = int>
class LList
{
public:
	LList();
	~LList();
	LList(const LList&);
	LList& operator=(const LList&);

	void iterStart(elem_link<T>* = NULL);
	elem_link<T>* iter();
	void toEnd(const T&);
	void insertAfter(elem_link<T>*, const T&);
	void insertBefore(elem_link<T>*, const T&);
	void deleteAfter(elem_link<T>*, T&);
	void deleteBefore(elem_link<T>*, T&);
	void deleteElem(elem_link<T>*, T&);
	bool empty() const;
	void print() const;
	int length() const;
private:
	elem_link<T> *start,
				 *end,
				 *current;
	void copyList(const LList&);
	void deleteList();
};

template <typename T>
LList<T>::LList()
{
	start = end = NULL;
}

template <typename T>
LList<T>::~LList()
{
	deleteList();
}

template <typename T>
LList<T>::LList(const LList<T>& r)
{
	copyList(r);
}

template <typename T>
LList<T>& LList<T>::operator=(const LList<T>& r)
{
	if (this != r)
	{
		deleteList();
		copyList(r);
	}
	return *this;
}

template <typename T>
void LList<T>::iterStart(elem_link<T>* r)
{
	if (r)
		current = r;
	else
		current = start;
}

template <typename T>
elem_link<T>* LList<T>::iter()
{
	elem_link<T> *p = current;
	if (current) current = current->link;
	return p;
}

template <typename T>
void LList<T>::toEnd(const T& r)
{
	elem_link<T>* p = end;
	end = new elem_link < T > ;
	assert(end != NULL);
	end->inf = r;
	end->link = NULL;
	if (p) p->link = end;
	else start = end;
}

template <typename T>
void LList<T>::insertAfter(elem_link<T>*p, const T& x)
{
	elem_link<T> *q = new elem_link < T > ;
	assert(q != NULL);
	q->inf = x;
	q->link = p->link;
	if (p == end) end = q;
	p->link = q;
}

template <typename T>
void LList<T>::insertBefore(elem_link<T>*p, const T& x)
{
	elem_link<T> *q = new elem_link < T > ;
	assert(q != NULL);
	*q = *p;
	if (p == end) end = q;
	p->inf = x;
	p->link = q;
}

template <typename T>
void LList<T>::deleteAfter(elem_link<T>*p, T& x)
{
	if (p->link)
	{
		elem_link<T>*r = p->link;
		x = r->inf;
		p->link = r->link;
		if (r == end) end = p;
		delete r;
	}
	else
		exit(1);
}

template <typename T>
void LList<T>::deleteElem(elem_link<T>*p, T& x)
{
	if (p == start)
	{
		x = p->inf;
		if (start = end)
		{
			start = end = NULL;
		}
		else start = start->link;
		delete p;
	}
	else
	{
		elem_link<T>* q = start;
		while (q->link != p)
			q = q->link;
		deleteAfter(q, x);
	}
}

template <typename T>
void LList<T>::deleteBefore(elem_link<T>*p, T& x)
{
	if (p != start)
	{ 
		elem_link<T>* q = start;
		while (q->link != p)
			q = q->link;
		deleteElem(q, x);
	}
	else
		exit(1)
}

template <typename T>
bool LList<T>::empty() const
{
	return start == NULL;
}

template <typename T>
void LList<T>::print() const
{
	elem_link<T>*p = start;
	while (p)
	{
		cout << p->inf << " ";
		p = p->link;
	}
	cout << endl;
}

template <typename T>
int LList<T>::length() const
{
	elem_link<T>*p = start;
	int n = 0;
	while (p)
	{
		n++;
		p = p->link;
	}
	return n;
}

template <typename T>
void LList<T>::copyList(const LList<T>& p)
{
	start = end = current = NULL;
	elem_link<T>* q = p.start;
	while (q)
	{
		toEnd(q->inf);
		q = q->link;
	}
}

template <typename T>
void LList<T>::deleteList()
{
	elem_link<T> *p;
	while (start)
	{
		p = start;
		start = start->link;
		delete p;
	}
	end = NULL;
}