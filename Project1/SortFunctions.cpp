#include"Header.h"
#include<iostream>

//Сортировки!!!
void swap(Student* a, Student* b);
void BubbleSort(STUDENT *mass)
{
	int flag = 1;
	for (int i = 0; (i < mass->count) && (flag == 1); i++) {
		flag = 0;
		for (int j = 0; j < mass->count - 1; j++) {
			if (strcmp(mass->mass[j].FirstName, mass->mass[j+1].FirstName)>0) {
				swap(&mass->mass[j], &mass->mass[j + 1]);
				flag = 1;
			}
		}
	}
	mass->GroupeNumberSort = true;
}
void SelectionSort(STUDENT* mass) {
	for (int i = 0; i < mass->count; i++) {
		for (int j = i + 1; j < mass->count; j++) {
			if (strcmp(mass->mass[i].LastName, mass->mass[j].LastName) > 0) {
				swap(&mass->mass[i], &mass->mass[j]);
			}
		}
	}
}
void InsertionSort(STUDENT* mass)
{
	for (int TransactionElement = 1; TransactionElement < mass->count; TransactionElement++) {
		if (strcmp(mass->mass[TransactionElement].Surname ,mass->mass[TransactionElement - 1].Surname)>0) {
			Student tmp;
			tmp.FirstName=mass->mass[TransactionElement].FirstName;
			tmp.LastName = mass->mass[TransactionElement].LastName;
			tmp.Surname = mass->mass[TransactionElement].Surname;
			tmp.GroupeNumber = mass->mass[TransactionElement].GroupeNumber;
			for (int i = 0; i < 5; i++) {
				tmp.Marks[i] = mass->mass[TransactionElement].Marks[i];
			}
			int location = TransactionElement;
			do {
				mass->mass[location] = mass->mass[location - 1];
				location--;
			} while (location > 0 && strcmp(mass->mass[location - 1].Surname,tmp.Surname)>0);
			mass->mass[location] = tmp;
			mass->mass[location].FirstName = tmp.FirstName;
			mass->mass[location].LastName = tmp.LastName;
			mass->mass[location].Surname = tmp.Surname;
			mass->mass[location].GroupeNumber = tmp.GroupeNumber;
			for (int i = 0; i < 5; i++) {
				mass->mass[location].Marks[i] = tmp.Marks[i];
			}
		}
	}
}

/////////////QUICKSORT////////////
int partition(STUDENT& mass, int first, int last) {
	int pivot;
	int smallIndex;
	swap(&mass.mass[first], &mass.mass[(first + last) / 2]);
	pivot = mass.mass[first].GroupeNumber;
	smallIndex = first;
	for (int index = first + 1; index <= last; index++) {
		if (mass.mass[index].GroupeNumber < pivot)
		{
			smallIndex++;
			swap(&mass.mass[smallIndex], &mass.mass[index]);
		}
	}
	swap(&mass.mass[first], &mass.mass[smallIndex]);
	return smallIndex;
}
void recQuickSort(STUDENT& mass, int first, int last) {
	if (first < last) {
		int pivotLocation = partition(mass, first, last);
		recQuickSort(mass, first, pivotLocation - 1);
		recQuickSort(mass, pivotLocation + 1, last);
	}
}
void QuickSort(STUDENT* mass) {
	recQuickSort(*mass, 0, mass->count - 1);
	mass->GroupeNumberSort = true;
}
//////////////END QUICKSORT////////

