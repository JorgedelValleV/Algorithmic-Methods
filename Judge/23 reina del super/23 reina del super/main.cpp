#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "IndexPQ.h"

using namespace std;

struct comp
{
	bool operator() (pair<int,int> a, pair<int, int> b) { return a.second < b.second || (a.second == b.second && a.first < b.first); }
};


bool resuelveCaso() {
	int n,c;
	cin >> n>>c;
	if (n == 0 && c == 0)return false;
	int cliente;
	IndexPQ<pair<int, int>,comp> pqi(n);
	for (int j = 0; j < n; ++j)
	{
		pqi.update(j, { j,0 });
	}
	for (int i = 0; i < c; ++i)
	{	
		cin >> cliente;
		auto x = pqi.top();
		pqi.update(x.elem, { x.elem, x.prioridad.second + cliente });
	}
	auto x = pqi.top();
	std::cout << x.elem+1<<'\n';
	return true;
}

int main() {
	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso());

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}