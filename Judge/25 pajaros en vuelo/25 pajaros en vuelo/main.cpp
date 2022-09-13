#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stack>
#include "PriorityQueue.h"

using namespace std;

struct comp
{
	bool operator() (int a, int b) { return a>b; }
};


bool resuelveCaso() {
	int n,m;
	cin >> n>>m;
	if (n==0 && m==0)return false;
	PriorityQueue<int> mayores;
	mayores.push(n);
	PriorityQueue<int, comp> menores;
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		cin >> a>>b;
		if (a > mayores.top()) {
			mayores.push(a);
		}
		else {
			menores.push(a);
		}
		if (b > mayores.top()) {
			mayores.push(b);
		}
		else {
			menores.push(b);
		}
		if (mayores.size() > menores.size() + 1) {// los dos nuevos son mayores que el lider
			menores.push(mayores.top());
			mayores.pop();
		}
		if (mayores.size() < menores.size()) {// los dos nuevos son menores que el lider
			mayores.push(menores.top());
			menores.pop();
		}
		cout << mayores.top() << ' ';
	}
	std::cout << '\n';
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