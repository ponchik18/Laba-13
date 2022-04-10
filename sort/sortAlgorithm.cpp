#include"sortAlgorithm.h"
#include<stdio.h>
void swap(int* a, int* b);
void BubbleSort(Array& mass)
{
	int flag = 1;
	for (int i = 0; (i < mass.Size) && (flag == 1); i++) {
		flag = 0;
		for (int j = 0; j < mass.Size - 1; j++) {
			if (mass.Array[j] > mass.Array[j + 1]) {
				swap(&mass.Array[j], &mass.Array[j + 1]);
				flag = 1;
			}
		}
	}
	mass.sort = true;
}
void SelectionSort(Array& mass) {
	for (int i = 0; i < mass.Size; i++) {
		for (int j = i + 1; j < mass.Size; j++) {
			if (mass.Array[i] > mass.Array[j]) {
				swap(&mass.Array[i], &mass.Array[j]);
			}
		}
	}
	mass.sort = true;
}
void InsertionSort(Array& mass)
{
	for (int TransactionElement = 1; TransactionElement < mass.Size; TransactionElement++) {
		if (mass.Array[TransactionElement] < mass.Array[TransactionElement - 1]) {
			int temp = mass.Array[TransactionElement];
			int location = TransactionElement;
			do {
				mass.Array[location] = mass.Array[location - 1];
				location--;
			} while (location > 0 && mass.Array[location - 1] > temp);
			mass.Array[location] = temp;
		}
	}
	mass.sort = true;
}

/////////////QUICKSORT////////////
int partition(int* mass, int first, int last) {
	int pivot;
	int smallIndex;
	swap(&mass[first], &mass[(first + last) / 2]);
	pivot = mass[first];
	smallIndex = first;
	for (int index = first + 1; index <= last; index++) {
		if (mass[index] < pivot)
		{
			smallIndex++;
			swap(&mass[smallIndex], &mass[index]);
		}
	}
	swap(&mass[first], &mass[smallIndex]);
	return smallIndex;
}
void recQuickSort(int* mass, int first, int last) {
	if (first < last) {
		int pivotLocation = partition(mass, first, last);
		recQuickSort(mass, first, pivotLocation - 1);
		recQuickSort(mass, pivotLocation + 1, last);
	}
}
void QuickSort(Array& mass) {
	recQuickSort(mass.Array, 0, mass.Size - 1);
}
//////////////END QUICKSORT////////

void ShellSort(Array& mass) {
	int i, j, step, tmp;
	for (step = mass.Size / 2; step > 0; step /= 2) {
		for (i = step; i < mass.Size; i++) {
			tmp = mass.Array[i];
			for (j = i; j >= step; j -= step) {
				if (tmp < mass.Array[j - step])
					mass.Array[j] = mass.Array[j - step];
				else
					break;
			}
			mass.Array[j] = tmp;
		}
	}
	mass.sort = true;
}

//////////MERGE SORT///////////////////
void merge(int* mass, int first, int last, int m) {
	if (first >= last || m<first || m>last) return;
	if (last == first + 1 && mass[first] > mass[last]) {
		swap(&mass[first], &mass[last]);
		return;
	}
	int* tmp = new int[last - first + 1];
	for (int i = first, j = 0; i <= last; i++, j++) {
		tmp[j] = mass[i];
	}
	for (int i = first, j = 0, k = m - first + 1; i <= last; ++i) {
		if (j > m - first) {
			mass[i] = tmp[k++];
		}
		else if (k > last - first) {
			mass[i] = tmp[j++];
		}
		else {
			mass[i] = (tmp[j] < tmp[k] ? tmp[j++] : tmp[k++]);
		}
	}
	delete[] tmp;
}
void recMergeSort(int* mass, int first, int last) {
	if (first >= last) return;
	int m = (first + last) / 2;
	recMergeSort(mass, first, m);
	recMergeSort(mass, m + 1, last);
	merge(mass, first, last, m);

}
void MergeSort(Array& mass) {
	recMergeSort(mass.Array, 0, mass.Size - 1);
}
//////////END MERGE SORT///////////////////

//////////HEAP SORT////////////////
void heap(int* mass, int i, int n) {
	int max = i;
	while (true) {
		int child = 2 * i + 1;//левый ребёнок
		if (child<n && mass[child]>mass[max])
			max = child;
		child++;//правый ребёнок
		if (child<n && mass[child]>mass[max])
			max = child;
		if (max == i)
			break;
		else {
			swap(&mass[max], &mass[i]);
			i = max;
		}
	}
}
void HeapSort(Array& mass) {
	for (int i = mass.Size / 2; i >= 0; i--) {// цикл нужен, чтобы найти наивысший элемент в родитель-левый ребёнок-правый ребёнок, в конце цикла получится что наивысший элемент будет в начале структуры
		heap(mass.Array, i, mass.Size);//создаём кучу
	}
	for (int i = mass.Size - 1; i >= 1; i--) {//меняем вершину кучи и последний элемент и затем опять пемещаем в вершину наиюольший элемент
		swap(&mass.Array[0], &mass.Array[i]);
		heap(mass.Array, 0, i);
	}
}
/////////////END HEAPSORT///////////


void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}