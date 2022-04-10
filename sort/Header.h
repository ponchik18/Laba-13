#pragma once
#include<stdio.h>
#include<locale>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<chrono>
#define UP 72
#define DOWN 80
#define ENTRY 13
#define ESC 27
#define CLEAN system("cls"); // отчистка консоли
#define PAUSE system("pause");
extern void menu();
extern void SetCustomization();
typedef struct Array {
	int* Array;
	int Size;
	bool sort;
}Array;
extern void pointer(Array & mass);