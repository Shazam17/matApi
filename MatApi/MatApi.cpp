﻿/*
8
Напишите программу, которая решает систему трех линейных уравнений с тремя
неизвестными матричным методом.
*/
#include "pch.h"
#include <iostream>

#define Log(x) std::cout << x << std::endl

template<typename T>
class mat {
private:
	T ** arr;
	int sI;
	int sJ;
public:
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

	T get(int i, int j) {
		return arr[i][j];
	}

	~mat() {
		for (int i = 0; i < sI; i++) {
			delete[] this->arr[i];
		}
		delete[] this->arr;
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
		res.show();
		return det(res);
	}
	return NULL;
}


template<typename T>
mat<T> matRev(mat<T> mt) {
	mat<T> ret;
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

int main() {
	mat<int> mt(3, 3);

	std::cout << det(mt) << std::endl;


	return 0;
}