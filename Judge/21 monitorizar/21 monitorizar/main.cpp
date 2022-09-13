#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "PriorityQueue.h"

using namespace std;
using tipoDat = pair<long int, pair<long int, long int>>;
struct comp
{
	bool operator() (tipoDat a, tipoDat b){ return a.second.second < b.second.second || (a.second.second == b.second.second && a.first < b.first); }
};

void resolver(PriorityQueue<tipoDat,comp> pq,int k) {
	 //vector<int> sol;
	 for (int i = 0; i < k; ++i)
	 {
		 tipoDat x = pq.top();
		 cout << x.first << '\n';
		 //sol.push_back(x.elem);
		 pq.pop();
		 pq.push({ x.first,{ x.second.first,x.second.second+x.second.first} });
	 }
}


bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0)return false;
	int id,prio;
	PriorityQueue<tipoDat,comp> pqi;
	for (int i = 0; i < n; ++i)
	{
		cin >> id >> prio;
		pqi.push({ id, {prio,prio } });
	}
	int k;
	cin >> k;
	resolver(pqi,k);
	cout <<"---\n";
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