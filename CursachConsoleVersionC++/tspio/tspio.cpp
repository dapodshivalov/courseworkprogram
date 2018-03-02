#include "tspio.h"

namespace tspio
{
	void TSPIO::NormString(string &s) {
		if (s.length() == 0)
			return;
		if (s[0] == ' ') {
			s = s.substr(1);
		}
		if (s[s.length() - 1] == ' ') {
			s = s.substr(0, s.length() - 1);
		}
	}

	double TSPIO::ToDouble(const string &s) {
		double res = 0, d = 1;
		bool isDiv = 0;
		for (int i = 0; i < (int)s.length(); i++) {
			if (s[i] == '.') {
				isDiv = 1;
				continue;
			}
			if (!isDiv) {
				res *= 10;
				res += (s[i] - '0');
			}
			else {
				res += (s[i] - '0') / d;
				d *= 10;
			}
		}
		return res;
	}

	void TSPIO::ReadTsp(vector < pair < double, double > > &g, string filename, map <string, string> &info) {
		ifstream fin;
		fin.open(filename);
		int n;
		info.clear();
		string data, key, value;
		getline(fin, data);
		while (data != "NODE_COORD_SECTION") {
			int pos = data.find(':');
			key = data.substr(0, pos);
			NormString(key);
			value = data.substr(pos + 1);
			NormString(value);
			info.insert(make_pair(key, value));
			if (key == "DIMENSION") {
				n = (int)ToDouble(value);
			}
			getline(fin, data);
		}

		g.resize(n);
		string strx, stry;
		double x, y;
		for (int i = 0; i < n; i++) {
			getline(fin, data);
			int pos1 = data.find(' ');
			int pos2 = data.find(' ', pos1 + 1);
			strx = data.substr(pos1 + 1, pos2 - pos1 - 1);
			stry = data.substr(pos2 + 1);
			x = ToDouble(strx);
			y = ToDouble(stry);
			g[i] = make_pair(x, y);
		}
		fin.close();
	}


	void TSPIO::WriteTsp(vector < pair < double, double > > &g, string filename, map <string, string> &info) {
		ofstream fout;
		fout.open(filename + ".tsp");
		int n = g.size();

		for each (auto var in info)
		{
			fout << var.first << ": " << var.second << "\n";
		}

		fout << "NODE_COORD_SECTION\n";

		string strx, stry;
		double x, y;
		for (int i = 0; i < n; i++) {
			x = g[i].first;
			y = g[i].second;
			strx = to_string(x);
			stry = to_string(y);
			fout << to_string(i + 1) << ' ' << strx << ' ' << stry << "\n";
		}
		fout << "EOF";
		fout.close();
	}

	void TSPIO::WriteOptTour(vector < int > &state, string filename, map <string, string> &info) {
		ofstream fout;
		fout.open(filename + ".opt.tour");
		int n = state.size();

		for each (auto var in info)
		{
			fout << var.first << ": " << var.second << "\n";
		}

		fout << "TOUR_SECTION\n";

		string strind;
		int ind;
		for (int i = 0; i < n; i++) {
			ind = state[i];
			strind = to_string(ind);
			fout << strind << "\n";
		}
		fout << "-1\nEOF";
		fout.close();
	}
}