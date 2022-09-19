#include <stdio.h>
#include <stdlib.h>
#include "unit.c"

int main()
{
    int size, **B = NULL, *C = NULL;
    const char *readFile = "input.txt";
    const char *writeFile = "output.txt";

    FILE *file;
    file = fopen(readFile, "r");
    if (!file)
    {
        printf("File isn't opened!\n");
        return 0;
    }
    fscanf(file, "%d", &size);

    B = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; ++i)
    {
        B[i] = (int *)malloc(size * sizeof(int));
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            fscanf(file, "%d", &B[i][j]);
        }
    }

    C = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i)
    {
        fscanf(file, "%d", &C[i]);
    }

    fclose(file);

    if (MainTask(B, C, size))
    {
        printf("Array wasn't changed!\nPress enter");
        getchar();
        FreeMemory(B, C, size);
        return 1;
    }
    WriteFile(writeFile, C, size);
    printf("Array was changed!\nPress enter");
    getchar();
    FreeMemory(B, C, size);
    return 0;
}