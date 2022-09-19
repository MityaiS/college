#include <stdio.h>
#include "test2.c"

int main() {
    // FILE *f;
    // f = fopen("test.txt", "r");
    // char line[150];

    // while (!feof(f)) {
    //     fgets(line, 150, f);
    //     printf("%s\n", line);
    // }
    // fclose(f);
    // int **arr = malloc(sizeof(int*) * 3);
    // for (int i = 0; i < 3; i++) 
    // {
    //     arr[i] = malloc(sizeof(int) * 3);
    // }
    // return 0;
    printf("%d\n", sizeof(short));
    printf("%d\n", getsumo(15, 10));
    return 0;
}

