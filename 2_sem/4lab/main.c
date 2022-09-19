#include <math.h>  // fabs, pow, ceil\floor, log, log10, exp, sqrt
#include <stdio.h> // printf, scanf
#include <time.h>
#include <stdlib.h> // randomize, rand
//---------------------------------------------------------------------------
const double xx[7] = {0.00001, -0.99, -1, -0.1, 0.1, 1, 0.99};

int main()
{
	int n, i, k, z;
	double e, sl, sum, f, *x; // четыре простого типа и один – дин.массив(указатель)
	// randomize();
	srand(time(NULL));
	printf("Type e=? "); // приглашение – шрифт Lucida Console нужен
	scanf("%lf", &e);	 // ввод числа с плавающей точкой двойной точности(%lf) e
	char ch;
	scanf("%c", &ch);
	if (e < 1e-13 || e > 0.11)
	{
		printf("Incorrect precision e (0..0.1] \nPress enter");
		getchar(); // ожидание нажатия клавиши
		return 0;  // выход из функции main
	}
	fflush(stdin);		 // очищаем буфер (лишние символы после ввода e)
	printf("Type n=? "); // приглашение
	scanf("%d", &n);	 // ввод десятичного(%d) n
	scanf("%c", &ch);
	if (n < 1 || n > 20)
	{
		printf("Invalid n [1..20]! \nPress enter");
		getchar(); // ожидание нажатия клавиши
		return 0;  // выход из функции main
	}
	fflush(stdin);
	// x = new double[n]; // выделяем память для n элементов массива
	x = calloc(n, sizeof(double));
	printf("Pass n=%d value X from (-1,+1):\n", n); // приглашение
	for (i = 0; i < n; i++)
	{						 // ввод x[0]...x[n-1]
		scanf("%lf", &x[i]); // типа long float (%lf)
		if (fabs(x[i]) >= 1)
		{
			x[i] = xx[rand() % 7]; // одно из семи значений массива xx
			if (fabs(x[i]) == 1)
			{
				x[i] = x[i] * (rand() % 100) / 100;
				if (x[i] == 0)
					x[i] = e; // для некоторых вариантов x=/=0
			}
			printf("Incorrect value replaced by %15.10lf\n", x[i]);
		}
	}
	z = ceil(fabs(log(e) / log(10.0))) + 1;
	printf("e = %*.*lf\n", z + 2, z, e); // вывод e:(z+2):z
	printf("N |        X        |      Sum(X)     | K|       F(X)      |  "
		   "|Sum(X)-F(X)|\n");
	for (i = 1; i < 80; i++)
		printf("=");
	printf("\n");
	for (i = 0; i < n; i++)
	{
		// поиск суммы ряда
		sum = sl = x[i] / 2; // sl=pow(x[i],2); sum=sl;  // ïåðâîå ñëàãàåìîå
		k = 1;
		while ((fabs(sl) >= e) && (k != 50000))
		{
			sl *= -x[i] * (2 * k -1) / (2 * k);
			sum += sl;
		}
		f = 1 - 1 / sqrt(x[i] + 1);
		printf("%2d|%17.*lf|%17.*lf|%2d|%17.*lf|%17.*lf\n", i + 1, z, x[i], z, sum,
			   k, z, f, z + 2, fabs(sum - f));
	}
	// delete[] x; //  освобождение памяти для одномерного дин.массива
	free(x);
	printf("Press enter\n");
	scanf("%c", &ch);
	getchar();
	return 0;
}