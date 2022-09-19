#include <stdio.h> 
#include <math.h>
#include <stdlib.h>

int *vvod(int* n, int *mas, FILE *fin, FILE *fout)
{
	int i;
	fscanf(fin, "%d", n);
	fprintf(fout, "n=%d\n", *n);
	mas = calloc(*n, sizeof(int));
	for (i = 0; i < *n; i++)
		fscanf(fin, "%d", &mas[i]);
	fprintf(fout, "mas:\n"); // вывод на экран
	for (i = 0; i < *n; i++)
		fprintf(fout, "%d ", mas[i]); // вывод в 10с/с элементов массива через два пробела

	fprintf(fout, "\n");
	return mas;
}

int kv(int *mas, int i, int j)
{
	int s;
	if (i == j)
	{
		if (pow(pow(mas[i], 2) + 1, 1. / 3) > 20)
		{
			printf("%10d %10.5f\n", mas[i], pow(pow(mas[i], 2) + 1, 1. / 3));

			return 1;
		}
		else return 0;
	}
	else
	{
		return (kv(mas, i + ((j - i) / 2) + 1, j) + kv(mas, i, i + ((j - i) / 2)));
	}
}

int main(int argc, char *argv[])
{
	int n, *mas, i, s = 0;
	FILE *fin, *fout;

	if ((fin = fopen(argv[1], "rt")) == NULL)
	{
		printf("Errror: Failed while opening file %s for reading\nPress enter", argv[1]);
		getchar(); 
		return 0;  
	}
	if((fout = fopen(argv[2], "wt")) == NULL)
	{
		printf("Errror: Failed while opening %s for writing\nPress enter", argv[2]);
		fclose(fin);
		getchar();
		return 0; 
	}

	mas = vvod(&n, mas, fin, fout);

	s = kv(mas, 0, n - 1);
	fprintf(fout, "%d\n", s);
	free(mas);
	fclose(fin);
	fclose(fout);
	printf("\nPress enter To exit\n");
	return 0;
}