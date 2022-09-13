#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;
bool resuelveCaso() {
	int numFilms;
	cin >> numFilms;
	if (numFilms == 0)return false;
	//lectura de datos
	vector<pair<int,int>> films;// fin ini
	int startHour, startMinute, duration, start;
	char dospuntos;
	for (int i = 0; i < numFilms; ++i) {
		cin >> startHour;
		cin.get(dospuntos);
		cin >> startMinute;
		cin >> duration;
		start = startHour * 60 + startMinute;//la hora en minutos
		films.push_back({ start + duration , start });// fin inicio
	}
	//resolver el problema
	sort(films.begin(), films.end());
	int cont = 1;
	int endFilm = films[0].first;
	for (int i = 1; i < numFilms; ++i) {
		if (films[i].second>= endFilm + 10) {
			endFilm = films[i].first;
			++cont;
		}
	}
	std::cout << cont << '\n';

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