#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stack>
#include "PriorityQueue.h"

using namespace std;

bool resuelveCaso() {
	long long int n;
	cin >> n;
	if (!cin)return false;
	long long int A,B,val;
	cin >> A >> B;
	PriorityQueue<long long int, std::greater<long long int>> nueve;
	PriorityQueue<long long int, std::greater<long long int>> uno;
	stack<long long int> grandes;
	stack<long long int> pequenas;
	for (int i = 0; i < A; ++i)
	{
		cin >> val;
		nueve.push(val);
	}
	for (int j = 0; j < B; ++j)
	{
		cin >> val;
		uno.push(val);
	}
	while (!nueve.empty() && !uno.empty() && n!=0) {
		long long int suma = 0;
		for (int i = 0; i < n; ++i)
		{
			if (!nueve.empty() && !uno.empty()) {
				long long int x = nueve.top();
				long long int y = uno.top();
				long long int m = min(x, y);
				nueve.pop();
				uno.pop();
				if(x-m!=0)grandes.push(x-m);
				if (y - m != 0)pequenas.push(y-m);
				suma += m;
			}
		}
		while (!grandes.empty()) {
			nueve.push(grandes.top());
			grandes.pop();
		}
		while (!pequenas.empty()) {
			uno.push(pequenas.top());
			pequenas.pop();
		}
		cout << suma << ' ';
	}
	if (n == 0)std::cout << '0';
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