void ShellSort(STUDENT* mass) {
	int i, j, step;
	Student tmp;
	for (step = mass->count / 2; step > 0; step /= 2) {
		for (i = step; i < mass->count; i++) {
			tmp.FirstName = mass->mass[i].FirstName;
			tmp.LastName = mass->mass[i].LastName;
			tmp.Surname = mass->mass[i].Surname;
			tmp.GroupeNumber = mass->mass[i].GroupeNumber;
			for (int a = 0; a < 5; a++) {
				tmp.Marks[a] = mass->mass[i].Marks[a];
			}
			for (j = i; j >= step; j -= step) {
				if (strcmp(mass->mass[j - step].FirstName, tmp.FirstName) > 0) {
					mass->mass[j].FirstName = mass->mass[j - step].FirstName;
					mass->mass[j].GroupeNumber = mass->mass[j - step].GroupeNumber;
					mass->mass[j].LastName = mass->mass[j - step].LastName;
					mass->mass[j].Surname = mass->mass[j - step].Surname;
					for (int a = 0; a < 5; a++) {
						mass->mass[j].Marks[a] = mass->mass[j - step].Marks[a];
					}
				}
				else
					break;
			}
			mass->mass[j].FirstName = tmp.FirstName;
			mass->mass[j].LastName = tmp.LastName;
			mass->mass[j].Surname = tmp.Surname;
			mass->mass[j].GroupeNumber = tmp.GroupeNumber;
			for (int a = 0; a < 5; a++) {
				mass->mass[j].Marks[a] = tmp.Marks[a];
			}



		}
	}
}

//////////MERGE SORT///////////////////
void merge(STUDENT& mass, int first, int last, int m) {
	if (first >= last || m<first || m>last) return;
	if (last == first + 1 && strcmp(mass.mass[first].LastName, mass.mass[last].LastName)>0) {
		swap(&mass.mass[first], &mass.mass[last]);
		return;
	}
	Student* tmp = new Student[last - first + 1];
	for (int i = first, j = 0; i <= last; i++, j++) {
		tmp[j].FirstName = new char[strlen(mass.mass[i].FirstName)+1];
		tmp[j].LastName = new char[strlen(mass.mass[i].LastName) + 1];
		tmp[j].Surname = new char[strlen(mass.mass[i].Surname) + 1];
		strcpy(tmp[j].FirstName, mass.mass[i].FirstName);
		strcpy(tmp[j].LastName, mass.mass[i].LastName);
		strcpy(tmp[j].Surname, mass.mass[i].Surname);
		tmp[j].GroupeNumber = mass.mass[i].GroupeNumber;
		for (int a = 0; a < 5; a++) {
			tmp[j].Marks[a] = mass.mass[i].Marks[a];
		}
	}
	for (int i = first, j = 0, k = m - first + 1; i <= last; ++i) {
		if (j > m - first) {

			strcpy(mass.mass[i].FirstName, tmp[k].FirstName);
			strcpy(mass.mass[i].LastName, tmp[k].LastName);
			strcpy(mass.mass[i].Surname, tmp[k].Surname);
			mass.mass[i].GroupeNumber = tmp[k].GroupeNumber;
			mass.mass[i].Surname = tmp[k].Surname;
			for (int a = 0; a < 5; a++) {
				mass.mass[i].Marks[a] = tmp[k].Marks[a];
			}
			k++;
		}
		else if (k > last - first) {

			strcpy(mass.mass[i].FirstName, tmp[j].FirstName);
			strcpy(mass.mass[i].LastName, tmp[j].LastName);
			strcpy(mass.mass[i].Surname, tmp[j].Surname);
			mass.mass[i].GroupeNumber = tmp[j].GroupeNumber;
			for (int a = 0; a < 5; a++) {
				mass.mass[i].Marks[a] = tmp[j].Marks[a];
			}
			j++;
		}
		else {
			if (strcmp(tmp[k].LastName, tmp[j].LastName) > 0) {

				strcpy(mass.mass[i].FirstName, tmp[j].FirstName);
				strcpy(mass.mass[i].LastName, tmp[j].LastName);
				strcpy(mass.mass[i].Surname, tmp[j].Surname);
				mass.mass[i].GroupeNumber = tmp[j].GroupeNumber;
				for (int a = 0; a < 5; a++) {
					mass.mass[i].Marks[a] = tmp[j].Marks[a];
				}
				j++;
			}
			else {
				strcpy(mass.mass[i].FirstName, tmp[k].FirstName);
				strcpy(mass.mass[i].LastName, tmp[k].LastName);
				strcpy(mass.mass[i].Surname, tmp[k].Surname);
				mass.mass[i].GroupeNumber = tmp[k].GroupeNumber;
				for (int a = 0; a < 5; a++) {
					mass.mass[i].Marks[a] = tmp[k].Marks[a];
				}
				k++;
			}
		}
	}
	for (int i = first, j = 0; i <= last; i++, j++) {

		delete[]tmp[j].FirstName;
		delete[]tmp[j].LastName;
		delete[]tmp[j].Surname;
	}
	delete[] tmp;
}
void recMergeSort(STUDENT& mass, int first, int last) {
	if (first >= last) return;
	int m = (first + last) / 2;
	recMergeSort(mass, first, m);
	recMergeSort(mass, m + 1, last);
	merge(mass, first, last, m);

}
void MergeSort(STUDENT* mass) {
	recMergeSort(*mass, 0, mass->count- 1);
}
//////////END MERGE SORT///////////////////

