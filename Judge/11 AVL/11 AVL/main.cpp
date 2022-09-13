#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "bintree_eda.h"

using namespace std;

const int N = 100000;
// comprueba si es un arbol equilibrado
struct TDev {
	bool b;
	int h;
	int min;
	int max;
};
template <typename T>
TDev arbolAVL(bintree<T> tree) {
	if (tree.empty()) { // es un árbol vacío
		return {true,0,N,-N};

	}
	else { // comprueba recursivamente los hijos
		auto iz = arbolAVL(tree.left());
		auto dr = arbolAVL(tree.right());
		return { iz.b&& dr.b && abs(iz.h - dr.h) <= 1 && iz.max<tree.root() && tree.root() < dr.min,1 + max(iz.h, dr.h),min(iz.min,tree.root()),max(dr.max, tree.root()) };
	}
}


void resuelveCaso() {
	bintree<int> bt = leerArbol(-1);
	bool x = arbolAVL(bt).b;
	if (x)cout << "SI\n";
	else cout << "NO\n";
}

int main() {
	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int numCasos;
	cin >> numCasos;
	int i = 0;
	while (i++<numCasos) {
		resuelveCaso();
	}

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}