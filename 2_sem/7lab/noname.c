#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXKV 1000	 //макс. номер квартиры
#define MAXSTR 31	 //макс. длина строки
#define MINYEAR 2000 //минимальный год
//------------------------------------------------------------
struct TZakaz
{
	char Street[MAXSTR];
	char Dom[MAXSTR];
	int Kv;
	int D;
	int M;
	int Y;
};
int CorrectKv(struct TZakaz Zakaz)
{ //проверка корректности номера квартиры
	if (Zakaz.Kv < 1 || Zakaz.Kv > MAXKV)
		return 0;
	return 1;
}
int CorrectDate(struct TZakaz Zakaz)
{ //проверка корректности даты
	int m[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	int d[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (Zakaz.Y < MINYEAR)
		return 0;
	if (Zakaz.Y % 4 == 0)
		d[1] = 29;
	if (Zakaz.M < 1 || Zakaz.M > 12)
		return 0;
	if (Zakaz.D < 1 || Zakaz.D > d[Zakaz.M - 1])
		return 0;
	return 1;
}
void GetKv(struct TZakaz Zakaz)
{ //ввод номера квартиры
	while (!CorrectKv(Zakaz))
	{
		printf("\nНекорректное значение номера квартиры - %d", Zakaz.Kv);
		printf("\nВведите номер квартиры (1..%d)", MAXKV);
		if (scanf("%d", &Zakaz.Kv) != 1)
		{
			Zakaz.Kv = 0;
			fflush(stdin);
		}
	}
}
void GetDate(struct TZakaz Zakaz)
//ввод даты
{
	while (!CorrectDate(Zakaz))
	{
		printf("\nНекорректное значение даты - %d %d %d", Zakaz.D, Zakaz.M, Zakaz.Y);
		printf("\nВведите три числа: день месяц род\n");
		if (scanf("%d %d %d", &Zakaz.D, &Zakaz.M, &Zakaz.Y) != 3)
		{
			Zakaz.Y = 0;
			fflush(stdin);
		}
	}
}
void InitFileName(char *tname, char *bname)
//установка имен текстоворо и двоичноро файлов
{
	printf("Текстовый файл: ");
	gets(tname);
	printf("Двоичный файл: ");
	gets(bname);
}
void PrintZakaz(struct TZakaz Zakaz)
//Вывод данных о заказе на экран
{
	printf("\n%-30s%-30s%-5d%02d\/%02d\/%4d", Zakaz.Street, Zakaz.Dom, Zakaz.Kv, Zakaz.D, Zakaz.M, Zakaz.Y);
}
int GetFileStr(FILE *f, char *s, char razd, int max)
//Считывание из файла строки до разделительноро символа
//либо до максимальной длины
{
	int i = 0;
	char str[2] = " ";
	s[0] = 0;
	while (str[0] != razd && str[0] != 13 && str[0] != 10)
	{
		str[0] = getc(f);
		strcat(s, str);
		i++;
		if (i >= max)
			return 0;
	}
	s[i - 1] = 0;
	return 1;
}
//---------- создание двоичноро из текстоворо
void CreateBinaryFile(char *tname, char *bname)
{
	if (bname[0] == 0)
	{
		printf("Имя BIN-файла не задано. Используйте опцию меню 5\n");
		return;
	}
	if (tname[0] == 0)
	{
		printf("Имя текстоворо файла не задано. Используйте опцию меню 5\n");
		return;
	}
	FILE *ft = fopen(tname, "r");
	if (ft == NULL)
	{
		printf("Error: не удалось открыть текстовый файл %s с данными\n", tname);
		printf("Press enter");
		getchar();
		return;
	}
	FILE *fb = fopen(bname, "wb");
	if (fb == NULL)
	{
		fclose(ft);
		printf("Error: не удалось создать двоичный файл %s\n", bname);
		printf("Press enter");
		getchar();
		return;
	}
	struct TZakaz Zakaz;
	int kol = 0, nw = 1;
	char s[MAXSTR];
	while (nw)
	{
		if (!GetFileStr(ft, &s[0], ',', MAXSTR))
		{
			printf("Ошибка чтения улицы в %i строке", kol);
			break;
		}
		// ввод слова
		//признак конца файла - фамилия ** или конец файла
		if (strcmp(s, "**") == 0 || feof(ft))
			break;
		strcpy(Zakaz.Street, s);
		if (!GetFileStr(ft, &s[0], ',', MAXSTR))
		{
			printf("Ошибка чтения дома в %i строке", kol);
			break;
		}
		strcpy(Zakaz.Dom, s);
		if (!GetFileStr(ft, &s[0], ',', MAXSTR))
		{
			printf("Ошибка чтения квартиры в %i строке", kol);
			break;
		}
		Zakaz.Kv = atoi(s);
		if (!GetFileStr(ft, &s[0], ',', MAXSTR))
		{
			printf("Ошибка чтения даты в %i строке", kol);
			break;
		}
		Zakaz.D = atoi(s);
		if (!GetFileStr(ft, &s[0], ',', MAXSTR))
		{
			printf("Ошибка чтения месяца в %i строке", kol);
			break;
		}
		Zakaz.M = atoi(s);
		if (!GetFileStr(ft, &s[0], '\n', MAXSTR))
		{
			printf("Ошибка чтения рода в %i строке", kol);
			break;
		}
		Zakaz.Y = atoi(s);
		nw = fwrite(&Zakaz, sizeof(Zakaz), 1, fb);
		kol++;
	}
	if (nw != 1)
		printf("Error: Ошибка при записи");
	fclose(ft);
	fclose(fb);
	printf("Создан двоичный файл из %d записей по %d байт\n", kol, sizeof(Zakaz));
	printf("Press any key to continue");
	getch();
	return;
}
void getstr(char *s)
//считывание строки с укорачиванием до заданноро максимума
{
	gets(s);
	s[MAXSTR - 1] = 0;
	fflush(stdin);
}
void CreateMask(struct TZakaz Mask)
//Создание шаблона поиска
{
	char s[MAXSTR];
	printf("Создание шаблона поиска. Вводите искомые значения либо символ *\n");
	printf("Улица: ");
	getstr(&s[0]);
	strcpy(Mask.Street, s);
	printf("Дом: ");
	getstr(&s[0]);
	strcpy(Mask.Dom, s);
	printf("Квартира: ");
	getstr(s);
	if (strcmp(s, "*"))
		Mask.Kv = atoi(s);
	else
		Mask.Kv = 0;
	printf("День: ");
	getstr(s);
	if (strcmp(s, "*"))
		Mask.D = atoi(s);
	else
		Mask.D = 0;
	printf("Месяц: ");
	getstr(s);
	if (strcmp(s, "*"))
		Mask.M = atoi(s);
	else
		Mask.M = 0;
	printf("род: ");
	getstr(s);
	if (strcmp(s, "*"))
		Mask.Y = atoi(s);
	else
		Mask.Y = 0;
}
int Compare(struct TZakaz Zakaz, struct TZakaz Mask)
//Проверяет Zakaz на соответствие маске поиска
{
	if (strcmp(Mask.Street, "*") && strcmp(Zakaz.Street, Mask.Street))
		return 0;
	if (strcmp(Mask.Dom, "*") && strcmp(Zakaz.Dom, Mask.Dom))
		return 0;
	if (Mask.Kv != 0 && Mask.Kv != Zakaz.Kv)
		return 0;
	if (Mask.D != 0 && Mask.D != Zakaz.D)
		return 0;
	if (Mask.M != 0 && Mask.M != Zakaz.M)
		return 0;
	if (Mask.Y != 0 && Mask.Y != Zakaz.Y)
		return 0;
	return 1;
}
void Find(char *bname)
//поиск в двоичном файле ----
{
	if (bname[0] == 0)
	{
		printf("Имя файла не задано. Используйте опцию меню 5\n");
		return;
	}
	FILE *fb = fopen(bname, "rb");
	if (fb == NULL)
	{
		printf("Error: не удалось открыть двоичный файл %s\n", bname);
		printf("Press any key...");
		getch();
		return;
	}
	struct TZakaz Zakaz, Mask;
	CreateMask(Mask);
	printf("результат поиска\n");
	int kol = 0, nr = 1;
	while (nr)
	{
		nr = fread(&Zakaz, sizeof(Zakaz), 1, fb);
		if (nr > 0)
			if (Compare(Zakaz, Mask) == 1)
			{
				PrintZakaz(Zakaz);
				kol++;
			}
	}
	if (kol == 0)
		printf("Данные, соответствующие запросу, не найдены\n");
	else
		printf("\nВсеро найдено: %d\n", kol);
	fclose(fb);
	printf("Press any key to continue");
	getch();
	return;
}
void CorrectFile(char *bname)
//корректировка в двоичном файле ----
{
	if (bname[0] == 0)
	{
		printf("Имя файла не задано. Используйте опцию меню 5\n");
		return;
	}
	FILE *fb = fopen(bname, "rb+");
	if (fb == NULL)
	{
		printf("Error: не удалось открыть двоичный файл %s\n", bname);
		printf("Press any key");
		getch();
		return;
	}
	struct TZakaz Zakaz;
	int kol = 0, nr = 1, nw = 1, flag;
	nr = fread(&Zakaz, sizeof(Zakaz), 1, fb);
	while (nr == 1 && nw == 1)
	{
		printf("\nСчитана запись:\n");
		PrintZakaz(Zakaz);
		flag = 0;
		if (!CorrectKv(Zakaz))
		{
			GetKv(Zakaz);
			flag = 1;
		}
		if (!CorrectDate(Zakaz))
		{
			GetDate(Zakaz);
			flag = 1;
		}
		if (flag)
		{
			kol++;
			fseek(fb, 0 - sizeof(Zakaz), SEEK_CUR);
			nw = fwrite(&Zakaz, sizeof(Zakaz), 1, fb);
			fseek(fb, 0, SEEK_CUR);
			printf("Сделана корректировка:\n");
			PrintZakaz(Zakaz);
		}
		nr = fread(&Zakaz, sizeof(Zakaz), 1, fb);
	}
	if (kol == 0)
		printf("Ни одной корректировки\n");
	else
		printf("Всеро корректировок: %d\n", kol);
	fclose(fb);
	printf("Press any key to continue");
	getch();
	return;
}
void PrintBinFile(char *bname)
//вывод двоичноро файла на экран
{
	if (bname[0] == 0)
	{
		printf("Имя файла не задано. Используйте опцию меню 5\n");
		return;
	}
	FILE *fb = fopen(bname, "rb");
	if (fb == NULL)
	{
		printf("Error: не удалось открыть двоичный файл %s\n", bname);
		printf("Press any key..,");
		getch();
		return;
	}
	struct TZakaz Zakaz;
	int kol = 0, nr = 1;
	nr = fread(&Zakaz, sizeof(Zakaz), 1, fb);
	if (!nr)
	{
		printf("Пустой файл\n");
		return;
	}
	printf("Улица\t\t\t      Дом\t\t\t    Кв.  Дата\n");
	while (nr)
	{
		if (nr > 0)
			PrintZakaz(Zakaz);
		nr = fread(&Zakaz, sizeof(Zakaz), 1, fb);
		kol++;
	}
}
void printmenu() //меню
{
	printf("\n1 - создать новый BIN-файл");
	printf("\n2 - поиск");
	printf("\n3 - коррекция");
	printf("\n4 - просмотр");
	printf("\n5 - задать имена файлов");
	printf("\nE - выход\n");
}
//------------------рлавная функция-----------------------
int main(int argc, char *argv[])
{
	char ch = 0;
	char tname[100], bname[100];
	strcpy(tname, "1.txt");
	strcpy(bname, "2.txt");
	if (argc < 2)
	{
		printf("Имена файлов не заданы. Установлены значения по умолчанию\n");
		printf("Текстовый файл: %s\nДвоичный файл: %s", tname, bname);
	}
	else
	{
		if (argc > 2)
			strcpy(tname, argv[2]);
		if (argc > 1)
			strcpy(bname, argv[1]);
		printf("Входные параметры\n");
		printf("Текстовый файл: %s\nДвоичный файл: %s", tname, bname);
	}
	while (ch != 'E')
	{
		printmenu();
		ch = getchar();
		getchar();
		switch (ch)
		{
			//---------- создание двоичноро из текстоворо
		case '1':
			CreateBinaryFile(tname, bname);
			break;
			//-------------- поиск в двоичном файле ----
		case '2':
			Find(bname);
			break;
			//------- корректировка в двоичном файле ----
		case '3':
			CorrectFile(bname);
			break;
			//------- просмотр в двоичном файле ----
		case '4':
			PrintBinFile(bname);
			break;
			//задать имена файлов
		case '5':
			InitFileName(&tname[0], &bname[0]);
			break;
			//-----------выход----------------------------------------
		case 'E':
			return 0;
			//--------------------------------------------------------
		}
	}
	return 0;
}