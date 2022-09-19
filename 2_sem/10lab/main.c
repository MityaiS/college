#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h> //Я пишу на Linux, поэтому для имплементации Unicode
//                    он мне нужен

struct TElem
{
    wchar_t Info;
    struct TElem *Next;
};

struct TElem *PushStack(struct TElem *St, wchar_t Info);
wchar_t PopStack(struct TElem **PSt);
void TopToTop(struct TElem **PSt1, struct TElem **PSt2);
struct TElem *CreateStack(struct TElem *St);
void OutputStack(struct TElem *St);
struct TElem *FreeStack(struct TElem *St);
void Decide(struct TElem **PSt1, struct TElem **PSt2);

struct TElem *PushStack(struct TElem *St, wchar_t Info)
{
    struct TElem *Elem = (struct TElem *)malloc(sizeof(struct TElem));
    Elem->Info = Info;
    Elem->Next = St;
    return Elem;
}

wchar_t PopStack(struct TElem **PSt)
{
    struct TElem *Elem = *PSt;
    int Info = Elem->Info;
    *PSt = Elem->Next;
    free(Elem);
    return Info;
}

void TopToTop(struct TElem **PSt1, struct TElem **PSt2)
{
    struct TElem *Elem, *StTop = *PSt1, *Dop = *PSt2;
    Elem = StTop;
    StTop = StTop->Next;
    Elem->Next = Dop;
    Dop = Elem;
    *PSt1 = StTop;
    *PSt2 = Dop;
    return;
}

struct TElem *CreateStack(struct TElem *St)
{
    setlocale(LC_ALL, "");
    int kol = 0;
    char ch;
    wchar_t Info = L'П';
    while (1)
    {
        printf("What's the letter (or *)=?");
        getchar();
        wscanf(L"%lc", &Info);
        if (Info == L'*')
            break;
        St = PushStack(St, Info);
        kol++;
    }
    printf("Created stack from %d elements\n", kol);
    printf("Press enter key to continue");
    getchar();
    return St;
}

void OutputStack(struct TElem *St)
{
    struct TElem *Dop = NULL;
    wchar_t inf;
    if (!St)
        printf("it's free\n");
    while (St)
    {
        inf = PopStack(&St);
        wprintf(L"%1lc\n", inf);
        Dop = PushStack(Dop, inf);
    }
    while (Dop)
        TopToTop(&Dop, &St);
    printf("Press enter key to continue");
    getchar();
    return;
}

struct TElem *FreeStack(struct TElem *St)
{
    wchar_t Info;
    while (St)
    {
        Info = PopStack(&St);
    }
    return St;
}

void Decide(struct TElem **PSt1, struct TElem **PSt2)
{
    struct TElem *Elem, *Dop1, *Dop2, *St1 = *PSt1, *St2 = *PSt2;
    St2 = FreeStack(St2);
    while (St1)
    {
        wchar_t inf = St1->Info;
        if ((inf > 64 && inf < 91) || (inf > 96 && inf < 123)) //латинская ли буква
        {
            TopToTop(&St1, &Dop1); //если да, перемещаем в доп стек с латинскими не выделяя новую память
        }
        else
        {
            TopToTop(&St1, &Dop2); //если нет, в доп стек с остальными
        }
    }
    while (Dop1)
    {
        TopToTop(&Dop1, &St1); //надо перевернуть стек так, как он был задом наперед
    }
    while (Dop2)
    {
        TopToTop(&Dop2, &St2);
    }
    *PSt1 = St1;
    *PSt2 = St2;
    return;
}

int main()
{
    struct TElem *StackTop1 = NULL, *StackTop2 = NULL;
    char ch, che;
    setlocale(LC_ALL, "");
    do
    {
        printf("\nN - create new stack; V - output; D - solve problem; F - free; \
E - end.\nYour choice?");
        ch = getchar();
        while ((che = getchar()) != '\n' && che != EOF)
            ;
        ch = toupper(ch);
        switch (ch)
        {
        case 'N':
            if (StackTop1)
            {
                printf("Error: free the memory first!");
                break;
            }
            StackTop1 = CreateStack(StackTop1);
            break;
        case 'V':
            printf("First stack(latin):\n");
            OutputStack(StackTop1);
            printf("\nSecond stack(other):\n");
            OutputStack(StackTop2);
            break;
        case 'D':
            Decide(&StackTop1, &StackTop2);
            break;
        case 'F':
            StackTop1 = FreeStack(StackTop1);
            StackTop2 = FreeStack(StackTop2);
            printf("All the memory for stacks is free\n");
            break;
        case 'E':
            return 0;
        default:
            printf("There is no such command\nPress any key");
            getchar();
        }
    } while (ch != 'E');
    return 0;
}
