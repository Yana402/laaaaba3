#include<stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <io.h>
#pragma warning(disable: 4996)
void enterIntValue(const char* instruction, int* value) {
	do {
		printf("%s", instruction);
		if (scanf_s("%d", *&value)) {
			return;
		}
		else {
			printf("Incorrect input!\n");
			rewind(stdin);
		}
	} while (1);
}
void fileInput(FILE*& file, const char* filename) {
	int* values, valuesNum;
	enterIntValue("How many values you want write down to file?\n", &valuesNum);
	if (!(values = (int*)calloc(valuesNum, sizeof(int)))) {
		printf("Allocation error!\n");
		return;
	}
	for (int i = 0; i < valuesNum; i++) {
		printf("Value %d: ", i + 1);
		enterIntValue("", &values[i]);
	}
	if (!(file = fopen(filename, "wb"))) {
		puts("Error!\n");
		return;
	}
	rewind(file);
	fwrite(values, sizeof(int), valuesNum, file);
	free(values);
	fclose(file);
}
void fileOutput(FILE*& file, const char* filename) {
	int value;
	if (!(file = fopen(filename, "rb"))) {
		printf("Error opening file!\n");
		return;
	}
	rewind(file);
	printf("File content: ");
	while (!feof(file)) {
		if (fread(&value, sizeof(int), 1, file))
			printf("%3d", value);
	}
	putchar('\n');
	fclose(file);
}
int count(FILE*& file, const char* filename) {
	int a, b, counter = 0;
	if (!(file = fopen(filename, "r"))) {
		printf("Error!\n");
		return 0;
	}
	enterIntValue("Enter specified value: ", &a);
	while (!feof(file)) {
		fread(&b, sizeof(int), 1, file);
		if (b < a)
			counter++;
	}
	return counter;
}
long int filesize(FILE* fp)
{
	long int save_pos, size_of_file;
	save_pos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	size_of_file = ftell(fp);
	fseek(fp, save_pos, SEEK_SET);
	return(size_of_file);
}
void sort(FILE*& f, const char* filename) {
	fpos_t n1, n2, n3;
	int i1, i2;
	if (!(f = fopen(filename, "r+b"))) {
		printf("Error!\n");
		return;
	}
	n3 = sizeof(int);
	fseek(f, -n3, 2);                // переход на последнее число в файле
	n3 = ftell(f);                   // позиция последнего числа
	rewind(f);                       // возврат в начало файла
	n1 = 0;
	while (1)
	{
		if (n1 >= n3) break;         // n1 на последнем числе в файле
		n2 = n3;                     // n2-позиция для движения вначало файла
		while (n1 < n2)
		{
			fsetpos(f, &n2);         // позиция 1 считываемого числа
			fread(&i2, sizeof(int), 1, f); // первое число для сравнения
			n2 -= sizeof(int);
			fsetpos(f, &n2);         // позиция 2 считываемого числа
			fread(&i1, sizeof(int), 1, f); // второе число для сравнения

			if (i1 < i2)               // сравнение и замена чисел в файле
			{
				fsetpos(f, &n2);     // позиция считываемого числа
				fwrite(&i2, sizeof(int), 1, f); // исходное число
				fwrite(&i1, sizeof(int), 1, f);
			}
		}
		n1 += sizeof(int);
	}
	rewind(f);
}
int main() {
	FILE* file;
	fileInput(file, "a.bin");
	fileOutput(file, "a.bin");
	printf("Number of elements less than specifed: %d", count(file, "a.bin"));
	sort(file, "a.bin");
	putchar('\n');
	fileOutput(file, "a.bin");
}