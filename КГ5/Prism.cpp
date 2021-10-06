#pragma once
#include"Prism.h"

Prism::Prism() {
	prism = new double* [6];
	for (int i = 0; i < 6; i++) {
		prism[i] = new double[4];
	}
	//             x				  y				     z
	prism[0][0] = 450, prism[0][1] = 350, prism[0][2] = 200, prism[0][3] = 1;//перед верх
	prism[1][0] = 450, prism[1][1] = 450, prism[1][2] = 200, prism[1][3] = 1;//перед низ
	prism[2][0] = 400, prism[2][1] = 400, prism[2][2] = 300, prism[2][3] = 1;//лево низ
	prism[3][0] = 400, prism[3][1] = 300, prism[3][2] = 300, prism[3][3] = 1;//лево верх
	prism[4][0] = 500, prism[4][1] = 300, prism[4][2] = 300, prism[4][3] = 1;//право верх
	prism[5][0] = 500, prism[5][1] = 400, prism[5][2] = 300, prism[5][3] = 1;//право низ
}

void Prism::Draw(HDC hdc) {
	//структуры 2d фигур призмы
	POINT kv2[4] = { {prism[0][0],prism[0][1] },
					{prism[1][0],prism[1][1] },
					{prism[2][0],prism[2][1] },//левый прямоугольник
					{prism[3][0],prism[3][1] } };//1
	POINT kv3[4] = { {prism[0][0],prism[0][1] },
					{prism[1][0],prism[1][1] },
					{prism[5][0],prism[5][1] },//правый прямоугольник
					{prism[4][0],prism[4][1] } };//2
	POINT kv4[4] = { {prism[2][0],prism[2][1] },
					{prism[3][0],prism[3][1] },
					{prism[4][0],prism[4][1] },//задний прямоугольник
					{prism[5][0],prism[5][1] } };//3
	POINT tr5[3] = { {prism[1][0],prism[1][1] },
					{prism[2][0],prism[2][1] },//нижний треугольник
					{prism[5][0],prism[5][1] } };//4
	POINT tr6[3] = { {prism[0][0],prism[0][1] },
					{prism[3][0],prism[3][1] },//верхний треугольник
					{prism[4][0],prism[4][1] } };//5

	setPlanePrism();
	double c[5]{}; //результирующая матрица переменожения вектора взгляда и матрицы объема фигуры
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			c[i] += e[j] * res[j][i + 5];
		}
	}
	for (int i = 0; i < 5; i++) {
		if (c[i] > 0) {
			switch (i) {
			case 0:
				ContourDraw(hdc, kv2, 4);
				break;
			case 1:
				ContourDraw(hdc, kv3, 4);
				break;
			case 2:
				ContourDraw(hdc, kv4, 4);
				break;
			case 3:
				ContourDraw(hdc, tr5, 3);
				break;
			case 4:
				ContourDraw(hdc, tr6, 3);
				break;
			default:
				continue;
			}
		}
	}
}

