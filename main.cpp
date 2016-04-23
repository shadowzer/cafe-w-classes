// main.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "headerA.h"

int main()
{
	setlocale(LC_ALL, "RUS");

	Cafe cafe;
	cafe.start();

	system("pause");
	return 0;
}