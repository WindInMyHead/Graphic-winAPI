#pragma comment(linker, "/STACK:99999999")
#include "Pyramid.h"
#include<stack>

double res[4][10] = {};
double e[4] = { 0, 0, 1, 0 };

Pyramid::Pyramid() {
	pyramid = new double* [5];
	for (int i = 0; i < 5; i++) {
		pyramid[i] = new double[4];
	}
	//               x				      y				       z
	pyramid[0][0] = 150, pyramid[0][1] = 350, pyramid[0][2] = 200, pyramid[0][3] = 1;//перед
	pyramid[1][0] = 100, pyramid[1][1] = 400, pyramid[1][2] = 300, pyramid[1][3] = 1;//лево низ
	pyramid[2][0] = 100, pyramid[2][1] = 300, pyramid[2][2] = 300, pyramid[2][3] = 1;//лево верх
	pyramid[3][0] = 200, pyramid[3][1] = 300, pyramid[3][2] = 300, pyramid[3][3] = 1;//право верх
	pyramid[4][0] = 200, pyramid[4][1] = 400, pyramid[4][2] = 300, pyramid[4][3] = 1;//право низ

}

double* Pyramid::findCentre(double** mas, int n, int m) {
	double* centre = new double[3];
	for (int i = 0; i < m; i++) {
		centre[i] = 0;
		for (int j = 0; j < n; j++) {
			centre[i] += mas[j][i];
		}
		centre[i] = centre[i] / n;
	}
	return centre;
}

void Pyramid::Draw(HDC hdc) {
	//структуры 2d фигур пирамиды
	POINT tr1[3] = { {pyramid[0][0],pyramid[0][1]},
					{pyramid[1][0],pyramid[1][1] },//левый треугольник
					{pyramid[2][0],pyramid[2][1] } };//1
	POINT tr2[3] = { {pyramid[0][0],pyramid[0][1] },
					{pyramid[4][0],pyramid[4][1] },//правый треугольник
					{pyramid[3][0],pyramid[3][1] } };//2
	POINT kv1[4] = { {pyramid[1][0],pyramid[1][1] },
					{pyramid[2][0],pyramid[2][1] },
					{pyramid[3][0],pyramid[3][1] },//основание
					{pyramid[4][0],pyramid[4][1] } };//3
	POINT tr3[3] = { {pyramid[0][0],pyramid[0][1] },
					{pyramid[1][0],pyramid[1][1] },//нижний треугольник
					{pyramid[4][0],pyramid[4][1] } };//4
	POINT tr4[3] = { {pyramid[0][0],pyramid[0][1] },
					{pyramid[2][0],pyramid[2][1] },//верхний треугольник
					{pyramid[3][0],pyramid[3][1] } };//5

	setPlanePyr(); //задание матрицы объема фигуры(уравнения плоскостей)
	double c[5]{}; //результирующая матрица переменожения вектора взгляда и матрицы объема фигуры
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			c[i] += e[j] * res[j][i];
		}
	}
	for (int i = 0; i < 5; i++) {
		if (c[i] > 0) {
			switch (i) {
			case 0:
				ContourDraw(hdc, tr1,3);
				//Hatching(hdc, tr1, 3);
				break;
			case 1:
				ContourDraw(hdc, tr2, 3);
				//Hatching(hdc, tr2, 3);
				break;
			case 2:
				ContourDraw(hdc, kv1, 4);
				//Hatching(hdc, kv1, 4);
				break;
			case 3:
				ContourDraw(hdc, tr3, 3);
				//Hatching(hdc, tr3, 3);
				break;
			case 4:
				ContourDraw(hdc, tr4, 3);
				//Hatching(hdc, tr4, 3);
				break;
			default:
				continue;
			}
		}
	}
}

double** Pyramid::mm(double** masA, double **masB, int n1, int m1, int n2, int m2) {
	int max = m1;
	if (n1 > m1) max = n1;
	if (n2 > m1) max = n2;
	if (m2 > m1) max = m1;
	double** mulRes = new double* [max];
	for (int i = 0; i < max; i++)
	{
		mulRes[i] = new double[max];
	}

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m2; j++) {
			mulRes[i][j] = 0;
			for (int k = 0; k < m1; k++) {
				mulRes[i][j] += (masA[i][k] * masB[k][j]);
			}
		}
	}

	for (int i = 0; i < m1; i++) {
		delete[] masA[i];
	}
	delete[] masA;
	return mulRes;
}

