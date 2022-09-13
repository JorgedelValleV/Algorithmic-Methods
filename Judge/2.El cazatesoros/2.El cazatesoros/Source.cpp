// Jorge del Valle Vazquez DG30
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int>  resolver(vector<pair<int, int>> const & cofres, int T, int & oroMax) {
	vector<vector<int>> matriz(cofres.size() + 1, vector<int>(T + 1));
	for (int j = 0; j < T+1; ++j) {matriz[0][j] = 0;}
	for (int j = 0; j < cofres.size()+1; ++j) {matriz[j][0] = 0;}
	for (int i = 1; i < cofres.size()+1; ++i) {
		int profundidad = cofres[i - 1].first;
		int oro = cofres[i - 1].second;
		for (int j = 1; j < T+1; ++j) {
			if (j < 3 * profundidad) {//para bajar hace falta p y para subir 2p => 3p
				matriz[i][j] = matriz[i - 1][j];
			}
			else {//tengo tiempo para coger el tesoro
				matriz[i][j] = max(matriz[i - 1][j - 3 * profundidad] + oro, matriz[i - 1][j]);//coger el tesoro + el maximo de considerar los tesoros anteriores con el tiempo que queda
			}
		}
	}
	oroMax = matriz[cofres.size()][T];
	vector<int> solucion;
	int j = T;
	for (int i = cofres.size(); i > 0; --i) {
		if (matriz[i][j] != matriz[i - 1][j]) {
			solucion.push_back(i - 1);
			j -= 3 * cofres[i - 1].first;
		}
	}
	return solucion;
}
bool resuelveCaso() {
	int T;
	cin >> T;
	if (!cin)return false;
	int N;
	cin >> N;
	int profundidad, oro;
	vector<pair<int, int>> cofres;
	for (int i = 0; i < N; ++i) {
		cin >> profundidad >> oro;
		cofres.push_back({ profundidad,oro });
	}
	int oroMax;
	vector<int> solucion = resolver(cofres, T, oroMax);
	cout << oroMax << '\n';
	cout << solucion.size() << '\n';
	for (int i = solucion.size() - 1; i >= 0; --i) {
		cout << cofres[solucion[i]].first << ' ' << cofres[solucion[i]].second << '\n';
	}
	cout << "---"<<'\n';
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