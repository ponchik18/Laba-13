#include"Header.h"
#include"sortAlgorithm.h"
extern HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли
static bool flag = true;
static int ActiveMenu = 8;
static void GotoY(short y, short x = 35) {
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
		SetConsoleTextAttribute(hStdOut, BACKGROUND_RED| BACKGROUND_BLUE| BACKGROUND_INTENSITY| FOREGROUND_GREEN| FOREGROUND_RED| FOREGROUND_INTENSITY);
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
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED| FOREGROUND_BLUE| FOREGROUND_RED | BACKGROUND_GREEN);
}

static int PositionInOutFile = 0;


////////Prototype//////////
static void removeRepeater(Array& mass);
static void RandomFill(Array& mass);
void ImplementFunction(void(*function)(Array&), Array& mass);
void CleanArray(Array& mass);
static void PrintArray(Array& mass);
static void ReadFromFile(Array& mass);
static void WriteInFile(Array& mass);
static void linearSearch(Array& mass);
static void BinarySearch(Array& mass);
////////endPrototype//////

extern void pointer(Array& mass) {
	char ch;
	void (*function)(Array&)=NULL;
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
			function = RandomFill;
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
	const char menuName[14][26] = {
		"Чтение массива с файла", 
		"Рандомный ввод", 
		"Отчистить массив", 
		"Сортировка Пузырьком",
		"Сортировка Вставкой", 
		"Сортировка Выбором", 
		"Сортировка Шелла", 
		"Быстрая сортировка", 
		"Сортировка Слиянием", 
		"Пирамидальная сортировка", 
		"Вывести массив", 
		"Линейный поиск",
		"Бинарный Поиск",
		"Запись в файл",};
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	GotoY(n);
	for (int i = 0; i < 50; i++) {
		if (i == 0 || i == 49) {
			printf("+");
		}
		else printf("-");
	}
	n++;
	for (int i = 0, j=0 ; i < 17; i++, n++) {
		if (i == 0) {
			GotoY(n);
			printf("|");
			GotoY(n, 57);
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_RED);
			printf("DIALOGUE");
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
			GotoY(n, 84);
			printf("|");
			n++;
			GotoY(n);
			for (int i = 0; i < 50; i++) {
				if (i == 0 || i == 49) {
					printf("+");
				}
				else printf("-");
			}
		}
		else if (i > 1 && i<16) {

			GotoY(n);
			printf("|");
			GotoY(n, 50);
			ConsoleTextColor(n);
			printf("%s", menuName[j++]);
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
			GotoY(n, 84);
			printf("|");
		}
		else {
			GotoY(n);
			printf("|");
			GotoY(n, 84);
			printf("|");
		}
	}
	GotoY(n);
	for (int i = 0; i < 50; i++) {
		if (i == 0 || i == 49) {
			printf("+");
		}
		else printf("-");
	}
	SetCustomization();

} 

void ImplementFunction(void(*function)(Array&), Array& mass) {
	GotoY(25, 4);
	function(mass);
	
}

