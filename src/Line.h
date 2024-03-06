#pragma once
#include<Windows.h>
#include"Point.h"

class Line {
private:
	Point pi, pf;	//Ponto inicial e ponto final

public:
	Line ();
	Line (Point p1, Point p2);

	void Draw (HWND wndId, long color);		//Desenhar a linha na janela
	double GetLength ();					//Obter o tamanho da linha
};

