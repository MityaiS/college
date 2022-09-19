#include <stdio.h>
#include <string.h>
#define MAXST 31

struct TOrder
{
    struct address
    {
        char street[MAXST];
        int house;
        int apartment;
    } address;
    struct date
    {
        int year;
        int month;
        int day;
    } date;
};

char *UpperCase(char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] = s[i] - 32;
        }
    }
    return s;
}

void Find(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Too less parameters\nPress enter");
        getchar();
        return;
    }
    FILE *fb = fopen(argv[1], "rb");
    if (fb == NULL)
    {
        printf("Error: Failed to open bin file %s\n", argv[1]);
        printf("Press ENTER");
        getchar();
        return;
    }
    struct TOrder Order;
    int kol = 0, nr = 1;
    while (nr)
    {
        nr = fread(&Order, sizeof(Order), 1, fb);
        if (nr > 0)
            if (Order.date.day == 15 && Order.date.month == 5 &&
                Order.date.year == 2015 &&
                strcmp(UpperCase(Order.address.street), "MOSCOW") == 0)
            {
                kol++;
            }
    }
    if (kol == 0)
        printf("Orders corresponded your request not found\n");
    else
        printf("Found: %d records\n", kol);
    fclose(fb);
    printf("Press enter to continue");
    getchar();
    return;
};

void CreateBinaryFile(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Too less paramenters\nPress enter");
        getchar();
        return;
    }
    FILE *ft = fopen(argv[2], "rt");
    if (ft == NULL)
    {
        printf("Error: failed to open a file with origin data %s\n", argv[2]);
        printf("Press enter ");
        getchar();
        return;
    }
    FILE *fb = fopen(argv[1], "wb");
    if (fb == NULL)
    {
        fclose(ft);
        printf("Error: failed to create bin file %s\n", argv[1]);
        printf("Press enter");
        getchar();
        return;
    }
    struct TOrder Order; // либо struct TOrder Order; в С
    int kol = 0, nw = 1;
    char s[10];
    while (nw)
    {
        fscanf(ft, "%30s", Order.address.street); // ввод слова
        //признак конца файла - улица ** или конец файла
        if (strcmp(Order.address.street, "**") == 0 || feof(ft))
            break;
        fscanf(ft, "%s", s);
        Order.address.house = atoi(s);
        fscanf(ft, "%s", s);
        Order.address.apartment = atoi(s);
        fscanf(ft, "%s", s);
        Order.date.year = atoi(s);
        fscanf(ft, "%s", s);
        Order.date.month = atoi(s);
        fscanf(ft, "%s", s);
        Order.date.day = atoi(s);
        nw = fwrite(&Order, sizeof(Order), 1, fb);
        kol++;
    }
    if (nw != 1)
        printf("Error: Failed while recording");
    fclose(ft);
    fclose(fb);
    printf("Created binary file from %d records, %d byte each\n",
           kol, sizeof(struct TOrder));
    printf("Press enter to continue");
    getchar();
    return;
}

void CorrectFile(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Too less parameters\nPress enter");
        getchar();
        return;
    }
    FILE *fb = fopen(argv[1], "rb+");
    if (fb == NULL)
    {
        printf("Error: Failed to open bin file %s\n", argv[1]);
        printf("Press ENTER");
        getchar();
        return;
    }
    struct TOrder Order;
    int kol = 0, nr = 1, nw = 1, flag;
    nr = fread(&Order, sizeof(Order), 1, fb);
    while (nr == 1 && nw == 1)
    {
        printf("Recorded order:\n");
        printf("%30s%10d%10d%10d%10d%10d\n", Order.address.street,
               Order.address.house, Order.address.apartment, Order.date.year, Order.date.month, Order.date.day);
        flag = 0;
        if (Order.address.apartment < 1)
        {
            Order.address.apartment = 1;
            flag = 1;
        }
        if (Order.date.day > 31)
        {
            Order.date.day = 31;
            flag = 1;
        }
        if (Order.date.month > 12)
        {
            Order.date.month = 12;
            flag = 1;
        }
        if (Order.date.month < 1)
        {
            Order.date.month = 1;
            flag = 1;
        }
        if (flag)
        {
            kol++;
            fseek(fb, 0 - sizeof(Order), SEEK_CUR);
            nw = fwrite(&Order, sizeof(Order), 1, fb);
            fseek(fb, 0, SEEK_CUR);
            printf("Adjustment made:\n");
            printf("%30s%10d%10d%10d%10d%10d\n", Order.address.street,
               Order.address.house, Order.address.apartment, 
               Order.date.year, Order.date.month, Order.date.day);
        }
        nr = fread(&Order, sizeof(Order), 1, fb);
    }
    if (kol == 0)
        printf("No adjustments\n");
    else
        printf("Total adjustments: %d\n", kol);
    fclose(fb);
    printf("Press enter to continue");
    getchar();
    return;
}

int main(int argc, char *argv[])
{
    char ch;
    do
    {
        printf("\nN - create new bin file; F - immediately search; C - corection; E - the end.\nYour choice?");
        ch = getchar();
        getchar();
        ch = toupper(ch);
        switch (ch)
        {
        case 'N':
            CreateBinaryFile(argc, argv);
            break;
        case 'F':
            Find(argc, argv);
            break;
        case 'C':
            CorrectFile(argc, argv);
            break;
        case 'E':
            return 0;
        default:
            printf("There is no such command\nPress enter");
            getchar();
        }
    } while (ch != 'E');
    return 0;
}