//////////HEAP SORT////////////////
void heap(STUDENT& mass, int i, int n) {
	int max = i;
	while (true) {
		int child = 2 * i + 1;//левый ребёнок
		if (child<n && mass.mass[child].GroupeNumber>mass.mass[max].GroupeNumber)
			max = child;
		child++;//правый ребёнок
		if (child<n && mass.mass[child].GroupeNumber>mass.mass[max].GroupeNumber)
			max = child;
		if (max == i)
			break;
		else {
			swap(&mass.mass[max], &mass.mass[i]);
			i = max;
		}
	}
}
void HeapSort(STUDENT* mass) {
	for (int i = mass->count / 2; i >= 0; i--) {// цикл нужен, чтобы найти наивысший элемент в родитель-левый ребёнок-правый ребёнок, в конце цикла получится что наивысший элемент будет в начале структуры
		heap(*mass, i, mass->count);//создаём кучу
	}
	for (int i = mass->count - 1; i >= 1; i--) {//меняем вершину кучи и последний элемент и затем опять пемещаем в вершину наиюольший элемент
		swap(&mass->mass[0], &mass->mass[i]);
		heap(*mass, 0, i);
	}
	mass->GroupeNumberSort = true;
}
/////////////END HEAPSORT///////////


void swap(Student*a, Student* b) {
	Student tmp;
	tmp.FirstName = a->FirstName;
	tmp.LastName = a->LastName;
	tmp.Surname = a->Surname;
	tmp.GroupeNumber = a->GroupeNumber;
	for (int i = 0; i < 5; i++) {
		tmp.Marks[i] = a->Marks[i];
	}
	a->FirstName = b->FirstName;
	a->LastName = b->LastName;
	a->Surname = b->Surname;
	a->GroupeNumber = b->GroupeNumber;
	for (int i = 0; i < 5; i++) {
		a->Marks[i] = b->Marks[i];
	}
	b->FirstName = tmp.FirstName;
	b->LastName = tmp.LastName;
	b->Surname = tmp.Surname;
	b->GroupeNumber = tmp.GroupeNumber;
	for (int i = 0; i < 5; i++) {
		b->Marks[i] = tmp.Marks[i];
	}

}


//Конец сортировок
template<typename T>
T getValue(T& b)
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{
		std::cin >> b;

		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			std::cout << std::endl << "Ошибка, попробуйте ещё раз: ";
		}
		else {

			ClEANCONSOLE
				return b;
		}// если всё хорошо, то возвращаем a
	}
}
extern void SetCustomization();
extern HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли
static bool flag = true;
static int ActiveMenu = 8;
static void GotoXY(short y, short x = 35) {
	SetConsoleCursorPosition(hStdOut, { x,y });
}
extern void ConsoleCursorVisible(bool show, short size) {
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.bVisible = show;
	CursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &CursorInfo);
}
static void ConsoleTextColor(int n) {
	if (n == ActiveMenu) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("->");
	}
	else {
		SetCustomization();
	}
}
extern void SetCustomization() {
	if (flag) {
		system("color 25");
		ConsoleCursorVisible(false, 25);
		flag = false;
	}
	else
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_GREEN);
}

