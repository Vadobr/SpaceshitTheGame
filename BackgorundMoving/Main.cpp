#include <iostream>
#include <conio.h>
#include <Windows.h>

int main() {

	int a = 0;

	while (!_kbhit()) {

		system("cls");

		for (int i(0); i < 80; i++) {

			if (i == a)
				std::cout << "0";
			else
				std::cout << "=";

		}

		a++;

		if (a == 80)
			a = 0;

		Sleep(20);

	}

	return 0;

}