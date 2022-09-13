// Hoja 6 Ejercicio 2 Jorge del Valle Vazquez

// Ejercicio 2. Dado un vector V[1. ..n] de números enteros mayores que 0, diseña un algoritmo
// que encuentre un subconjunto de suma C >0 de cardinal mínimo.


// Equivalente al problema de las monedas sin repeticion de estas.

// suma(i, j) := cardinal de enteros entre 1 e i que suman j

//suma(i, j) =	suma(i − 1, j)										si V[i] > j		sumar sin considerar el elemento i
//				min(suma(i − 1, j), suma(i − 1, j − v[i]) + 1)		si V[i] ≤ j		min entre sumar sin considerar oconsiderando


// suma(i, 0) = 0 0 ≤ i ≤ n.
// suma(0, j) = +∞ 1 ≤ j ≤ C.

// se depende de arriba y arriba a la izda por lo que se puede ir sobreescribiendo en un vector de derecha a izda

// tiempo  O(n ∗ C) 
// espacio O(C)

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

vector<int> subcjtosumcardmin(vector<int> const & v, int C) {//v(0...n-1)
	vector<int> suma(C + 1);// suma(i) representa el cardinal del subcjto min que suma i
	suma[0] = 0;
	for (size_t i = 1; i <= C; ++i)//suma(0,j)=+∞ 1 ≤ j ≤ C.
	{
		suma[i] = 1000000;//INT_MAX da problemas con std::min
	}
	for (size_t i = 0; i < v.size(); ++i)
	{
		for (size_t j = C; j >= v[i]; --j){//de dcha a izqda
			suma[j] = min(suma[j], suma[j - v[i]] + 1);
		}
	}

	vector<int> subconjunto;
	int i = v.size()-1, j = C;
	while (i >= 0 && j > 0) {
		if (v[i] <= j && suma[j] == (1 + suma[j - v[i]])){
			subconjunto.push_back(v[i]);
			j = j - v[i];
		}
	--i;
	}
	return subconjunto;
}
int main() {
	int C = 10;
	vector<int> v = { 2,3,4,5,6 };
	vector<int> sol = subcjtosumcardmin(v, C);
	for (size_t i = 0; i < sol.size(); ++i)
	{
		cout << sol[i] << ' ';
	}
	system("PAUSE");
	return 0;
}
/*
	0	1	2	3	4	5	6	7	8	9	10
0	0	f	f	f	f	f	f	f	f	f	f		{}
1	0	f	1	f	f	f	f	f	f	f	f		{2}
2	0	f	1	1	f	2	f	f	f	f	f		{2,3}
3	0	f	1	1	1	2	2	2	f	3	f		{2,3,4}
4	0	f	1	1	1	1	2	2	2	2	3		{2,3,4,5}
5	0	f	1	1	1	1	1	2	2	2	2		{2,3,4,5,6}

*/