#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "PriorityQueue.h"

using namespace std;


/*long long int resolver(PriorityQueue<long long int> pq) {
	long long int sol = 0; long long int coste = 0;
	 if (pq.size() <= 1)return coste;
	 else {
		 long long int val;
		 pq.pop(val);
		 sol += val;
		 while (!pq.empty()) {
			 pq.pop(val);
			 sol = sol + val;
			 coste = coste + sol;
		 }
	 }
	 return coste;
}*/
long long int resolver(PriorityQueue<long long int> pq) {
	long long int suma = 0;
	while (pq.size() > 1) {
		long long int valor1, valor2;
		valor1 = pq.top();
		pq.pop();
		valor2 = pq.top();
		pq.pop();
		suma = suma + valor1 + valor2;
		pq.push(valor1 + valor2);
	}
	return suma;
}


bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0)return false;
	vector<long long int> v(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> v[i];
	}
	PriorityQueue<long long int> pq(v);
	long long int sol = resolver(pq);
	cout << sol << '\n';
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