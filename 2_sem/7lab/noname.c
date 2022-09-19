#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXKV 1000	 //����. ����� ��������
#define MAXSTR 31	 //����. ����� ������
#define MINYEAR 2000 //����������� ���
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
{ //�������� ������������ ������ ��������
	if (Zakaz.Kv < 1 || Zakaz.Kv > MAXKV)
		return 0;
	return 1;
}
int CorrectDate(struct TZakaz Zakaz)
{ //�������� ������������ ����
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
{ //���� ������ ��������
	while (!CorrectKv(Zakaz))
	{
		printf("\n������������ �������� ������ �������� - %d", Zakaz.Kv);
		printf("\n������� ����� �������� (1..%d)", MAXKV);
		if (scanf("%d", &Zakaz.Kv) != 1)
		{
			Zakaz.Kv = 0;
			fflush(stdin);
		}
	}
}
void GetDate(struct TZakaz Zakaz)
//���� ����
{
	while (!CorrectDate(Zakaz))
	{
		printf("\n������������ �������� ���� - %d %d %d", Zakaz.D, Zakaz.M, Zakaz.Y);
		printf("\n������� ��� �����: ���� ����� ���\n");
		if (scanf("%d %d %d", &Zakaz.D, &Zakaz.M, &Zakaz.Y) != 3)
		{
			Zakaz.Y = 0;
			fflush(stdin);
		}
	}
}
void InitFileName(char *tname, char *bname)
//��������� ���� ���������� � ��������� ������
{
	printf("��������� ����: ");
	gets(tname);
	printf("�������� ����: ");
	gets(bname);
}
void PrintZakaz(struct TZakaz Zakaz)
//����� ������ � ������ �� �����
{
	printf("\n%-30s%-30s%-5d%02d\/%02d\/%4d", Zakaz.Street, Zakaz.Dom, Zakaz.Kv, Zakaz.D, Zakaz.M, Zakaz.Y);
}
int GetFileStr(FILE *f, char *s, char razd, int max)
//���������� �� ����� ������ �� ��������������� �������
//���� �� ������������ �����
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
//---------- �������� ��������� �� ����������
void CreateBinaryFile(char *tname, char *bname)
{
	if (bname[0] == 0)
	{
		printf("��� BIN-����� �� ������. ����������� ����� ���� 5\n");
		return;
	}
	if (tname[0] == 0)
	{
		printf("��� ���������� ����� �� ������. ����������� ����� ���� 5\n");
		return;
	}
	FILE *ft = fopen(tname, "r");
	if (ft == NULL)
	{
		printf("Error: �� ������� ������� ��������� ���� %s � �������\n", tname);
		printf("Press enter");
		getchar();
		return;
	}
	FILE *fb = fopen(bname, "wb");
	if (fb == NULL)
	{
		fclose(ft);
		printf("Error: �� ������� ������� �������� ���� %s\n", bname);
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
			printf("������ ������ ����� � %i ������", kol);
			break;
		}
		// ���� �����
		//������� ����� ����� - ������� ** ��� ����� �����
		if (strcmp(s, "**") == 0 || feof(ft))
			break;
		strcpy(Zakaz.Street, s);
		if (!GetFileStr(ft, &s[0], ',', MAXSTR))
		{
			printf("������ ������ ���� � %i ������", kol);
			break;
		}
		strcpy(Zakaz.Dom, s);
		if (!GetFileStr(ft, &s[0], ',', MAXSTR))
		{
			printf("������ ������ �������� � %i ������", kol);
			break;
		}
		Zakaz.Kv = atoi(s);
		if (!GetFileStr(ft, &s[0], ',', MAXSTR))
		{
			printf("������ ������ ���� � %i ������", kol);
			break;
		}
		Zakaz.D = atoi(s);
		if (!GetFileStr(ft, &s[0], ',', MAXSTR))
		{
			printf("������ ������ ������ � %i ������", kol);
			break;
		}
		Zakaz.M = atoi(s);
		if (!GetFileStr(ft, &s[0], '\n', MAXSTR))
		{
			printf("������ ������ ���� � %i ������", kol);
			break;
		}
		Zakaz.Y = atoi(s);
		nw = fwrite(&Zakaz, sizeof(Zakaz), 1, fb);
		kol++;
	}
	if (nw != 1)
		printf("Error: ������ ��� ������");
	fclose(ft);
	fclose(fb);
	printf("������ �������� ���� �� %d ������� �� %d ����\n", kol, sizeof(Zakaz));
	printf("Press any key to continue");
	getch();
	return;
}
void getstr(char *s)
//���������� ������ � ������������� �� ��������� ���������
{
	gets(s);
	s[MAXSTR - 1] = 0;
	fflush(stdin);
}
void CreateMask(struct TZakaz Mask)
//�������� ������� ������
{
	char s[MAXSTR];
	printf("�������� ������� ������. ������� ������� �������� ���� ������ *\n");
	printf("�����: ");
	getstr(&s[0]);
	strcpy(Mask.Street, s);
	printf("���: ");
	getstr(&s[0]);
	strcpy(Mask.Dom, s);
	printf("��������: ");
	getstr(s);
	if (strcmp(s, "*"))
		Mask.Kv = atoi(s);
	else
		Mask.Kv = 0;
	printf("����: ");
	getstr(s);
	if (strcmp(s, "*"))
		Mask.D = atoi(s);
	else
		Mask.D = 0;
	printf("�����: ");
	getstr(s);
	if (strcmp(s, "*"))
		Mask.M = atoi(s);
	else
		Mask.M = 0;
	printf("���: ");
	getstr(s);
	if (strcmp(s, "*"))
		Mask.Y = atoi(s);
	else
		Mask.Y = 0;
}
int Compare(struct TZakaz Zakaz, struct TZakaz Mask)
//��������� Zakaz �� ������������ ����� ������
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
//����� � �������� ����� ----
{
	if (bname[0] == 0)
	{
		printf("��� ����� �� ������. ����������� ����� ���� 5\n");
		return;
	}
	FILE *fb = fopen(bname, "rb");
	if (fb == NULL)
	{
		printf("Error: �� ������� ������� �������� ���� %s\n", bname);
		printf("Press any key...");
		getch();
		return;
	}
	struct TZakaz Zakaz, Mask;
	CreateMask(Mask);
	printf("��������� ������\n");
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
		printf("������, ��������������� �������, �� �������\n");
	else
		printf("\n����� �������: %d\n", kol);
	fclose(fb);
	printf("Press any key to continue");
	getch();
	return;
}
void CorrectFile(char *bname)
//������������� � �������� ����� ----
{
	if (bname[0] == 0)
	{
		printf("��� ����� �� ������. ����������� ����� ���� 5\n");
		return;
	}
	FILE *fb = fopen(bname, "rb+");
	if (fb == NULL)
	{
		printf("Error: �� ������� ������� �������� ���� %s\n", bname);
		printf("Press any key");
		getch();
		return;
	}
	struct TZakaz Zakaz;
	int kol = 0, nr = 1, nw = 1, flag;
	nr = fread(&Zakaz, sizeof(Zakaz), 1, fb);
	while (nr == 1 && nw == 1)
	{
		printf("\n������� ������:\n");
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
			printf("������� �������������:\n");
			PrintZakaz(Zakaz);
		}
		nr = fread(&Zakaz, sizeof(Zakaz), 1, fb);
	}
	if (kol == 0)
		printf("�� ����� �������������\n");
	else
		printf("����� �������������: %d\n", kol);
	fclose(fb);
	printf("Press any key to continue");
	getch();
	return;
}
void PrintBinFile(char *bname)
//����� ��������� ����� �� �����
{
	if (bname[0] == 0)
	{
		printf("��� ����� �� ������. ����������� ����� ���� 5\n");
		return;
	}
	FILE *fb = fopen(bname, "rb");
	if (fb == NULL)
	{
		printf("Error: �� ������� ������� �������� ���� %s\n", bname);
		printf("Press any key..,");
		getch();
		return;
	}
	struct TZakaz Zakaz;
	int kol = 0, nr = 1;
	nr = fread(&Zakaz, sizeof(Zakaz), 1, fb);
	if (!nr)
	{
		printf("������ ����\n");
		return;
	}
	printf("�����\t\t\t      ���\t\t\t    ��.  ����\n");
	while (nr)
	{
		if (nr > 0)
			PrintZakaz(Zakaz);
		nr = fread(&Zakaz, sizeof(Zakaz), 1, fb);
		kol++;
	}
}
void printmenu() //����
{
	printf("\n1 - ������� ����� BIN-����");
	printf("\n2 - �����");
	printf("\n3 - ���������");
	printf("\n4 - ��������");
	printf("\n5 - ������ ����� ������");
	printf("\nE - �����\n");
}
//------------------������� �������-----------------------
int main(int argc, char *argv[])
{
	char ch = 0;
	char tname[100], bname[100];
	strcpy(tname, "1.txt");
	strcpy(bname, "2.txt");
	if (argc < 2)
	{
		printf("����� ������ �� ������. ����������� �������� �� ���������\n");
		printf("��������� ����: %s\n�������� ����: %s", tname, bname);
	}
	else
	{
		if (argc > 2)
			strcpy(tname, argv[2]);
		if (argc > 1)
			strcpy(bname, argv[1]);
		printf("������� ���������\n");
		printf("��������� ����: %s\n�������� ����: %s", tname, bname);
	}
	while (ch != 'E')
	{
		printmenu();
		ch = getchar();
		getchar();
		switch (ch)
		{
			//---------- �������� ��������� �� ����������
		case '1':
			CreateBinaryFile(tname, bname);
			break;
			//-------------- ����� � �������� ����� ----
		case '2':
			Find(bname);
			break;
			//------- ������������� � �������� ����� ----
		case '3':
			CorrectFile(bname);
			break;
			//------- �������� � �������� ����� ----
		case '4':
			PrintBinFile(bname);
			break;
			//������ ����� ������
		case '5':
			InitFileName(&tname[0], &bname[0]);
			break;
			//-----------�����----------------------------------------
		case 'E':
			return 0;
			//--------------------------------------------------------
		}
	}
	return 0;
}