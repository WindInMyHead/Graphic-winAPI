#pragma once
#include<iostream>
#include<Windows.h>

using namespace std;

#define M 4
#define N 5
#define P 3.141592653589793

extern double res[4][10];
extern double e[4];

class Pyramid {
private:
	double** pyramid;
public:
	//конструктор
	Pyramid();
	//поиск центра
	double* findCentre(double** mas, int n, int m);
	//заливка
	double fill(HDC, double x, double y, double x0);
	//рисование
	void Draw(HDC);
	//перемножение матриц
	double** mm(double** masA, double** masB, int, int, int, int);
	//приближение/отдаление
	void scale(double Sx, double Sy, double Sz);
	//вращение по осям
	void turnX(double alpha);
	void turnY(double alpha);
	void turnZ(double alpha);
	void ContourDraw(HDC, POINT* p, int);//рисование контура
	void Hatching(HDC, POINT* p, int);//штриховка
	void setPlanePyr();//задать матрицу объема пирамиды
	void equationPlane(int numPlane, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);//задать уравнение плоскости
	//движение по направлениям
	void moveUp(int a);
	void moveDown(int a);
	void moveLeft(int a);
	void moveRight(int a);
	~Pyramid();
};