static int PositionInOutFile = 0;


////////Prototype//////////
static void DinamicAllocate(STUDENT* mass);
extern void CinInfoAboutStudent(STUDENT* mass);
static char* CoutString();
static void InfoClassification();
void InfoOneStudent(Student& one);
void InitilizeOneStudent(char* Nm, char* Ln, char* Sn, int GrNum, int* marks, STUDENT* mass);
void ReadOneStudentFromFile(STUDENT* mass, FILE* in, int pos);
void WriteOneStudentFromFile(STUDENT* mass, FILE* out, int pos);
void ImplementFunction(void(*function)(STUDENT*), STUDENT* mass);
void CleanArray(STUDENT* mass);
static void PrintArray(STUDENT* mass);
static void ReadFromFile(STUDENT* mass);
static void WriteInFile(STUDENT* mass);
static void linearSearch(STUDENT* mass);
static void BinarySearch(STUDENT* mass);
////////endPrototype//////
//void InitilizeOneStudent(char* Nm, char* Ln, char* Sn, int GrNum, int* marks,STUDENT* mass)
//{
//	mass->FirstName = Nm; 
//	mass->LastName = Ln;
//	mass->Surname = Sn;
//	mass->GroupeNumber = GrNum;
//	for (int i = 0; i < 5; i++) {
//		mass->Marks[i] = marks[i];
//	}
//	mass->count++;
//}

int EnterPoiskParametr() {
	printf("\n1)По Фамилии");
	printf("\n2)По номеру группы");
	int i=0;
	do {
		printf("\nВведите номер: ");
		scanf_s("%d", &i);
		getchar();
	} while (i!=1 && i!=2);
	return i;
}
bool PoiskSearchLastName(STUDENT & mass) {
	printf("\nВведите фамилию: ");
	char* str;
	str = CoutString();
	bool flag = false;
	for (int i = 0; i < mass.count; i++) {
		if (strcmp(str, mass.mass[i].LastName) == 0) {
			if (flag == false) {
				flag = true;
				InfoClassification();
			}
			InfoOneStudent(mass.mass[i]);
		}
	}
	return flag;
}
bool PoiskSearchGroupeNumber(STUDENT& mass) {
	printf("\nВведите номер группы: ");
	int groupe=getValue(groupe);

	bool flag = false;
	for (int i = 0; i < mass.count; i++) {
		if (groupe==mass.mass[i].GroupeNumber) {
			if (flag == false) {
				flag = true;
				InfoClassification();
			}
			InfoOneStudent(mass.mass[i]);
		}
	}
	return flag;
}
bool Poisk(int pos, STUDENT& mass) {
	bool flag = false;
	if (pos == 1) {
		flag=PoiskSearchLastName(mass);
	}
	else {
		flag = PoiskSearchGroupeNumber(mass);
	}
	return flag;
}

void ReadOneStudentFromFile(STUDENT* mass, FILE* in, int pos)
{
	int c;
	//////1
	Student InfoOne;
	fread(&c, sizeof(int), 1, in);
	InfoOne.FirstName = new char[c];
	fread(InfoOne.FirstName, sizeof(char), c, in);
	//////2
	fread(&c, sizeof(int), 1, in);
	InfoOne.LastName = new char[c];
	fread(InfoOne.LastName, sizeof(char), c, in);
	//////3
	fread(&c, sizeof(int), 1, in);
	InfoOne.Surname = new char[c];
	fread(InfoOne.Surname, sizeof(char), c, in);
	///////4
	fread(&InfoOne.GroupeNumber, sizeof(int), 1, in);
	///////5
	for (int i = 0; i < 5; i++) {
		fread(&InfoOne.Marks[i], sizeof(int), 1, in);
	}
	mass->mass[pos] = InfoOne;
}

