#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>
#include "Grafo.h"

using namespace std;
const std::vector<int> incF = { -1,1,0,0 };//arriba  abajo derecha izquierda
const std::vector<int> incC = { 0,0,1,-1 };//arriba  abajo derecha izquierda

enum tColor { blanco, gris, negro };
bool bfs(int v, Grafo grafo, vector<tColor> & marcas, vector<bool> const & estadoCasillas, int salida, int & sol) {
	if (!estadoCasillas[v])return false;//
	vector<int> niveles(grafo.V(), -1);
	queue <int> q;
	q.push(v);
	bool noenc = true;
	marcas[v] = gris;
	niveles[v] = 0;
	while (!q.empty() && noenc) {
		int x = q.front();
		q.pop();
		vector<int> ad = grafo.ady(x);//miramos las casillas candidatas a ser la siguiente
		int i = 0;
		while (i < ad.size() && noenc) {
			if (marcas[ad[i]] == blanco && estadoCasillas[ad[i]]) {// todavia no lo he visitado, y no es ni muro ni queda controlada por un sensor
				niveles[ad[i]] = niveles[x] + 1;//nivel en que visito la casilla es uno mas que el nivel desde la que accedo a ella
				if (ad[i] == salida)//he llegado a la salida
					noenc = false;
				else {
					marcas[ad[i]] = gris;
					q.push(ad[i]);
				}
			}
			++i;
		}
	}
	sol = niveles[salida];
	return !noenc;
}
bool resolver(Grafo const & grafo, int origen, int salida, int & sol, vector<bool> const & estadoCasillas) {
	//Mediante busqueda en profundidad con poda, llegamos si existe al camino mas corto.
	vector<int> niveles(grafo.V());//num elem es eltotal de casillas
	vector<tColor> marcas(grafo.V(), blanco);// vamos marcando las transitadas entre las posibles que nos deja estadoCasilla
	return bfs(origen, grafo, marcas, estadoCasillas, salida, sol);
}
void marcar(vector<vector<pair<char, bool>>> & matriz, pair<int, pair<int, int>> const& sensor, int alto, int ancho) {
	for (int i = 0; i < 4; ++i) {//arriba(0)  abajo(1) derecha(2) izquierda(3)
		int j = 1;
		bool continuar = true;
		while (j <= sensor.first && continuar) { 
			int fila = sensor.second.first + incF[i] * j;//fila del sensor +: -j(0)  +j(1) +0(2) +0(3)
			int col = sensor.second.second + incC[i] * j;//colu del sensor +: +0(0)  +0(1) +j(2) -j(3)
			if (0 <= fila && fila < alto && 0 <= col && col < ancho) { // si la casilla existe(esta dentro de los margenes)
				matriz[fila][col].second = false; // Si es muro o sensor ya estaba marcada a false, si era E , P o . ahora queda marcada
				if (matriz[fila][col].first == '#') // Si es muro el sensor se detienes
					continuar = false;
			}
			else {
				continuar = false;
			}
			++j;
		}
	}
}
void resuelveCaso() {
	// leer los datos de la entrada
	char car;
	int alto, ancho, entrada, puerta;
	cin >> ancho >> alto;
	vector<vector<pair<char, bool>>> matriz(alto);// guarda el caracter seguido de si podria pasar por esa celda // no utilizo matriz.h porque da problemas con los bool
	vector<pair<int, pair<int, int>>> sensores;//alcance, fila,columna
	vector<bool> estadoCasillas(alto*ancho);//el elemento de la fila f y la columna c esta en la posicion f*(ancho matriz) +c
	for (int i = 0; i<alto; ++i) {
		for (int j = 0; j < ancho; ++j) {
			cin >> car;
			if (car == '.') {//vacia
				matriz[i].push_back({ car,true });
			}
			else if (car == 'E') {//entrada
				entrada = ancho*i + j;
				matriz[i].push_back({ car,true });
			}
			else if (car == 'P') {//puerta
				puerta = ancho*i + j;
				matriz[i].push_back({ car,true });
			}
			else if (car == '#') {//muro
				matriz[i].push_back({ car,false });
			}
			else {//sensor
				int n = int(car) - int('0');
				matriz[i].push_back({ car,false });
				sensores.push_back({ n,{ i,j } });
			}
		}
	}
	for (int i = 0; i < sensores.size(); ++i) {//inhabilitamos o marcamos las alcanzadas por un sensor
		marcar(matriz, sensores[i], alto, ancho);
	}
	Grafo grafo(alto*ancho);
	for (int i = 0; i < alto; ++i) {//empezamos en la posicion de arriba a la izquierda
		for (int j = 0; j < ancho; ++j) {
			estadoCasillas[ancho*i + j] = matriz[i][j].second;
			if (0 <= i && i < alto && 0 <= j + 1 && j + 1 < ancho)//podemos ir a la casilla que nos queda a la derecha?
				grafo.ponArista(ancho * i + j, ancho * i + j + 1);
			if (0 <= i + 1 && i + 1 < alto && 0 <= j && j < ancho)//podemos ir a la casilla que nos queda debajo?
				grafo.ponArista(ancho * i + j, ancho * (i + 1) + j);
		}
	}
	int sol = 0;
	if (resolver(grafo, entrada, puerta, sol, estadoCasillas))cout << sol << '\n';
	else cout << "NO" << '\n';
}
int main() {
	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int numcasos;
	cin >> numcasos;
	int i = 0;
	while (i<numcasos) {
		resuelveCaso();
		++i; 
	}

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}