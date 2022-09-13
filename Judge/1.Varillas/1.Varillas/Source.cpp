// Jorge del Valle Vazquez DG30

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

bool esPosible(vector<pair<int, int>> const & varillas, int L, int & numManeras, int & minVarillas, int & minCoste) { //Se puede mejorar usando un vector auxiliar.
	vector<bool> posible(L + 1, false);
	vector<int> ManerasNum(L + 1, 0);
	vector<int> VarillasMin(L + 1, INT_MAX);
	vector<int> CosteMin(L + 1, INT_MAX);
	posible[0] = true;
	ManerasNum[0] = 1;
	VarillasMin[0] = 0;
	CosteMin[0] = 0;
	bool parar = false;
	for (int i = 1; i < L+1 && !parar; ++i) {
		if (varillas[0].first == i) {
			posible[i] = true;
			ManerasNum[i] = 1;
			VarillasMin[i] = 1;
			CosteMin[i] = varillas[0].second;
			parar = true;
		}
	}
	for (int i = 1; i < varillas.size(); ++i) {
		for (int j = L; j - varillas[i].first >= 0; --j) {
			if (posible[j - varillas[i].first]) {
				posible[j] = true;
				ManerasNum[j]  +=		 ManerasNum[j - varillas[i].first];
				VarillasMin[j] =	min(VarillasMin[j - varillas[i].first] + 1, VarillasMin[j]);
				CosteMin[j]	   =	min(   CosteMin[j - varillas[i].first] + varillas[i].second, CosteMin[j]);
			}
		}
	}
	numManeras = ManerasNum[L];
	minVarillas = VarillasMin[L];
	minCoste = CosteMin[L];
	return posible[L];
}

bool resuelveCaso() {
	int N, L;
	cin >> N >> L;
	if (!cin)return false;
	int longitud, coste;
	vector<pair<int, int>> varillas;
	for (int i = 0; i < N; ++i) {
		cin >> longitud >> coste;
		varillas.push_back({ longitud,coste });
	}
	int numManeras = 0;
	int minVarillas = 0;
	int minCoste = 0;
	esPosible(varillas, L, numManeras, minVarillas, minCoste) ? cout << "SI " << numManeras << ' ' << minVarillas << ' ' << minCoste << '\n' : cout << "NO" << '\n';
	return true;
}
int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif 
	while (resuelveCaso());
#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}