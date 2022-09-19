#include <windows.h> // SetConsoleOutputCP, SetConsoleCP
#include <stdio.h>   //printf , fgets
#include <conio.h>   // getch
#include <string.h>  // strcpy, strncmp, strchr
//---------------------------------------------------------------------------
struct TInfo
{
    char FamIO[31];
    int Ball;
};
struct TElem
{                // моделирование стека на основе односвязного списка
    TInfo Info;  //  или struct TInfo Info;
    TElem *Next; // или struct TElem *Next; здесь и далее
};
//-----------------------прототипы-------------------------------------------
TElem *PushStack(TElem *St, TInfo Info); // добавить элемент в стек
TInfo PopStack(TElem **PSt);             //извлечь элемент из стека
// дополнительная процедура перекладывания элемента из одного стека (StTop) в другой(Dop)
void TopToTop(TElem **PSt1, TElem **PSt2); // без изменения адресов элементов, только связи
//----------первая часть: создание стека из текстового файла
TElem *CreateStack(TElem *St);
//----------вторая часть: вывод стека на экран ------
void OutputStack(TElem *&St);
//----------третья часть: решение задачи -------------
TElem *Decide(TElem **PSt1, TElem *St2);
//----------четвертая часть: освобождение памяти -----
TElem *FreeStack(TElem *St);
//---------------------------------------------------------------------------
int main()
{
    TElem *StackTop1 = NULL, *StackTop2 = NULL;
    char ch;
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    do
    {
        printf("\nN - создать новый стек; V - вывод; D - решение; F - освободить; \ 
E - конец.\nВаш выбор?");
        ch = getchar();
        fflush(stdin);
        ch = toupper(ch);
        switch (ch)
        {
            //----------первая часть: создание стека из текстового
        case 'N':
            if (StackTop1)
            {
                printf("Error: сначала надо освободить память!");
                break;
            }
            StackTop1 = CreateStack(StackTop1);
            break;
            //----------вторая часть: вывод стеков на экран ------
        case 'V':
            printf("Первый стек:\n");
            OutputStack(StackTop1);
            printf("\nВторой стек (отличники):\n");
            OutputStack(StackTop2);
            break;
            //----------третья часть: решение задачи -------------
        case 'D':
            StackTop2 = Decide(&StackTop1, StackTop2);
            break;
            //----------четвертая часть: освобождение памяти -----
        case 'F':
            StackTop1 = FreeStack(StackTop1);
            StackTop2 = FreeStack(StackTop2);
            printf("Вся память под стеки особождена\n");
            break;
            //-----------------------выход------------------------
        case 'E':
            return 0;
        default:
            printf("Нет такой команды\nPress any key");
            getch();
        }
    } while (ch != 'E');
    return 0;
}
//---------------------------------------------------------------------------
TElem *PushStack(TElem *St, TInfo Info)
{ // добавить элемент в стек
    TElem *Elem = new TElem;
    Elem->Info.Ball = Info.Ball;
    strcpy(Elem->Info.FamIO, Info.FamIO);
    Elem->Next = St;
    return Elem; // Адрес новой вершины
}
TInfo PopStack(TElem **PSt)
{ //извлечь элемент из стека
    TElem *Elem = *PSt;
    TInfo Info = Elem->Info;
    *PSt = Elem->Next;
    delete Elem;
    return Info;
}
// дополнительная процедура перекладывания элемента из одного стека (StTop) в другой(Dop)
void TopToTop(TElem **PSt1, TElem **PSt2)
{
    TElem *Elem, *StTop = *PSt1, *Dop = *PSt2;
    Elem = StTop;
    StTop = StTop->Next; // или StTop=(*StTop).Next;
    Elem->Next = Dop;
    Dop = Elem;
    *PSt1 = StTop;
    *PSt2 = Dop; // сохранить новые адреса вершин по адресам PSt1 и PSt2
    return;
}
//----------первая часть: создание стека из текстового
TElem *CreateStack(TElem *St)
{
    int kol = 0;
    char *n, *r;
    TInfo Info;
    char Balls[5];
    while (1)
    {
        printf("FamIO (или **)=?");
        fgets(Info.FamIO, 30, stdin);
        fflush(stdin);
        n = strchr(Info.FamIO, '\n');
        if (n)
            Info.FamIO[n - Info.FamIO] = '\0';
        if (strncmp(Info.FamIO, "**", 2) == 0)
            break; // условие окончания ввода - два первых символа **
        printf("Ball =?");
        fgets(Balls, 4, stdin);
        fflush(stdin);
        Info.Ball = atoi(Balls);
        St = PushStack(St, Info);
        kol++;
    }
    printf("Создан стек из %d элементов\n", kol);
    printf("Press any key to continue");
    getch();
    return St;
}
//----------вторая часть: вывод стека на экран ------
void OutputStack(TElem *St)
{
    TElem *Dop = NULL;
    TInfo inf;
    if (!St)
        printf("пустой\n");
    while (St)
    {
        inf = PopStack(&St);
        printf("%30s %3d\n", inf.FamIO, inf.Ball);
        Dop = PushStack(Dop, inf);
    }
    while (Dop)
        TopToTop(&Dop, &St);
    printf("Press any key to continue");
    getch();
    return;
}
//----------третья часть: решение задачи -------------
TElem *Decide(TElem **PSt1, TElem *St2)
{
    TElem *St1 = *PSt1, *Dop = NULL;
    St2 = FreeStack(St2);
    int Sum = 0, N = 0;
    while (St1)
    {
        Sum += St1->Info.Ball;
        N++;
        if (St1->Info.Ball >= 85)
            St2 = PushStack(St2, St1->Info); // отличники
        TopToTop(&St1, &Dop);
    }
    while (Dop)
        TopToTop(&Dop, &St1);
    if (N)
        printf("Средний балл = %6.2f\n", (float)Sum / N);
    else
        printf("Стек пуст\n");
    printf("Press any key to continue");
    getch();
    *PSt1 = St1; // новый адрес через параметр (изменение по адресу)
    return St2;  // новый адрес через результат функции вернется
}
//----------четвертая часть: освобождение памяти -----
TElem *FreeStack(TElem *St)
{
    TInfo Info;
    while (St)
    {
        Info = PopStack(&St);
    }
    return St;
}
//---------------------------------------------------------------------------