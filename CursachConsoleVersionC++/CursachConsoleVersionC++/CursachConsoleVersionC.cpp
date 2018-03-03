#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include "tspio.h"
#include "treaplib.h"

using namespace std;
using namespace tspio;
using namespace treaplib;

typedef long long i64;

const double initT = 100001;
const double minT = 1;

// TODO: 
// 1) pair <d,d> -> Point
// 2) 

double Distance(pair < double, double > a, pair < double, double > b) {
	return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

double Temp(int i) {
	// iniT  - initial temperature
	// i - number of current operation
	return initT  * 0.1 /  i;
}

// TODO: pair <d,d> -> Point
double Energy(vector < pair < double, double > > &g, vector < int > &state) {
	int n = g.size(), j, si, sj;
	double res = 0;
	for (int i = 0; i < n; i++) {
		j = (i + 1) % n;
		si = state[i];
		sj = state[j];
		res += Distance(g[sj], g[si]);
	}
	return res;
}

double P(double deltaE, double curT) {
	return exp(-deltaE / curT);
}

void Reverse(vector < int > &state, vector < int > &newstate, int from, int to) {
	int n = state.size();
	newstate.resize(n);
	for (int i = 0; i < n; i++)
		newstate[i] = state[i];
	if (to == from)
		return;
	if (to < from)
		swap(from, to);
	for (int i = from; i <= to; i++) {
		newstate[i] = state[to - (i - from)];
	}
}

void NextState(vector < int > &state, vector < int > &newstate) {
	int from, to, n = state.size();
	do {
		from = rand() % n;
		to = rand() % n;
	} while (from >= to);
	newstate.clear();
	Reverse(state, newstate, from, to);
}

double newStateEnergy(vector < pair < double, double > > &g, vector < int > &state, double stateEnergy, int &from, int &to) {
	int n = state.size();
	do {
		from = rand() % n;
		to = rand() % n;
	} while (from >= to);

	double res = stateEnergy;

	int fromPrev = from == 0 ? n - 1 : from - 1;
	int toNext = to == n - 1 ? 0 : to + 1;

	res -= Distance(g[state[fromPrev]], g[state[from]]);
	res -= Distance(g[state[to]], g[state[toNext]]);

	res += Distance(g[state[from]], g[state[toNext]]);
	res += Distance(g[state[to]], g[state[fromPrev]]);
	return res;
}

void GenSeq(vector < int > &state, int n) {
	state.resize(n);
	vector < bool > used(n, 0);
	int cnt = n, next, cur = 0;
	while (cnt-- > 0) {
		do
		{
			next = rand() % n;
		} while (used[next]);
		used[next] = true;
		state[cur++] = next;
	}
}

void PrintStatus(int ind, double e, int from = -1, int to = -1) {
	system("cls");
	cout <<"Ind: " <<ind  << " Temp: "<< Temp(ind) << " Energy: " << e << ' ' << from << ' ' << to << endl;
}

void MainAlgo(vector < pair < double, double > > &g, vector < int > &state) {
	GenSeq(state, g.size());
	vector < int > newstate;
	double energy = Energy(g, state);
	double curT = initT;
	double deltaE, newStateE;
	int i = 0, from, to;
	for (int i = 0; i < 1000000; i++){
		NextState(state, newstate);
		deltaE = Energy(g, newstate) - Energy(g, state);
		//newStateE = newStateEnergy(g, state, energy, from, to);
		//deltaE = newStateE - energy;
		if (deltaE < 0) {
			//Reverse(state, newstate, from, to);
			state = newstate;
			//energy = newStateE;
			energy = energy + deltaE;
			//PrintStatus(i, energy, from, to);
			//PrintStatus(i, energy);
		}
		else {
			double probability = P(deltaE, curT) * 100;
			double Godhand = rand() % 101;
			if (probability >= Godhand) {
				state = newstate;
				//energy = newStateE;
				energy = energy + deltaE;
				//PrintStatus(i, energy, from, to);
				//PrintStatus(i, energy);
			}
			else {
				//PrintStatus(i, energy);
			}
		}
		PrintStatus(i, energy);
		curT = Temp(i);
		if (curT <= minT)
			break;
	}
}
	

int main(int argc, char *argv[])
{
	/*
	map < string, string > info;
	vector < pair < double, double > > g;
	TSPIO::ReadTsp(g, "C:/Users/user/Documents/Visual Studio 2017/Projects/CursachConsoleVersionC++/tspio/kek.tsp", info);
	vector < int > state;
	MainAlgo(g, state);
	cout << "Length = " << Energy(g, state) << endl;
	for (int i = 0; i < state.size(); i++) {
		cout << state[i] << " : " << g[state[i]].first << ' ' << g[state[i]].second << endl;
	}
	*/
	/*
	int n;
	cin >> n;
	vector < int > a(n), newa;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Reverse(a, newa, i, j);
			for (int x = 0; x < n; x++) {
				cout << newa[x] << ' ';
			}
			cout << endl;
		}
	}
	*/
	int n;
	cin >> n;
	vector < pair < double, double > > g(n);
	int a, b, ind;
	for (int i = 0; i < n; i++) {
		cin >> ind >> a >> b;
		g[i].first = a;
		g[i].second = b;
	}
	vector < int > state;
	
	
	MainAlgo(g, state);


	cout << "anser =\n";
	for (int i = 0; i < n; i++) {
		cout << state[i] << "\n";
	}
	cout << "Distance = \n";
	cout << Energy(g, state);
	system("pause");
    return 0;
}
