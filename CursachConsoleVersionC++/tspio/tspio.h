#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <map>

using namespace std;

namespace tspio
{
	static class TSPIO
	{
	public:
		static void NormString(string &s);

		static double ToDouble(const string &s);

		static void ReadTsp(vector < pair < double, double > > &g, string filename, map <string, string> &info);

		static void WriteTsp(vector < pair < double, double > > &g, string filename, map <string, string> &info);

		static void WriteOptTour(vector < int > &state, string filename, map <string, string> &info);
	};
}