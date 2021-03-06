/*
��������� ������ �� �������� �����.
�������� ���������.
���������� �� ������ ���������:
http://informatics.mccme.ru/mod/statements/view3.php?chapterid=111240#1
*/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;


struct Point {
	double x, y;
	Point(double x = 0, double y = 0) {
		this->x = x;
		this->y = y;
	}
};

double Distance(Point* a, Point* b) {
	return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

int CompareDouble(double a, double b) {
	/*
		a > b => 1
		a == b => 0
		a < b => -1
	*/
	int EPS = 0.00000001;
	if (a >= b - EPS && a <= b + EPS)
		return 0;
	if (a > b)
		return 1;
	return 1;
}

struct Node {
	int y, value, size;
	double dist;
	Point* p;
	// ����� ����� ������� � ���������
	Point* leftel;
	// ����� ������ ������� � ���������
	Point* rightel;
	bool toreverse;
	Node* left;
	Node* right;
	Node(int x, Point* p) {
		this->dist = 0;
		this->leftel = this->rightel = this->p = p;
		this->y = ((rand() << 15) | rand());
		this->value = x;
		this->size = 1;
		this->left = NULL;
		this->right = NULL;
		//this->min = x;
		this->toreverse = false;
	}
};

typedef pair < Node*, Node* > tpair;

int size(Node* t) { return (t == NULL ? 0 : t->size); }
double dist(Node* t) { return (t == NULL ? 0 : t->dist); }
void torev(Node* t) { 
	if (t != NULL) {
		t->toreverse = !t->toreverse;
		swap(t->leftel, t->rightel);
	}
}

void update(Node* t) {
	if (t == NULL)
		return;
	t->size = size(t->left) + size(t->right) + 1;
	// TODO: ��������� ���������� ���������
	double newdist = 0;
	if (t->toreverse) {
		t->toreverse = false;
		
		Node* tmp = t->left; 
		t->left = t->right;
		t->right = tmp;

		torev(t->left);
		torev(t->right);
		// ���������� ����������
		if (t->left) {
			newdist += dist(t->left);
			newdist += Distance(t->p, t->left->rightel);
		}
		if (t->right) {
			newdist += dist(t->right);
			newdist += Distance(t->p, t->right->leftel);
		}
	}
}

Node* Merge(Node* left, Node* right) {
	if (left == NULL) {
		return right;
	}
	if (right == NULL) {
		return left;
	}
	update(left);
	update(right);
	if (left->y < right->y) {
		Node* t = Merge(left->right, right);
		left->right = t;
		update(left);
		return left;
	}
	else {
		Node* t = Merge(left, right->left);
		right->left = t;
		update(right);
		return right;
	}
}

tpair Split(Node* t, int key) {
	if (t == NULL) {
		return tpair(NULL, NULL);
	}
	update(t);
	if (size(t->left) >= key) {
		tpair p;
		p = Split(t->left, key);
		t->left = p.second;
		update(t);
		p.second = t;
		return p;
	}
	else {
		tpair p;
		p = Split(t->right, key - size(t->left) - 1);
		t->right = p.first;
		update(t);
		p.first = t;
		return p;
	}
}

void Reverse(Node* t, int ind, int len) {
	if (t == NULL)
		return;
	tpair tp1, tp2;
	tp1 = Split(t, ind);
	update(tp1.second);
	tp2 = Split(tp1.second, len);
	tp2.first->toreverse = !tp2.first->toreverse;
	update(tp2.first);
	tp1.second = Merge(tp2.first, tp2.second);
	update(tp1.second);
	t = Merge(tp1.first, tp1.second);
	update(t);
}



void write(Node* t) {
	if (!t)
		return;
	//update(t);
	write(t->left);
	cout << t->value << ' ';
	write(t->right);
}

int main()
{
	
    return 0;
}