extern void pointer(STUDENT* mass) {
	char ch;
	void (*function)(STUDENT*) = NULL;
	ch = _getch();
	if (ch == -32) ch = _getch(); // Отлавливаем стрелочки
	switch (ch)
	{
	case ESC:
		exit(0);
	case DOWN:
		if (ActiveMenu < 21)
			ActiveMenu++;
		break;
	case UP:
		if (ActiveMenu > 8)
			ActiveMenu--;
		break;
	case ENTRY:
		switch (ActiveMenu) {
		case 8:
			function = ReadFromFile;
			break;
		case 9:
			function = CinInfoAboutStudent;
			break;
		case 10:
			function = CleanArray;
			break;
		case 11:
			function = BubbleSort;
			break;
		case 12:
			function = InsertionSort;
			break;
		case 13:
			function = SelectionSort;
			break;
		case 14:
			function = ShellSort;
			break;
		case 15:
			function = QuickSort;
			break;
		case 16:
			function = MergeSort;
			break;
		case 17:
			function = HeapSort;
			break;
		case 18:
			function = PrintArray;
			break;
		case 19:
			function = linearSearch;
			break;
		case 20:
			function = BinarySearch;
			break;
		case 21:
			function = WriteInFile;
			break;
		}
		if (ActiveMenu >= 11 && ActiveMenu <= 17) {
			auto begin = std::chrono::high_resolution_clock::now();//запуск таймера
			ImplementFunction(function, mass);
			auto end = std::chrono::high_resolution_clock::now();//конец таймера
			auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);//разница во времени
			printf("Сортировка завершена за %.6f секунд!\n    ", elapsed.count() * 1e-9);
			PAUSE
		}
		else {
			ImplementFunction(function, mass);
			PAUSE
		}
		break;
	default:
		break;
	}
}
extern void menu() {
	int n = 4; // для перехода по строкам меню
	//////////
	CLEAN
		const char menuName[14][40] = {
			"Чтение массива с файла",
			"Ввеcти данные",
			"Отчистить массив",
			"Сортировка Пузырьком(имя)",
			"Сортировка Вставкой(отчество)",
			"Сортировка Выбором(фамилия)",
			"Сортировка Шелла(имя)",
			"Быстрая сортировка(номер группы)",
			"Сортировка Слиянием(фамилия)",
			"Heap Sort(номер группы)",
			"Вывести массив",
			"Линейный поиск",
			"Бинарный Поиск",
			"Запись в файл", };
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	GotoXY(n);
	for (int i = 0; i < 50; i++) {
		if (i == 0 || i == 49) {
			printf("+");
		}
		else printf("-");
	}
	n++;
	for (int i = 0, j = 0; i < 17; i++, n++) {
		if (i == 0) {
			GotoXY(n);
			printf("|");
			GotoXY(n, 57);
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_RED);
			printf("DIALOGUE");
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
			GotoXY(n, 84);
			printf("|");
			n++;
			GotoXY(n);
			for (int i = 0; i < 50; i++) {
				if (i == 0 || i == 49) {
					printf("+");
				}
				else printf("-");
			}
		}
		else if (i > 1 && i < 16) {

			GotoXY(n);
			printf("|");
			GotoXY(n, 50);
			ConsoleTextColor(n);
			printf("%s", menuName[j++]);
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
			GotoXY(n, 84);
			printf("|");
		}
		else {
			GotoXY(n);
			printf("|");
			GotoXY(n, 84);
			printf("|");
		}
	}
	GotoXY(n);
	for (int i = 0; i < 50; i++) {
		if (i == 0 || i == 49) {
			printf("+");
		}
		else printf("-");
	}
	SetCustomization();

}

