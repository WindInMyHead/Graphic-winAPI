#pragma once
#include"Pyramid.h"

class Prism : public Pyramid {
private:
	double** prism;
public:
	Prism();
	void Draw(HDC);//���������
	//�����������/���������
	void scale(double Sx, double Sy, double Sz);
	//�������� �� ����
	void turnX(double alpha);
	void turnY(double alpha);
	void turnZ(double alpha);
	void setPlanePrism();//������ ������� ������ ������
	//�������� �� ������������
	void moveUp(int a);
	void moveDown(int a);
	void moveLeft(int a);
	void moveRight(int a);
	~Prism();
};