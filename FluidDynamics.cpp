// FluidDynamics.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <Windows.h>
#include <iostream>
#include <string>

#include "World.h"

#define WIDTH 80
#define HEIGHT 20


void consoleRender(const Vecf2 prevPartsPos[PART_NUM], const Vecf2 partsPos[PART_NUM])
{
	static CHAR_INFO* chiBuffer = new CHAR_INFO[WIDTH * HEIGHT]{};
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coordBufSize{ WIDTH, HEIGHT };
	COORD coordBufCoord{ 0, 0 };
	SMALL_RECT srctWriteRect{ 0, 0, WIDTH, HEIGHT };

	for (int i(0); i < PART_NUM; ++i) {
		SHORT pos = SHORT(VIEW_HEIGHT - partsPos[i].y - 1) / 30 * WIDTH + SHORT(partsPos[i].x / 10);
		chiBuffer[pos].Char.UnicodeChar = L'@';
		chiBuffer[pos].Attributes = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
	}

	WriteConsoleOutput(output,
		chiBuffer,        // buffer to copy from
		coordBufSize,     // col-row size of chiBuffer
		coordBufCoord,    // top left src cell in chiBuffer
		&srctWriteRect);  // dest. screen buffer rectangle

	ZeroMemory(chiBuffer, WIDTH * HEIGHT * sizeof(CHAR_INFO));
}


int main()
{
	SMALL_RECT windowSize{ 0,0,WIDTH-1,HEIGHT-1 };
	COORD screenSize = { WIDTH,HEIGHT };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), screenSize);

	World w(consoleRender);
	w.render();
	Sleep(5000);

	while (true)
	{
		w.update();
		w.render();
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
