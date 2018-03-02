#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

namespace treaplib {
	class TREAP
	{
	public:
		struct Point;
		struct Node;

		typedef pair <Node*, Node*> tpair;

		int size(Node* t);
		double dist(Node* t);
		void torev(Node* t);

		void update(Node* t);

		Node* Merge(Node* left, Node* right);

		tpair Split(Node* t, int key);

		void Reverse(Node* t, int ind, int len);

		void write(Node* t);
	};
}