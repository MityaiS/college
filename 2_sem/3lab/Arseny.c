#include <stdio.h>

typedef struct node
{
    int inf;
    node* next;
    node* prev;
} node;



void create_list(node* Beg, node* End, char* file_n)
{
    FILE* file;
    file = fopen(file_n, "r");
    int info;
    node* Elem = malloc(sizeof(node));
    while (file != EOF && file != NULL)
    {  
        fscanf("%d", &info);
        Elem->inf = info;
    }
}

void add_last(node** End, int info)
{
    node* Elem = malloc(sizeof(node));
    Elem->inf = info;
    (*End)->next = Elem;
    Elem->next = NULL;
    Elem->prev = *End;
    *End = Elem;
}

void add_cur(node* Beg, int k, int info)
{
    node* Elem = malloc(sizeof(node));

}

void free_list(node* Top)
{
    node* Elem = Top;
    while(Elem)
    {
        Top = Top->next;
        free(Elem);
        Elem = Top;
    }
    
}

void fdf(int x)
{
    x = 5;
}

int main()
{
    int y = 6;
    fdf(y);
    node* Beg = NULL;
    node* End = NULL;
    char* file_n = "in.txt";
    create_list(Beg, End, char* file_n)
}