void ImplementFunction(void(*function)(STUDENT*), STUDENT* mass) {
	GotoXY(25, 4);
	function(mass);

}
void InfoOneStudent(Student& one) {
	std::cout.width(20);
	std::cout << one.LastName << " " << one.FirstName[0] << ". " << one.Surname[0] << ".";
	std::cout.width(20);
	std::cout << one.GroupeNumber;
	std::cout.width(20);
	std::cout << one.Marks[0] << ", " << one.Marks[1] << ", " << one.Marks[2] << ", " << one.Marks[3] << ", " << one.Marks[4] << ". " <<std::endl;
}
//////Функции для работы со массивом//////
static void MakeEmpty(STUDENT* mass) {
	if (mass->count != 0) {
		mass->count = 0;
		free(mass->mass);
	}
}
static void InfoClassification() {
	CLEAN
		std::cout.width(30);
	std::cout << "Фамилия и Инициалы";
	std::cout.width(24);
	std::cout << "Номер группы";
	std::cout.width(29);
	std::cout << "5 оценок студента" << std::endl;
	for (register int i = 0; i < 85; i++)
		std::cout << "_";
	std::cout << std::endl;
}
static void PrintArray(STUDENT* mass) {
	if (mass->count == 0) {
		std::cout << "Сначало нужно ввести данные" << std::endl;
		return;
	}
	InfoClassification();
	for (register int i = 0; i < mass->count; i++) {
		std::cout << i + 1 << ":";
		InfoOneStudent(mass->mass[i]);
	}
}
static void howElement(int* i) {
	printf("Введите количество элементов в массиве: ");
	scanf_s("%d", i);
}
static void initilize(STUDENT* mass, int count = -1) {
	if (count < 0) {

		do {
			howElement(&count);
		} while (count <= 0);
	}
	mass->count = count;
	mass->mass = (Student*)malloc(count * sizeof(Student));

}

void CleanArray(STUDENT* mass) {
	MakeEmpty(mass);
	printf("\n    Массив отчищен!\n    ");

}
static void ReadFromFile(STUDENT* mass) {
	int i = 0;
	FILE* Out = fopen("Data.txt", "rb");
	if (Out == 0) {
		printf("Файл не найден!\n    ");
		return;
	}
	fseek(Out, PositionInOutFile, SEEK_CUR);
	if (fread(&i, sizeof(int), 1, Out)) {
		MakeEmpty(mass);
		initilize(mass, i);
		for (int i = 0; i < mass->count; i++) {
			ReadOneStudentFromFile(mass, Out, i);
		}
		PositionInOutFile = ftell(Out);
		printf("Данные считаны с файла!\n    ");
	}
	else {
		printf("Данный файл пуст или с него считана вся информация!\n    ");
	}
	fclose(Out);
}
void WriteOneStudentFromFile(STUDENT* mass, FILE* out, int pos)
{
	int c;
	///1
	c = (size_t)strlen(mass->mass[pos].FirstName) + 1;
	fwrite(&c, sizeof(int), 1, out);
	fwrite(mass->mass[pos].FirstName, sizeof(char), c, out);
	/////2
	c = (size_t)strlen(mass->mass[pos].LastName) + 1;
	fwrite(&c, sizeof(int), 1, out);
	fwrite(mass->mass[pos].LastName, sizeof(char), c, out);
	/////3
	c = (size_t)strlen(mass->mass[pos].Surname) + 1;
	fwrite(&c, sizeof(int), 1, out);
	fwrite(mass->mass[pos].Surname, sizeof(char), c, out);
	//////4
	fwrite(&mass->mass[pos].GroupeNumber, sizeof(int), 1, out);
	//////5
	for (int i = 0; i < 5; i++) {
		fwrite(&mass->mass[pos].Marks[i], sizeof(int), 1, out);
	}
}
static void WriteInFile(STUDENT* mass) {
	if (mass->count == 0)
	{
		printf("Эйй, зачем записывать пустой массив!?\n    ");
	}
	else {
		FILE* Out = fopen("Data.txt", "a+b");
		fwrite(&mass->count, sizeof(int), 1,Out);
		for (int i = 0; i < mass->count; i++) {
			WriteOneStudentFromFile(mass, Out, i);
		}
		fclose(Out);
		printf("Данные записаны в файл!\n    ");
	}
}

