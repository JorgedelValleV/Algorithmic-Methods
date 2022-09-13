// Jorge del Valle Vazquez DG30

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <math.h>
using namespace std;
int resolver(vector<int> const& cortes) {
	vector<vector<int>> matriz(cortes.size(), vector<int>(cortes.size()));//matriz(i,j) = esfuerzo minimo haciendo los cortes desde i hasta j
	for (int diag = 2; diag < cortes.size(); ++diag) {
		for (int i = 0; i < cortes.size() - diag; ++i) {
			int j = i + diag;
			int minimo = INT_MAX;
			for (int k = i + 1; k < j; ++k) {
				minimo = min(minimo, matriz[i][k] + matriz[k][j]);
			}
			matriz[i][j] = minimo + 2 * (cortes[j] - cortes[i]);
		}
	}
	return matriz[0][cortes.size() - 1];
}


bool resuelveCaso() {
	int L, N;
	cin >> L >> N;
	if (N == 0 && L == 0)return false;
	vector<int> cortes(N + 2);
	cortes[0] = 0;
	cortes[N + 1] = L;
	for (int i = 1; i < N + 1; ++i) {
		cin >> cortes[i];
	}
	cout << resolver(cortes) << '\n';
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
}