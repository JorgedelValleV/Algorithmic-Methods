// Hoja 6 Ejercicio 21 Jorge del Valle Vazquez (dos formas)

// Ejercicio 21.  La empresa SlowTravel ofrece un recorrido en burro por la Alcarria. La ruta consiste en visitar n pueblos en un orden preestablecido 1,2,...,n. En cada pueblo, el viajero tiene la posiblidad de cambiar de burro o de seguir con el que tiene. Se conoce el coste pij de alquilar un pollino en cada pueblo i y dejarlo en cualquier pueblo j situado más adelante en la ruta. Desarrollar un algoritmo que encuentre la secuencia de alquileres de pollinos para hacer la ruta completa, que tenga coste mínimo. Los costes en tiempo y en espacio del algoritmo no han de exceder respectivamente O(n2) y O(n).  

// Buscamos un subconjunto R = {r1, ..., rl} ⇢ P tal que el coste C(R) = suma p(i)(i+1) 1<=i<=l-1 sea minimo

// coste(i) := coste minimo para llegar al final desde i.
// cuesta(i) := coste minimo para llegar desde el inicio a i.

// coste(i) = min{pij + coste(j)}		i + 1 ≤ j ≤ n	1≤i<n
// cuesta(i) = min{cuesta(j) + pji}		1 ≤ j ≤ i - 1	1<i≤n

// He supuesto pii=0 sino solo haria falta eliminar tal caso de los posibles minimos

// coste(n) = 0	
// cuesta(1) = 0	

// Utilizamos un vector coste espacio O(N)
// Recorremos el vector y para cada posicion desde el inicio hasta esta misma coste tiempo O(N^2)

// tiempo  O(N^2)
// espacio O(N)

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;
int burroMinCost(vector<vector<int>> const& p, int N) {
	vector <int> coste(N, 0);
	vector <int> puebloto(N, 0);//reconstruccion
	for (int i = N - 2; i >= 0; --i) {
		int mejor = p[i][N-1] + 0;
		puebloto[i] = N-1;
		for (int j = i+1; j < N-1; ++j) {
			if (mejor > p[i][j] + coste[j]) {
				mejor = p[i][j] + coste[j];
				puebloto[i] = j;
			}
		}
		coste[i] = mejor;
	}
	//reconstruccion
	int k = 0;
	vector<int> recorrido;
	while (k != N-1) {
		recorrido.push_back(k);//orden correcto
		k = puebloto[k];
	}
	recorrido.push_back(k);
	return coste[0];
}

int burritoMinCost(vector<vector<int>> const& p, int N) {
	vector <int> cuesta(N, 0);
	vector <int> puebloto(N, 0);//reconstruccion
	for(int i = 1; i < N; ++i) {
		int mejor = 0 + p[0][i];
		puebloto[i] = 0;
		for(int j = 1; j < i; ++j) {
			if (mejor > cuesta[j] + p[j][i]) {
				mejor = cuesta[j] + p[j][i];
				puebloto[i] = j;
			}
		}
		cuesta[i] = mejor;
	}
	//reconstruccion
	int k = N - 1;
	vector<int> recorrido;
	while (k != 0) {
		recorrido.push_back(k);//orden inverso
		k= puebloto[k];
	}
	recorrido.push_back(k);
	return cuesta[N-1];
}

int main() {
	int N = 5;
	vector<vector<int>> v = {	{ 0,1,3,2,5 },
								{ 0,0,3,1,3 } ,
								{ 0,0,0,4,7 } ,
								{ 0,0,0,0,2 } ,
								{ 0,0,0,0,0 } };
	int sol = burritoMinCost(v, N);
	cout << sol << '\n';
	system("PAUSE");
	return 0;
}
