// Jorge del Valle Vazquez DG30
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int resolver(vector<int> const & cubos) {
	vector<vector<int>> matriz(cubos.size(), vector<int>(cubos.size()));
	for (int i = 0; i < cubos.size(); ++i) {
		matriz[i][i] = cubos[i];
	}
	for (int i = 0; i < cubos.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			matriz[i][j] = 0;
		}
	}
	for (int i = cubos.size() - 2; i >= 0; --i) {
		for (int j = i + 1; j < cubos.size(); ++j) {
			int v1, v2;
			if (cubos[i + 1] > cubos[j])v1 = matriz[i + 2][j];
			else						v1 = matriz[i + 1][j - 1];
			if (cubos[j - 1] > cubos[i])v2 = matriz[i][j - 2];
			else						v2 = matriz[i + 1][j - 1];
			matriz[i][j] = max(cubos[i] + v1, cubos[j] + v2);
		}
	}
	return matriz[0][cubos.size() - 1];
}

bool resuelveCaso() {
	int N;
	cin >> N;
	if (N == 0)return false;
	vector<int> cubos(N);
	for (int i = 0; i < N; ++i) {
		cin >> cubos[i];
	}
	int sol = resolver(cubos);
	cout << sol << '\n';
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