static void linearSearch(STUDENT* mass) {
	if (mass->count != 0) {
		
		
		int searchElemnet = EnterPoiskParametr();
		bool flag = false;
		flag = Poisk(searchElemnet, *mass);
		if (flag == false) {
			printf("Данный параметр не найден в массиве!\n" );
		}
		else {
			printf("\n");
		}
	}
	else {
		printf("Что вы хотите найти в пустом массиве!?\n    ");
	}
}
static void DinamicAllocate(STUDENT *mass) {
	Student*tmp = new Student[mass->count];
	for (register int i = 0; i < mass->count - 1; i++) {
		tmp[i] = mass->mass[i];
	}
	delete[] mass->mass;
	mass->mass = tmp;
}
static char* CoutString() {

	char c;
	int len = 1;
	char* str = new char[0];
	while ((c = std::cin.get()) != '\n')
	{
		char* temp = new char[len + 1];

		for (int i = 0; i < len - 1; i++) {
			temp[i] = str[i];
		}
		temp[len - 1] = c;
		temp[len] = '\0';
		delete[] str;
		str = temp;
		len++;
	}
	return str;
}
extern void CinInfoAboutStudent(STUDENT* mass) {
	mass->count++;
	DinamicAllocate(mass);
	std::cout << "Введите фамилию " << mass->count << "-ого студента: " << std::endl;
	mass->mass[mass->count - 1].LastName = CoutString();
	std::cout << "Введите имя " << mass->count  << "-ого студента: " << std::endl;
	mass->mass[mass->count - 1].FirstName = CoutString();
	std::cout << "Введите отчество " << mass->count  << "-ого студента: " << std::endl;
	mass->mass[mass->count - 1].Surname = CoutString();
	std::cout << "Введите группу " << mass->count << "-ого студента: " << std::endl;
	mass->mass[mass->count - 1].GroupeNumber = getValue(mass->mass[mass->count - 1].GroupeNumber);
	std::cout << "Введите 5 оценок " << mass->count + 1 << "-ого студента: " << std::endl;
	for (register short unsigned i = 0; i < 5; i++) {
		std::cout << "\t" << i + 1 << ": ";
		mass->mass[mass->count - 1].Marks[i] = getValue(mass->mass[mass->count - 1].Marks[i]);
	}

}

static void BinarySearch(STUDENT* mass) {
	int searchElemnet;
	if (!mass->GroupeNumberSort) {
		printf("Бинарный поиск нельзя применить к нетсортированному массиву!\n    ");
		return;
	}
	if (mass->count != 0) {
		printf("Введите номер группу, по которой вы хотите найти студента: ");
		scanf_s("%d", &searchElemnet);
		printf("\n    ");
	}
	else {
		printf("Чтовы хотите найти в пустом массиве!?\n    ");
		return;
	}
	int midd = 0;
	int left = 0, right = mass->count- 1;
	while (1)
	{
		midd = (left + right) / 2;

		if (searchElemnet < mass->mass[midd].GroupeNumber)       // если искомое меньше значения в ячейке
			right = midd - 1;      // смещаем правую границу поиска
		else if (searchElemnet > mass->mass[midd].GroupeNumber)  // если искомое больше значения в ячейке
			left = midd + 1;    // смещаем левую границу поиска
		else
		{
			printf("%d найден под индексом %d\n    ", mass->mass[midd].GroupeNumber, midd);
			system("pause");
			InfoClassification();
			InfoOneStudent(mass->mass[midd]);
			break;
		}

		if (left > right)          // если границы сомкнулись 
		{
			printf("\n    Данный элемент не найден в исходном массиве!\n    ");
			break;
		}
	}
}