void Prism::scale(double Sx, double Sy, double Sz) {
	double** scale = new double* [4];
	for (int i = 0; i < 4; i++)
	{
		scale[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(prism, 6, 3);

	scale[0][0] = Sx, scale[0][1] = 0, scale[0][2] = 0, scale[0][3] = 0;
	scale[1][0] = 0, scale[1][1] = Sy, scale[1][2] = 0, scale[1][3] = 0;
	scale[2][0] = 0, scale[2][1] = 0, scale[2][2] = Sz, scale[2][3] = 0;
	scale[3][0] = c[0] * (1 - Sx), scale[3][1] = c[1] * (1 - Sy), scale[3][2] = c[2] * (1 - Sz), scale[3][3] = 1;

	prism = mm(prism, scale, 6, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] scale[i];
	}
	delete[] scale, c;
}

void Prism::turnX(double alpha) {
	double** angle = new double* [4];
	for (int i = 0; i < 4; i++)
	{
		angle[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(prism, 6, 3);

	angle[0][0] = cos(alpha * P / 180), angle[0][1] = sin(alpha * P / 180), angle[0][2] = 0, angle[0][3] = 0;
	angle[1][0] = -sin(alpha * P / 180), angle[1][1] = cos(alpha * P / 180), angle[1][2] = 0, angle[1][3] = 0;
	angle[2][0] = 0, angle[2][1] = 0, angle[2][2] = 1, angle[2][3] = 0;
	angle[3][0] = c[0] * (1 - cos(alpha * P / 180)) + c[1] * sin(alpha * P / 180), angle[3][1] = c[0] * (1 - cos(alpha * P / 180)) - c[1] * sin(alpha * P / 180), angle[3][2] = 0, angle[3][3] = 1;

	prism = mm(prism, angle, 6, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] angle[i];
	}
	delete[] angle, c;
}

void Prism::turnY(double alpha) {
	double** angle = new double* [4];
	for (int i = 0; i < 4; i++)
	{
		angle[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(prism, 6, 3);

	angle[0][0] = cos(alpha * P / 180), angle[0][1] = 0, angle[0][2] = sin(alpha * P / 180), angle[0][3] = 0;
	angle[1][0] = 0, angle[1][1] = 1, angle[1][2] = 0, angle[1][3] = 0;
	angle[2][0] = -sin(alpha * P / 180), angle[2][1] = 0, angle[2][2] = cos(alpha * P / 180), angle[2][3] = 0;
	angle[3][0] = c[0] * (1 - cos(alpha * P / 180)) + c[2] * sin(alpha * P / 180), angle[3][1] = 0, angle[3][2] = c[2] * (1 - cos(alpha * P / 180)) - c[0] * sin(alpha * P / 180), angle[3][3] = 1;

	prism = mm(prism, angle, 6, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] angle[i];
	}
	delete[] angle, c;
}

void Prism::turnZ(double alpha) {
	double** angle = new double* [4];
	for (int i = 0; i < 4; i++)
	{
		angle[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(prism, 6, 3);

	angle[0][0] = 1, angle[0][1] = 0, angle[0][2] = 0, angle[0][3] = 0;
	angle[1][0] = 0, angle[1][1] = cos(alpha * P / 180), angle[1][2] = sin(alpha * P / 180), angle[1][3] = 0;
	angle[2][0] = 0, angle[2][1] = -sin(alpha * P / 180), angle[2][2] = cos(alpha * P / 180), angle[2][3] = 0;
	angle[3][0] = 0, angle[3][1] = c[1] * (1 - cos(alpha * P / 180)) + c[2] * sin(alpha * P / 180), angle[3][2] = c[2] * (1 - cos(alpha * P / 180)) - c[1] * sin(alpha * P / 180), angle[3][3] = 1;

	prism = mm(prism, angle, 6, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] angle[i];
	}
	delete[] angle, c;
}

void Prism::setPlanePrism() {
	Pyramid::equationPlane(5, prism[0][0], prism[0][1], prism[0][2], prism[1][0], prism[1][1], prism[1][2], prism[2][0], prism[2][1], prism[2][2]);
	Pyramid::equationPlane(6, prism[0][0], prism[0][1], prism[0][2], prism[5][0], prism[5][1], prism[5][2], prism[1][0], prism[1][1], prism[1][2]);
	Pyramid::equationPlane(7, prism[2][0], prism[2][1], prism[2][2], prism[4][0], prism[4][1], prism[4][2], prism[3][0], prism[3][1], prism[3][2]);
	Pyramid::equationPlane(8, prism[1][0], prism[1][1], prism[1][2], prism[5][0], prism[5][1], prism[5][2], prism[2][0], prism[2][1], prism[2][2]);
	Pyramid::equationPlane(9, prism[0][0], prism[0][1], prism[0][2], prism[3][0], prism[3][1], prism[3][2], prism[4][0], prism[4][1], prism[4][2]);
}

void Prism::moveUp(int a) {
	for (int i = 0; i < 6; i++) {
		prism[i][1] -= a;
	}
}

void Prism::moveDown(int a) {
	for (int i = 0; i < 6; i++) {
		prism[i][1] += a;
	}
}

void Prism::moveLeft(int a) {
	for (int i = 0; i < 6; i++) {
		prism[i][0] -= a;
	}
}

void Prism::moveRight(int a) {
	for (int i = 0; i < 6; i++) {
		prism[i][0] += a;
	}
}

Prism::~Prism() {
	for (int i = 0; i < 4; i++) {
		delete[] Prism::prism[i];
	}
	delete[] Prism::prism;
}