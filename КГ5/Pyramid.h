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
	//�����������
	Pyramid();
	//����� ������
	double* findCentre(double** mas, int n, int m);
	//�������
	double fill(HDC, double x, double y, double x0);
	//���������
	void Draw(HDC);
	//������������ ������
	double** mm(double** masA, double** masB, int, int, int, int);
	//�����������/���������
	void scale(double Sx, double Sy, double Sz);
	//�������� �� ����
	void turnX(double alpha);
	void turnY(double alpha);
	void turnZ(double alpha);
	void ContourDraw(HDC, POINT* p, int);//��������� �������
	void Hatching(HDC, POINT* p, int);//���������
	void setPlanePyr();//������ ������� ������ ��������
	void equationPlane(int numPlane, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);//������ ��������� ���������
	//�������� �� ������������
	void moveUp(int a);
	void moveDown(int a);
	void moveLeft(int a);
	void moveRight(int a);
	~Pyramid();
};