void Pyramid::scale(double Sx, double Sy, double Sz){
	double** scale = new double*[4];
	for (int i = 0; i < 4; i++)
	{
		scale[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(pyramid, 5, 3);
	
	scale[0][0] = Sx, scale[0][1] = 0,  scale[0][2] = 0, scale[0][3] = 0;
	scale[1][0] = 0,  scale[1][1] = Sy, scale[1][2] = 0, scale[1][3] = 0;
	scale[2][0] = 0,  scale[2][1] = 0,  scale[2][2] = Sz, scale[2][3] = 0;
	scale[3][0] = c[0] * (1 - Sx), scale[3][1] = c[1] * (1 - Sy), scale[3][2] = c[2] * (1 - Sz), scale[3][3] = 1;
	pyramid = mm(pyramid, scale, 5, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] scale[i];
	}
	delete[] scale, c;
}

void Pyramid::turnX(double alpha){
	double** angle = new double*[4];
	for (int i = 0; i < 4; i++)
	{
		angle[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(pyramid, 5, 3);

	angle[0][0] = cos(alpha * P / 180), angle[0][1] = sin(alpha * P / 180), angle[0][2] = 0, angle[0][3] = 0;
	angle[1][0] = -sin(alpha * P / 180), angle[1][1] = cos(alpha * P / 180), angle[1][2] = 0, angle[1][3] = 0;
	angle[2][0] = 0, angle[2][1] = 0, angle[2][2] = 1, angle[2][3] = 0;
	angle[3][0] = c[0] * (1 - cos(alpha * P /180)) + c[1] * sin(alpha * P / 180), angle[3][1] = c[0] * (1 - cos(alpha * P / 180)) - c[1] * sin(alpha * P / 180), angle[3][2] = 0, angle[3][3] = 1;
	pyramid = mm(pyramid, angle, 5, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] angle[i];
	}
	delete[] angle, c;
}

void Pyramid::turnY(double alpha){
	double** angle = new double* [4];
	for (int i = 0; i < 4; i++)
	{
		angle[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(pyramid, 5, 3);

	angle[0][0] = cos(alpha * P / 180), angle[0][1] = 0, angle[0][2] = sin(alpha * P / 180), angle[0][3] = 0;
	angle[1][0] = 0, angle[1][1] = 1, angle[1][2] = 0, angle[1][3] = 0;
	angle[2][0] = -sin(alpha * P / 180), angle[2][1] = 0, angle[2][2] = cos(alpha * P / 180), angle[2][3] = 0;
	angle[3][0] = c[0] * (1 - cos(alpha * P / 180)) + c[2] * sin(alpha * P / 180), angle[3][1] = 0, angle[3][2] = c[2] * (1 - cos(alpha * P / 180)) - c[0] * sin(alpha * P / 180), angle[3][3] = 1;
	pyramid = mm(pyramid, angle, 5, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] angle[i];
	}
	delete[] angle, c;
}

void Pyramid::turnZ(double alpha){
	double** angle = new double*[4];
	for (int i = 0; i < 4; i++)
	{
		angle[i] = new double[4];
	}

	double* c = new double[3];
	c = findCentre(pyramid, 5, 3);

	angle[0][0] = 1, angle[0][1] = 0, angle[0][2] = 0, angle[0][3] = 0;
	angle[1][0] = 0, angle[1][1] = cos(alpha * P / 180), angle[1][2] = sin(alpha * P / 180), angle[1][3] = 0;
	angle[2][0] = 0, angle[2][1] = -sin(alpha * P / 180), angle[2][2] = cos(alpha * P / 180), angle[2][3] = 0;
	angle[3][0] = 0, angle[3][1] = c[1] * (1 - cos(alpha * P / 180)) + c[2] * sin(alpha * P / 180), angle[3][2] = c[2] * (1 - cos(alpha * P / 180)) - c[1] * sin(alpha * P / 180), angle[3][3] = 1;
	pyramid = mm(pyramid, angle, 5, 4, 4, 4);

	for (int i = 0; i < 4; i++) {
		delete[] angle[i];
	}
	delete[] angle, c;
}

void Pyramid::ContourDraw(HDC hdc, POINT* p, int n) {
	MoveToEx(hdc, p[0].x, p[0].y, NULL);
	for (int i = 0; i < n; i++) {
		LineTo(hdc, p[i].x, p[i].y);
	}
	LineTo(hdc, p[0].x, p[0].y);
}

double Pyramid::fill(HDC hdc, double x, double y, double x0) {
	double xleft;
	while (GetPixel(hdc, x - 1, y) != 0) {
		SetPixel(hdc, x, y, 0x0000FF00);
		x--;
	}
	xleft = x;
	x = x0 + 1;
	while (GetPixel(hdc, x, y) != 0) {
		SetPixel(hdc, x, y, 0x0000FF00);
		x++;
	}
	return xleft;
}

void Pyramid::Hatching(HDC hdc, POINT* p, int n) {
	POINT dot{};
	for (int i = 0; i < n; i++) {
		dot.x += p[i].x;
		dot.y += p[i].y;
	}
	dot.x /= n; dot.y /= n;
	stack<POINT>stk;
	stk.push(dot);
	double x = dot.x, y = dot.y;
	while (!stk.empty()) {
		x = stk.top().x, y = stk.top().y;
		stk.pop();

		if (GetPixel(hdc, x - 1, y) != 0 && GetPixel(hdc, x - 1, y) != 65280) {//точка слева
			SetPixel(hdc, x - 1, y, 0x0000FF00);
			dot.x = x - 1;
			dot.y = y;
			stk.push(dot);
		}

		if (GetPixel(hdc, x + 1, y) != 0 && GetPixel(hdc, x + 1, y) != 65280) {//точка справа
			SetPixel(hdc, x + 1, y, 0x0000FF00);
			dot.x = x + 1;
			dot.y = y;
			stk.push(dot);
		}

		if (GetPixel(hdc, x, y - 1) != 0 && GetPixel(hdc, x, y - 1) != 65280) {//точка сверху
			SetPixel(hdc, x, y - 1, 0x0000FF00);
			dot.x = x;
			dot.y = y - 1;
			stk.push(dot);
		}

		if (GetPixel(hdc, x, y + 1) != 0 && GetPixel(hdc, x, y + 1) != 65280) {//точка снизу
			SetPixel(hdc, x, y + 1, 0x0000FF00);
			dot.x = x;
			dot.y = y + 1;
			stk.push(dot);
		}
	}
}
	
void Pyramid::setPlanePyr() {
	equationPlane(0, pyramid[0][0], pyramid[0][1], pyramid[0][2], pyramid[1][0], pyramid[1][1], pyramid[1][2], pyramid[2][0], pyramid[2][1], pyramid[2][2]);
	equationPlane(1, pyramid[0][0], pyramid[0][1], pyramid[0][2], pyramid[3][0], pyramid[3][1], pyramid[3][2], pyramid[4][0], pyramid[4][1], pyramid[4][2]);
	equationPlane(2, pyramid[1][0], pyramid[1][1], pyramid[1][2], pyramid[3][0], pyramid[3][1], pyramid[3][2], pyramid[2][0], pyramid[2][1], pyramid[2][2]);
	equationPlane(3, pyramid[0][0], pyramid[0][1], pyramid[0][2], pyramid[4][0], pyramid[4][1], pyramid[4][2], pyramid[1][0], pyramid[1][1], pyramid[1][2]);
	equationPlane(4, pyramid[0][0], pyramid[0][1], pyramid[0][2], pyramid[2][0], pyramid[2][1], pyramid[2][2], pyramid[3][0], pyramid[3][1], pyramid[3][2]);
}

void Pyramid::equationPlane(int numPlane, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
	res[0][numPlane] = ((y2 - y1) * (z3 - z1) - (y3 - y1) * (z2 - z1))/100;
	res[1][numPlane] = ((x3 - x1) * (z2 - z1) - (x2 - x1) * (z3 - z1)) / 100;
	res[2][numPlane] = ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / 100;
	res[3][numPlane] = ((res[0][numPlane] * x1 + res[1][numPlane] * y1 + res[2][numPlane] * z1)) / 100;
}

void Pyramid::moveUp(int a) {
	for (int i = 0; i < 5; i++) {
		pyramid[i][1] -= a;
	}
}

void Pyramid::moveDown(int a) {
	for (int i = 0; i < 5; i++) {
		pyramid[i][1] += a;
	}
}

void Pyramid::moveLeft(int a) {
	for (int i = 0; i < 5; i++) {
		pyramid[i][0] -= a;
	}
}

void Pyramid::moveRight(int a) {
	for (int i = 0; i < 5; i++) {
		pyramid[i][0] += a;
	}
}

Pyramid::~Pyramid(){
	for (int i = 0; i < 4; i++) {
		delete[] Pyramid::pyramid[i];
	}
	delete[] Pyramid::pyramid;
}


//while (!stk.empty()) {
	//		dot.x = fill(hdc, stk.top().x, stk.top().y, dot.x);//заливка линии
	//		dot.y = stk.top().y + 1;// переходим к строке нижe
	//		stk.pop();//чистим стек
	//		while (GetPixel(hdc, dot.x, dot.y+1) != 0) {
	//			while (GetPixel(hdc, dot.x + 1, dot.y + 1) != 0) {//крайний правый незакрашенный пиксель в строке ниже
	//				dot.x++;
	//			}
	//			stk.push(dot);
	//			dot.y++;//следующая строка
	//		}
	//	}
	//}