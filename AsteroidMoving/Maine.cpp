#include <iostream>
#include <conio.h>

int main() {
	

	for (int j(0); j < 100; j++) {
		for (int i(0); i < 80; i++) {
			std::cout << ' ';
		}
		std::cout << std::endl;
	}

	while (!_kbhit()) {

		for (int i(0); i < 80; i++) {

			if (rand() % 80 == i)
				std::cout << '*';
			else
				std::cout << ' ';

		}

	}

	return 0;
}