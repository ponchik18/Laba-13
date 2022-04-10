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
#define CLEAN system("cls"); // îò÷èñòêà êîíñîëè
#define PAUSE system("pause");
#define ClEANCONSOLE std::cin.clear(); std::cin.ignore(32767, '\n');

typedef struct Student
{
	char* FirstName; // ÈÌß
	char* LastName; // ÔÀÌÈËÈß
	char* Surname; // ÎÒ×ÅÑÒÂÎ
	int GroupeNumber; // ÍÎÌÅĞ ÃĞÓÏÏÛ
	int Marks[5]; // ÓÑÏÅÂÀÅÌÎÑÒÜ
}Student;
typedef struct studentArray {
	struct Student* mass;
	int count;
	bool GroupeNumberSort;
}STUDENT;
extern void menu();
extern void pointer(STUDENT* mass);
extern void SetCustomization();


