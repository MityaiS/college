#include <windows.h>
#include <stdio.h>
#include <conio.h>
//------------------------------------------------------------
struct TStud
{
    struct
    {
        char F[31], I[31], O[31];
    } FIO;
    int o1, o2, o3;
};
// ---------создание копии строки, но с символами
//---------------в верхнем регистре в Win1251
char *ANSIUpperCase(char *s, char *S)
{
    S = strcpy(S, s);
    char *ch = S;
    while (*ch)
    {
        if (*ch >= 'a' && *ch <= 'z' || *ch >= 'а' && *ch <= 'я')
            *ch = *ch - 32;
        if (*ch == 'ё')
            *ch = 'Ё';
        ch++;
    }
    return S;
}
//----------первая часть: создание двоичного из текстового
void CreateBinaryFile(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Мало параметров\nPress any key");
        getch();
        return;
    }
    FILE *ft = fopen(argv[2], "rt");
    if (ft == NULL)
    {
        printf("Error: не удалось открыть файл с \ 
исходными данными %s\n",
               argv[2]);
        printf("Press any key ");
        getch();
        return;
    }
    FILE *fb = fopen(argv[1], "wb");
    if (fb == NULL)
    {
        fclose(ft);
        printf("Error: не удалось создать \ 
двоичный файл %s\n",
               argv[1]);
        printf("Press any key");
        getch();
        return;
    }
    TStud Stud; // либо struct TStud Stud; в С
    int kol = 0, nw = 1;
    char s[3];
    while (nw)
    {
        fscanf(ft, "%30s", Stud.FIO.F); // ввод слова
        //признак конца файла - фамилия ** или конец файла
        if (strcmp(Stud.FIO.F, "**") == 0 || feof(ft))
            break;
        //для ввода строки из нескольких слов см.Указание выше
        fscanf(ft, "%30s", Stud.FIO.I);
        fscanf(ft, "%30s", Stud.FIO.O);
        fscanf(ft, "%s", s);
        Stud.o1 = atoi(s);
        fscanf(ft, "%s", s);
        Stud.o2 = atoi(s);
        fscanf(ft, "%s", s);
        Stud.o3 = atoi(s);
        nw = fwrite(&Stud, sizeof(Stud), 1, fb);
        kol++;
    }
    if (nw != 1)
        printf("Error: Ошибка при записи");
    fclose(ft);
    fclose(fb);
    printf("Создан двоичный файл из %d записей \ 
по %d байт\n",
           kol, sizeof(TStud));
    printf("Press any key to continue");
    getch();
    return;
}
//-------------- вторая часть: поиск в двоичном файле ----
void FindIVAN(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Мало параметров\nPress any key");
        getch();
        return;
    }
    FILE *fb = fopen(argv[1], "rb");
    if (fb == NULL)
    {
        printf("Error: не удалось открыть двоичный \ 
файл %s\n",
               argv[1]);
        printf("Press ENTER");
        getch();
        return;
    }
    TStud Stud;
    char SUp[31];
    int kol = 0, nr = 1;
    while (nr)
    {
        nr = fread(&Stud, sizeof(Stud), 1, fb);
        if (nr > 0)
            if (Stud.o1 == 5 && Stud.o2 == 5 && Stud.o3 == 5 &&
                strcmp(ANSIUpperCase(Stud.FIO.I, SUp), "ИВАН") == 0)
            {
                printf("Найден %s %s %s\n", Stud.FIO.I, Stud.FIO.O, Stud.FIO.F);
                kol++;
            }
    }
    if (kol == 0)
        printf("Данные, соответствующие запросу,не найдены\n");
    else
        printf("Всего найдено: %d\n", kol);
    fclose(fb);
    printf("Press any key to continue");
    getch();
    return;
}
//-------третья часть: корректировка в двоичном файле ----
void CorrectFile(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Мало параметров\nPress any key");
        getch();
        return;
    }
    FILE *fb = fopen(argv[1], "rb+");
    if (fb == NULL)
    {
        printf("Error: не удалось открыть двоичный файл %s\n", argv[1]);
        printf("Press ENTER");
        getch();
        return;
    }
    TStud Stud;
    int kol = 0, nr = 1, nw = 1, flag;
    nr = fread(&Stud, sizeof(Stud), 1, fb);
    while (nr == 1 && nw == 1)
    {
        printf("Считана запись:\n");
        printf("%25s%20s%25s%2d%2d%2d\n", Stud.FIO.F,
               Stud.FIO.I, Stud.FIO.O, Stud.o1, Stud.o2, Stud.o3);
        flag = 0;
        if (Stud.o1 < 2)
        {
            Stud.o1 = 2;
            flag = 1;
        }
        if (Stud.o2 < 2)
        {
            Stud.o2 = 2;
            flag = 1;
        }
        if (Stud.o3 < 2)
        {
            Stud.o3 = 2;
            flag = 1;
        }
        if (Stud.o1 > 5)
        {
            Stud.o1 = 5;
            flag = 1;
        }
        if (Stud.o2 > 5)
        {
            Stud.o2 = 5;
            flag = 1;
        }
        if (Stud.o3 > 5)
        {
            Stud.o3 = 5;
            flag = 1;
        }
        if (flag)
        {
            kol++;
            fseek(fb, 0 - sizeof(Stud), SEEK_CUR);
            nw = fwrite(&Stud, sizeof(Stud), 1, fb);
            fseek(fb, 0, SEEK_CUR);
            printf("Сделана корректировка:\n");
            printf("%25s%20s%25s%2d%2d%2d\n", Stud.FIO.F,
                   Stud.FIO.I, Stud.FIO.O, Stud.o1, Stud.o2, Stud.o3);
        }
        nr = fread(&Stud, sizeof(Stud), 1, fb);
    }
    if (kol == 0)
        printf("Ни одной корректировки\n");
    else
        printf("Всего корректировок: %d\n", kol);
    fclose(fb);
    printf("Press any key to continue");
    getch();
    return;
}
//------------------главная функция-----------------------
int main(int argc, char *argv[])
{
    char ch;
    SetConsoleOutputCP(1251);
    do
    {
        printf("\nN - создать новый тип.файл; F - сразу поиск;\ 
 C - коррекция; E - конец.\nВаш выбор?");
        ch = getchar();
        fflush(stdin);
        ch = toupper(ch);
        switch (ch)
        {
            //----------первая часть: создание двоичного из текстового
        case 'N':
            CreateBinaryFile(argc, argv);
            break;
            //-------------- вторая часть: поиск в двоичном файле ----
        case 'F':
            FindIVAN(argc, argv);
            break;
            //-------третья часть: корректировка в двоичном файле ----
        case 'C':
            CorrectFile(argc, argv);
            break;
            //-----------выход----------------------------------------
        case 'E':
            return 0;
            //--------------------------------------------------------
        default:
            printf("Нет такой команды\nPress any key");
            getch();
        }
    } while (ch != 'E');
    return 0;
}