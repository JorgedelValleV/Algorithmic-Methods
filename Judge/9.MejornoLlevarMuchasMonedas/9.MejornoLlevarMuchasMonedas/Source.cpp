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
pair<bool,int> resolver(vector<int> const & valor, vector<int> & cantidad, int precio) {
	vector<vector<int>> matriz(valor.size()+1, vector<int>(precio+1));
	for (int i = 0; i < precio+1; ++i) {
		matriz[0][i] = INT_MAX;
	}
	for (int i = 0; i < valor.size()+1; ++i) {
		matriz[i][0] = 0;
	}
	for (int i = 1; i < valor.size() + 1; ++i) {
		for (int j = 1; j < precio + 1; ++j) {
			if (cantidad[i - 1] > 0 && valor[i - 1] <= j) {
				int val = INT_MAX;
				int numUsadas=0;
				for (int k = 0; k <= (int)floor(j / valor[i - 1])&&k<=cantidad[i-1]; ++k) {
					int m = j - (k*valor[i - 1]);
					int n = matriz[i - 1][m] + k;
					if (n < 0)n = INT_MAX;//para cuando sumamos a int_max que da negativo
					if (n < val) {
						val =n;
						numUsadas = k;
					}
				}
				//cantidad[i - 1] = cantidad[i - 1] - numUsadas;
				matriz[i][j] = val;
			}
			else matriz[i][j] = matriz[i - 1][j];

		}
	}
	int n = matriz[valor.size()][precio];
	return {n!=INT_MAX, n};
}


bool resuelveCaso() {
	int N;
	cin >> N;
	if (!cin)return false;
	vector<int> valor(N);
	vector<int> cantidad(N);
	for (int i = 0; i < N; ++i) {
		cin >> valor[i];
	}
	for (int i = 0; i < N; ++i) {
		cin >> cantidad[i];
	}
	int precio;
	cin >> precio;
	auto solucion = resolver(valor, cantidad, precio);
	(solucion.first) ? cout <<"SI "<< solucion.second << '\n': cout << "NO\n";
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