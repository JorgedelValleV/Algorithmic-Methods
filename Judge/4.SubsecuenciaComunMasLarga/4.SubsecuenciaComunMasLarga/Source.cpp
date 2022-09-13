// Jorge del Valle Vazquez DG30

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<char> resolver(string const & X, string const & Y) {
	vector<vector<int>> matriz(X.size() + 1, vector<int>(Y.size() + 1, 0));
	for (int i = 1; i < X.size() + 1; ++i) {
		for (int j = 1; j < Y.size() + 1; ++j) {
			if (X[i - 1] == Y[j - 1])//coinciden
				matriz[i][j] = matriz[i - 1][j - 1] + 1;
			else
				matriz[i][j] = max(matriz[i - 1][j], matriz[i][j - 1]);
		}
	}
	vector<char> solucion;
	int i = X.size();
	for (int j = Y.size(); j > 0; --j) {
		if (matriz[i][j] != matriz[i][j - 1]) {
			solucion.push_back(Y[j - 1]);
			--i;
			while (X[i] != Y[j - 1]) {
				--i;
			}
		}
	}
	return solucion;
}
bool resuelveCaso() {
	string X;
	cin >> X;
	if (!cin)return false;
	string Y;
	cin >> Y;
	vector<char> solucion = resolver(Y, X);
	for (int i = solucion.size() - 1; i >= 0; --i) {
		cout << solucion[i];
	}
	cout << '\n';
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