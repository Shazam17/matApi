#include "pch.h"
#include <iostream>
/*
8
Напишите программу, которая решает систему трех линейных уравнений с тремя
неизвестными матричным методом.
*/
#define Log(x) std::cout << x << std::endl
#define LogLine(x) std::cout << __LINE__ << ' ' << x << std::endl

template<typename T>
class mat {
public:
	T ** arr;
	int sI;
	int sJ;

	mat() {

	}

	mat(int I, int J) : sI(I), sJ(J) {
		this->arr = new T *[I];
		for (int i = 0; i < I; i++) {
			this->arr[i] = new T[J];
		}
		for (int i = 0; i < sI; i++) {
			for (int j = 0; j < sJ; j++) {
				if (i == j) {
					arr[i][j] = 1;
				}
				else {
					arr[i][j] = 0;
				}
			}
		}
	}
	mat(int I) : sI(I), sJ(I) {
		this->arr = new T *[I];
		for (int i = 0; i < I; i++) {
			this->arr[i] = new T[I];
		}
		for (int i = 0; i < sI; i++) {
			for (int j = 0; j < sJ; j++) {
				if (i == j) {
					arr[i][j] = 1;
				}
				else {
					arr[i][j] = 0;
				}
			}
		}
	}

	mat operator= (mat &mt) {
		mat ret(mt.getI(), mt.getJ());
		for (int i = 0; i < mt.getI(); i++) {
			for (int j = 0; j < mt.getJ(); j++) {
				ret[i][j] = mt[i][j];
			}
		}
		return ret;
	}

	int getI() const { return this->sI; }
	int getJ() const { return this->sJ; }


	void show() {
		for (int i = 0; i < sI; i++) {
			for (int j = 0; j < sJ; j++) {
				std::cout << arr[i][j] << ' ';
			}
			std::cout << std::endl;
		}
	}

	T * operator[] (int i) {
		return arr[i];
	}

	void realoc(int row, int col) {
		~mat();
		this->arr = new T *[row];
		for (int i = 0; i < row; i++) {
			arr[i] = new T[col];
		}
	}
	~mat() {
		LogLine("Destructor called");
		for (int i = 0; i < sI; i++) {
			delete[] this->arr[i];
		}
		delete[] this->arr;	
	}
};

template<typename T>
class vec : mat<T> {

public:
	vec(int size) {
		//this->arr = mat<T>(size, 1);
		this->sI = size;
		this->sJ = 1;
	}
	vec(const T * a , int n) {
		this->arr = new T *[1];
		this->arr[0] = new T[n];

		for (int i = 0; i < n; i++) {
			this->arr[0][i] = a[i];
		}
		this->sI = 1;
		this->sJ = n;
	}

};

template<typename T>
T det(mat<T> &mt) {
	if (mt.getI() == mt.getJ()) {
		if (mt.getI() == 3) {
			return (
				mt[0][0] * mt[1][1] * mt[2][2] +
				mt[0][1] * mt[1][2] * mt[2][0] +
				mt[0][2] * mt[1][0] * mt[2][1] -
				mt[0][2] * mt[1][1] * mt[2][0] -
				mt[0][1] * mt[1][0] * mt[2][2] -
				mt[0][0] * mt[1][2] * mt[2][1]);
		}
		if (mt.getI() == 1) {
			return mt[0][0];
		}
		if (mt.getI() == 2) {
			return (mt[0][0] * mt[1][1] - mt[1][0] * mt[0][1]);
		}
	}
}
template<typename T>
T getMinor(mat<T> & mt, int row, int col) {
	if (mt.getI() == mt.getJ()) {
		int s = mt.getI() - 1;
		mat<T> res(s, s);
		int cI = 0;
		int cJ = 0;
		for (int i = 0; i < mt.getI(); i++) {
			for (int j = 0; j < mt.getI(); j++) {
				if (i != row && j != col) {
					res[cI][cJ] = mt[i][j];
					cJ++;
					if (cJ > s - 1) {
						cJ = 0;
						cI++;
					}
				}
			}
		}
		return det(res);
	}
	return NULL;
}


template<typename T>
void matRev(mat<T> & mt) {
	if (mt.getI() != mt.getJ()) {
		return;
	}
	mat<T> ret(mt.getI(), mt.getI());
	T d = det(mt);
	if(d == 0) {
		return;
	}
	for (int i = 0; i < mt.getI(); i++) {
		for (int j = 0; j < mt.getI(); j++) {
			int c;
			if (((i + 1) + (j + 1)) % 2) {
				c = -1;
			}
			else {
				c = 1;
			}
			ret[i][j] = c * (getMinor(mt , i , j) / d);
		}
	}
	for (int i = 0; i < mt.getI(); i++) {
		for (int j = 0; j < mt.getI(); j++) {
			mt[i][j] = ret[i][j];
		}
	}
}

template<typename T>
void transpose(mat<T> &mt) {
	if (mt.getI() != mt.getJ()) {
		for (int i = 0; i < mt.getI(); i++) {
			for (int j = 0; j < mt.getJ(); j++) {

			}
		}
	}
	else {
		if (mt.getI() > 1) {
			for (int i = 1; i < mt.getJ(); i++) {
				for (int j = 0; j < i; j++) {
					T temp = mt[i][j];
					mt[i][j] = mt[j][i];
					mt[j][i] = temp;
				}
			}
		}
	}
}
template<typename T>
void mult(mat<T> *a, mat<T>* b , mat<T>* res) {
	if (a->getI() == b->getI() && a->getJ() == b->getI()) {
		for (int i = 0; i < a->getI(); i++) {
			for (int j = 0; j < b->getJ(); j++) {
				T elem = 0;
				for (int c = 0; c < a.getJ(); c++) {
					elem += a[i][c] * b[c][j];
				}
				res[i][j] = elem;
			}
		}
	}
	
}

template<typename T>
mat<T> multOptim(mat<T> a, mat<T> b) {
	if (a.getI() == b.getI() && a.getJ() == b.getI()) {
		mat<T>(a.getI(), b.getJ());
		
	}
}

int main() {
	mat<int> mt(3, 3);
	matRev(mt);
	mat<int> res(3);
	mult(&mt, &mt, &res);
	res.show();

}