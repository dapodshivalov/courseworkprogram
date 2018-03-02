/*
Декартово дерево по неявному ключу.
Работает корректно.
Проверенно на задаче Переворот:
http://informatics.mccme.ru/mod/statements/view3.php?chapterid=111240#1
*/


#include "treaplib.h"


using namespace std;

namespace treaplib {

	struct TREAP::Point {
		double x, y;
		Point(double x, double y) {
			this->x = x;
			this->y = y;
		}
		double distTo(Point* a) {
			return std::sqrt((x - a->x) * (x - a->x) + (y - a->y) * (y - a->y));
		}
	};

	struct TREAP::Node {
		int y, value, size;
		double dist;
		Point* p;
		// самый левый элемент в поддереве
		Point* leftel;
		// самый правый элемент в поддереве
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
			this->toreverse = false;
		}
	};

	typedef pair < TREAP::Node*, TREAP::Node* > tpair;

	int TREAP::size(Node* t) { return (t == NULL ? 0 : t->size); }
	double TREAP::dist(Node* t) { return (t == NULL ? 0 : t->dist); }
	void TREAP::torev(Node* t) {
		if (t != NULL) {
			t->toreverse = !t->toreverse;
			swap(t->leftel, t->rightel);
		}
	}

	void TREAP::update(Node* t) {
		if (t == NULL)
			return;
		t->size = size(t->left) + size(t->right) + 1;
		// TODO: прописать обновление дистанции
		double newdist = 0;
		if (t->toreverse) {
			t->toreverse = false;

			Node* tmp = t->left;
			t->left = t->right;
			t->right = tmp;

			torev(t->left);
			torev(t->right);
			// обновление расстояния
			if (t->left) {
				newdist += dist(t->left);
				newdist += t->p->distTo(t->left->rightel);
			}
			if (t->right) {
				newdist += dist(t->right);
				newdist += t->p->distTo(t->right->leftel);
			}
		}
	}

	TREAP::Node* TREAP::Merge(Node* left, Node* right) {
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

	TREAP::tpair TREAP::Split(Node* t, int key) {
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

	void TREAP::Reverse(Node* t, int ind, int len) {
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



	void TREAP::write(Node* t) {
		if (!t)
			return;
		//update(t);
		write(t->left);
		cout << t->value << ' ';
		write(t->right);
	}
}