//////Функции для работы со массивом//////
static void MakeEmpty(Array& mass) {
	if (mass.Size != 0) {
		mass.Size = 0;
		free(mass.Array);
	}
}
static void PrintArray(Array& mass) {
	for (int i = 0; i < mass.Size; i++) {
		printf("%3d", mass.Array[i]);
		printf(" ");
	}
	printf("\n    ");
}
static void howElement(int* i) {
	printf("Введите количество элементов в массиве: ");
	scanf_s("%d", i);
}
static void initilize(Array & mass, int count = -1) {
	if (count < 0) {

		do {
			howElement(&count);
		} while (count <= 0);
	}
	mass.Size = count;
	mass.Array =(int*) malloc(count * sizeof(int));

}
static void random(Array& mass) {
	for (int i = 0; i < mass.Size; i++) {
		mass.Array[i] = 0 + rand() % 100;
	}
}
static void RandomFill(Array& mass) {
	MakeEmpty(mass);
	initilize(mass);
	random(mass);
	GotoY(26, 4);
	printf("Массив заполнен!");
	GotoY(27, 4);
	PrintArray(mass);

}
void CleanArray(Array& mass) {
	MakeEmpty(mass);
	printf("\n    Массив отчищен!\n    ");

}
static void ReadFromFile(Array& mass) {
	int i=0;
	FILE* Out= fopen("Data.txt", "rb");
	if (Out == 0) {
		printf("Файл не найден!\n    ");
		return;
	}
	fseek(Out, PositionInOutFile, SEEK_CUR);
	if (fread(&i, sizeof(int), 1, Out)) {
		MakeEmpty(mass);		
		initilize(mass, i);
		fread(mass.Array, sizeof(int), mass.Size, Out);
		PositionInOutFile = ftell(Out);
		printf("Данные считаны с файла!\n    ");
	}
	else {
		printf("Данный файл пуст или с него считана вся информация!\n    ");
	}
	fclose(Out);
}
static void WriteInFile(Array& mass) {
	if (mass.Size == 0)
	{
		printf("Эйй, зачем записывать пустой массив!?\n    ");
	}
	else {
		FILE* In = fopen("Data.txt", "a+b");
		fwrite(&mass.Size, sizeof(int), 1, In);
		fwrite(mass.Array, sizeof(int), mass.Size, In);
		fclose(In);
		printf("Данные записаны в файл!\n    ");
	}
}
static void linearSearch(Array& mass) {
	if (mass.Size != 0) {
		printf("Введите число, которое хотите найти: ");
		int searchElemnet;
		scanf_s("%d", &searchElemnet);
		printf("\n    ");
		bool flag = false;
		for (int i = 0; i < mass.Size; i++) {
			if (mass.Array[i] == searchElemnet) {
				flag = true;
				printf("%d найден под индексом %d\n    ", mass.Array[i],i );
			}
		}
		if (flag == false) {
			printf("%d не найден в массиве!\n    ", searchElemnet);
		}
		else {
			printf("\n    ");
		}
	}
	else {
		printf("Чтовы хотите найти в пустом массиве!?\n    ");
	}
}
static void removeRepeater(Array& mass) { 
	int repeater = 0;
	int NewEnd=mass.Size-1;
	for (int i = 0; i <= NewEnd; i++) {
		if (mass.Array[i] == mass.Array[i + 1]) {
			repeater = 0;
			int j;
			for (j = i; j <= NewEnd && mass.Array[j] == mass.Array[j+1]; j++) {
					repeater++;
			}
			int index = i+repeater+1;
			for (int a = i+1; index <= NewEnd; a++, index++) {
				mass.Array[a] = mass.Array[index];
			}
			NewEnd -= repeater;
		}
	}
	int* tmp = (int*)malloc((NewEnd + 1) * sizeof(int));
	for (int i = 0; i <= NewEnd; i++) {
		tmp[i] = mass.Array[i];
	}
	free(mass.Array);
	mass.Size = NewEnd + 1;
	mass.Array = tmp;
}
static void BinarySearch(Array& mass) {
	int searchElemnet;
	if (!mass.sort) {
		printf("Бинарный поиск нельзя применить к нетсортированному массиву!\n    ");
		return;
	}
	removeRepeater(mass);
	if (mass.Size != 0) {
		printf("Введите число, которое хотите найти: ");
		scanf_s("%d", &searchElemnet);
		printf("\n    ");
	}
	else {
		printf("Чтовы хотите найти в пустом массиве!?\n    ");
		return;
	}
	int midd = 0;
	int left = 0, right=mass.Size-1; 
	while (1)
	{
		midd = (left + right) / 2;

		if (searchElemnet < mass.Array[midd])       // если искомое меньше значения в ячейке
			right = midd - 1;      // смещаем правую границу поиска
		else if (searchElemnet > mass.Array[midd])  // если искомое больше значения в ячейке
			left = midd + 1;    // смещаем левую границу поиска
		else                     
		{
			printf("%d найден под индексом %d\n    ", mass.Array[midd], midd);
			break;
		}

		if (left > right)          // если границы сомкнулись 
		{
			printf("\n    Данный элемент не найден в исходном массиве!\n    ");
			break;
		}
	}
}
//1 2 2 3 4 4 4 5 5 
//i=1
