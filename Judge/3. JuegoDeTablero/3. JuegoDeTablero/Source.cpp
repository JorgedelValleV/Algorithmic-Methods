// Jorge del Valle Vazquez DG30
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include<algorithm>

using namespace std;
bool exist(int N, int j) {
	return j >= 0 && j < N;
}
pair<int, int> resolver(vector<vector<int>> const & tablero) {
	vector<vector<int>> matriz(tablero.size(), vector<int>(tablero.size()));//guarda la suma maxima
	for (int j = 0; j < tablero.size(); ++j) {
		matriz[0][j] = tablero[0][j];
	}
	for (int i = 1; i < tablero.size(); ++i) {
		for (int j = 0; j < tablero.size(); ++j) {
			matriz[i][j] = tablero[i][j];
			if (exist(tablero.size(), j - 1) && exist(tablero.size(), j + 1))//exiten tres posibilidades --->max de las tres
				matriz[i][j] +=max(max(matriz[i - 1][j + 1], matriz[i - 1][j]), matriz[i - 1][j - 1]);
			else {
				if (exist(tablero.size(), j - 1))//existe la diagonal izquierda y vertical
					matriz[i][j] += max(matriz[i - 1][j - 1], matriz[i - 1][j]);
				else//existe vertical y la diagonal derecha 
					matriz[i][j] += max(matriz[i - 1][j + 1], matriz[i - 1][j]);
			}
		}
	}
	int maxValor = 0;
	int columna = 0;
	int i = tablero.size();
	for (int j = 0; j < tablero.size(); ++j) {
		if (matriz[i - 1][j] > maxValor) {
			maxValor = matriz[i - 1][j];
			columna = j + 1;
		}
	}
	return { maxValor,columna };
}
bool resuelveCaso() {
	int N;
	cin >> N;
	if (!cin)return false;
	vector<vector<int>> tablero(N,vector<int> (N));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> tablero[i][j];
		}
	}
	pair<int, int> solucion = resolver(tablero);
	cout << solucion.first << ' ' << solucion.second << '\n';
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