#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "bintree_eda.h"

using namespace std;


// comprueba si es un arbol equilibrado
template <typename T>
pair<bool,int> arbolEquilibrado(bintree<T> tree) {
	//T raiz;
	//std::cin >> raiz;
	if (tree.empty()) { // es un árbol vacío
		return {true,0};
	}
	else { // comprueba recursivamente los hijos
		auto iz = arbolEquilibrado(tree.left());
		auto dr = arbolEquilibrado(tree.right());
		return { iz.first&& dr.first && abs(iz.second - dr.second)<=1,1+max(iz.second, dr.second) };
	}
}


void resuelveCaso() {
	bintree<char> bt = leerArbol('.');
	bool x = arbolEquilibrado(bt).first;
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