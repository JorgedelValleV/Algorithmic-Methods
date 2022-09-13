#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

int resolver(vector<pair<int, int>>& jobs, int c, int f, bool & posible) {
	sort(jobs.begin(), jobs.end());//orden pormenor comienzo menor final
	stack<pair<int, int>> stack;
	int i = 0;
	int dev = 0;
	bool complete = false;
	posible = true;
	int ultima_cubierta = c;
	while (!complete && posible && i < jobs.size()) {
		if (!stack.empty() && jobs[i].first > ultima_cubierta) {//el actual dejaria libre hueco, por eso cogemos el anterior
			if (stack.top().first <= ultima_cubierta && stack.top().second > ultima_cubierta) {//amplia el rago actual
				++dev;
				ultima_cubierta = stack.top().second;
				stack.pop();
			}
			else {
				posible = false;
			}
		}
		if (ultima_cubierta >= f) {
			complete = true;
		}
		if (jobs[i].first <= ultima_cubierta && !complete) {//nuevo trabajo a considerar
			if (stack.empty() || jobs[i].second > stack.top().second)
				stack.push(jobs[i]);
		}
		++i;
	}
	if (!stack.empty() && !complete) {
		if (stack.top().first <= ultima_cubierta && stack.top().second > ultima_cubierta) {
			++dev;
			ultima_cubierta = stack.top().second;
			stack.pop();
		}
		else {
			posible = false;
		}
	}
	if (ultima_cubierta < f) {
		posible = false;
	}
	return dev;
}

bool resuelveCaso() {
	int c, f, Njobs;
	cin >> c >> f >> Njobs;
	if (c == 0 && f == 0 && Njobs == 0)return false;
	vector<pair<int, int>> jobs;//ini fin
	int ini, fin;
	for (int i = 0; i < Njobs; ++i) {
		cin >> ini >> fin;
		jobs.push_back({ ini, fin });
	}
	bool posible;
	int min_trabajos = resolver(jobs, c, f, posible);
	if (!posible)cout << "Imposible\n" ;
	else cout << min_trabajos << '\n';
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