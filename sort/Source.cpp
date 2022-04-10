#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<chrono>
#include"Header.h"
//auto begin = std::chrono::high_resolution_clock::now();//запуск таймера
//auto end = std::chrono::high_resolution_clock::now();//конец таймера
//auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);//разница во времени


//printf("The elapsed time is %.6f seconds\n", elapsed.count()*1e-9);



int main() {
	system("mode con cols=134 lines=40");
	srand(time(0));
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	SetCustomization();
	Array mass;
	mass.Size = 0;
	mass.Array = NULL;
	mass.sort = false;

	while (true) {
		menu();

		pointer(mass);
	}
	return 0;
}

















