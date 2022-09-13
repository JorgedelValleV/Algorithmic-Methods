// Jorge del Valle Vazquez DG30
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void conectar(string X, string Y, vector<string> & personas, vector<vector<int>> & conexiones) {
	int i = 0;
	bool parar = false;//vemos si esa persona esta ya 
	while (i < personas.size() && !parar) {
		if (personas[i] == X)
			parar = true;
		else {
			++i;
		}
	}
	if (!parar)personas.push_back(X);
	int j = 0;
	parar = false;//vemos si esa persona esta ya 
	while (j < personas.size() && !parar) {
		if (personas[j] == Y)
			parar = true;
		else {
			++j;
		}
	}
	if (j == personas.size())personas.push_back(Y);
	conexiones[i][j] = 1;
	conexiones[j][i] = 1;
	conexiones[i][i] = 0;
	conexiones[j][j] = 0;

}
pair<int,bool> gradoDeSeparacion(vector<vector<int>> & conexiones) {
	int minimo = 0;
	for (int k = 0; k < conexiones.size(); ++k) {//para cada persona analizamos las relaciones que establece como intermediaria entre otras dos
		for (int i = 0; i < conexiones.size(); ++i) {
			for (int j = 0; j < conexiones.size(); ++j) {
				minimo = conexiones[i][k] + conexiones[k][j];
				if (minimo < 0)minimo = INT_MAX;//necesario puesto que he usado INT_MAX que al sumarle uno toma valores negativos
				if (minimo < conexiones[i][j])conexiones[i][j] = minimo;//el grado es menor de entre todas las relaciones que unen i con j
			}
		}
	}
	int i = 0;
	pair<int, bool> solucion = { 0,true };
	//comprobamos el maximo de entre los grados de separacion
	while (i < conexiones.size() && solucion.second) {
		int j = 0;
		while (j < i && solucion.second) {
			if (conexiones[i][j] >= INT_MAX)solucion.second = false;//hay una relacion que no se da entre dos personas
			else if (conexiones[i][j] > solucion.first)solucion.first = conexiones[i][j];
			++j;
		}
		++i;
	}
	return solucion;
}
bool resuelveCaso() {
	int P;
	cin >> P;
	if (!cin)return false;
	int R;
	cin >> R;
	string X, Y;
	vector<string> personas;
	vector<vector<int>> conexiones(P, vector<int>(P, INT_MAX));
	for (int i = 0; i < R; ++i) {
		cin >> X >> Y;
		conectar(X, Y, personas, conexiones);
	}
	auto solucion = gradoDeSeparacion(conexiones);
	solucion.second ? cout << solucion.first << '\n':cout << "DESCONECTADA\n";
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