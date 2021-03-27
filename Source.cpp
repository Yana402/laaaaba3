#include <stdio.h>
#include <windows.h>
#pragma warning(disable: 4996)
void input(FILE*& stream, const char* filename) {
	char buffer[100];
	if (!(stream = fopen(filename, "w"))) {
		printf("Error!\n");
		return;
	}
	printf("Enter smth in file: ");
	gets_s(buffer);
	fprintf(stream, "%s", buffer);
	fclose(stream);
}
void output(FILE*& stream, const char* filename) {
	char buffer[100];
	if (!(stream = fopen(filename, "r"))) {
		printf("Error!\n");
		return;
	}
	fgets(buffer, 100, stream);
	printf("File content: %s\n", buffer);
	fclose(stream);
}
int sum(FILE*& stream, const char* filename) {
	char buffer[100]; int sum = 0, n = 0;
	if (!(stream = fopen(filename, "r"))) {
		printf("Error!\n");
		return 0;
	}
	while (!feof(stream)) {
		fscanf(stream, "%s", buffer);
		int i = 0;
		n = atoi(buffer);
		sum += n;
	}
	return sum;
}
int strlen(char* str) {
	int i;
	for (i = 0; str[i]; i++);
	return i;
}
//long int filesize(FILE* fp)
//{
//	long int save_pos, size_of_file;
//	save_pos = ftell(fp);
//	fseek(fp, 0, SEEK_END);
//	size_of_file = ftell(fp);
//	fseek(fp, save_pos, SEEK_SET);
//	return(size_of_file);
//}
//void change(FILE*& file, const char* name) {
//	char a[100], b[100];
//	fpos_t pos1, pos2;
//	if (!(file = fopen(name, "r+"))) {
//		printf("Error!\n");
//		return;
//	}
//	int len = 0;
//	while (!feof(file)) {
//		fscanf(file, "%s", a);
//		len += strlen(a);
//	}
//	fseek(file, -strlen(a), SEEK_CUR);
//	fgetpos(file, &pos1);
//	rewind(file);
//	while (ftell(file) != (filesize(file) - len)) {
//		fscanf(file, "%s", b);
//	}
//	fseek(file, -strlen(b), SEEK_CUR);
//	fgetpos(file, &pos2);
//	rewind(file);
//	fsetpos(file, &pos1);
//	fprintf(file, "%s", b);
//	fsetpos(file, &pos2);
//	fprintf(file, "%s", a);
//	fclose(file);
//}
int main() {
	FILE* file;
	input(file, "a.txt");
	printf("%d\n", sum(file, "a.txt"));
	output(file, "a.txt");
	return 0;
}