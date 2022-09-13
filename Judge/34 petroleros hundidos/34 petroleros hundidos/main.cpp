#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "ConjuntosDisjuntos.h"

using namespace std;

bool resuelveCaso() {
	int filas;
	std::cin >> filas;
	if (!std::cin)return false;
	int columnas;
	std::cin >> columnas;
	char caractersaltodelinea;
	std::cin.get(caractersaltodelinea);
	std::vector<bool> petroleo(filas*columnas, false);
	ConjuntosDisjuntos conjuntos(filas*columnas);
	bool hayPetroleo = false;
	int contador = 0;
	int maximo = 0;


	string linea;
	getline(cin, linea);
	// primera fila
	for (int j = 0; j < columnas; ++j) {
		if (linea[j] == '#') {
			petroleo[contador] = true;
			hayPetroleo = true;
			if (j>0&&petroleo[j] == petroleo[j - 1]) {
				conjuntos.unir(j, j - 1);
			}
			maximo = std::max(maximo, conjuntos.tam(j));
		}
		++contador;
	}
	//Resto de filas

	
	for (int i = 1; i < filas; ++i) {
		getline(cin, linea);
		//Resto de elementos menos el ultimo
		for (int j = 0; j < columnas; ++j) {
			if (linea[j] == '#') {
				petroleo[contador] = true;
				hayPetroleo = true;

				if (petroleo[contador] == petroleo[contador - columnas])//arriba
					conjuntos.unir(contador, contador - columnas);
				if (j<columnas-1 && petroleo[contador] == petroleo[contador - columnas + 1])//arriba dcha
					conjuntos.unir(contador, contador - columnas + 1);

				if (j>0 && petroleo[contador] == petroleo[contador - 1])//izqda -----------el primero de la fila no tiene elemento a su izquierda
					conjuntos.unir(contador, contador - 1);

				if (j >0 && petroleo[contador] == petroleo[contador - columnas - 1])//arriba izda-----------el primero de la fila no tiene elemento a su izquierda
					conjuntos.unir(contador, contador - columnas - 1);

				maximo = std::max(maximo, conjuntos.tam(contador));
			}
			++contador;
		}
		//Ultimo elemento de la fila
		/*if (columnas > 1) {
			if (linea[columnas-1] == '#') {
				petroleo[contador] = true;
				hayPetroleo = true;
				if (petroleo[contador] == petroleo[contador - 1])//izqda
					conjuntos.unir(contador, contador - 1);
				if (petroleo[contador] == petroleo[contador - columnas - 1])//arriba izqda
					conjuntos.unir(contador, contador - columnas - 1);
				if (petroleo[contador] == petroleo[contador - columnas ])//arriba
					conjuntos.unir(contador, contador - columnas );
				maximo = max(maximo, conjuntos.tam(contador));
			}
			++contador;
		}*/
	}
	std::cout << maximo;

	int modificaciones;
	std::cin >> modificaciones;
	int fila, col;
	for (int i = 0; i < modificaciones; ++i) {
		std::cin >> fila >> col;
		int pos = columnas*(fila - 1) + col -1;
		petroleo[pos] = true;
		if (col < columnas && petroleo[pos +1]) { //derecha +1
			conjuntos.unir(pos, pos +1);
		}
		if (col > 1 && petroleo[pos-1]) { // izquierda -1
			conjuntos.unir(pos, pos-1);
		}
		if (fila > 1 && petroleo[pos-columnas]) { // Arriba -columnas
			conjuntos.unir(pos, pos - columnas);
		}
		if (fila < filas && petroleo[pos + columnas]) { //Abajo  +columnas
			conjuntos.unir(pos, pos + columnas);
		}
		if (fila > 1 && col < columnas && petroleo[pos - columnas +1]) { //Arriba derecha -columnas+1
			conjuntos.unir(pos, pos - columnas +1);
		}
		if (fila> 1 && col > 1 && petroleo[pos - columnas -1]) { //Arriba izquierda -columnas-1
			conjuntos.unir(pos, pos - columnas - 1);
		}
		if (fila < filas && col < columnas && petroleo[pos + columnas +1]) { //Abajo derecha +columnas +1
			conjuntos.unir(pos, pos + columnas + 1);
		}
		if (fila < filas && col > 1 && petroleo[pos + columnas - 1]) { //Abajo izquierda +columnas-1
			conjuntos.unir(pos, pos + columnas -1);
		}
		maximo = max(maximo, conjuntos.tam(pos));
		cout << " " << maximo;
	}
	cout << '\n';
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