#include <iostream>
#include <limits>
using namespace std;

template <typename T>
int get_abs_min(T arr[], int size)
{
    int num = 0;
    for (int i = 1; i < size; i++)
    {
        if (abs(arr[num]) > abs(arr[i]))
            num = i;
    }
    return (num + 1);
}

template <typename T>
T get_sum_abs(T arr[], int size)
{
    int Passed = 0;
    T sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (Passed)
            sum += abs(arr[i]);
        if (arr[i] < 0)
            Passed = 1;
    }
    return sum;
}

template <typename T>
void insertion_sort(T *arr, int size)
{
    T key;
    int j;
    for (int i = 0; i < size; i++)
    {
        key = arr[i];
        j = i;
        while (j > 0 && arr[j - 1] < key)
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

template<typename T>
void fill_arr(T *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "Type the element of an array(-1000 < x < 1000): ";
        cin >> arr[i];
        while (!cin.good() or arr[i] >= 1000 or arr[i] <= -1000)
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max()), '\n');
            cout << "Type the correct element: ";
            cin >> arr[i];
        }
    }
}

template<typename T>
void output(T *arr, int size)
{
    cout << "Number of min of absulute values is " << get_abs_min(arr, size) << endl;
    cout << "Sum of absolute values after first negative is " << get_sum_abs(arr, size) << endl;
    insertion_sort(arr, size);
    cout << "Elements of an array in descending order: ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    cout << "Welcome to my awesome program. What type of an array you want to use?" << endl
         << "Integer(i), float(f), double(d): ";
    char ans;
    cin >> ans;
    ans = tolower(ans);
    while (ans != 'i' and ans != 'f' and ans != 'd')
    {
        cout << "Type the correct answere(I/f/d): ";
        cin >> ans;
        ans = tolower(ans);
    }
    cout << "What is the size of the array you want to craete?(0 < n < 100): ";
    int n;
    cin >> n;
    while (!cin.good() or n >= 100 or n < 1)
    {
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max()), '\n');
        cout << "Type the correct n: ";
        cin >> n;
    }
    char s_type;
    if (ans == 'i' or ans == 'f')
        s_type = 4;
    else
        s_type = 8;
    char arr[s_type * n];
    if (ans == 'i')
    {
        int *arr_i = (int *)arr;
        fill_arr(arr_i, n);
        output(arr_i, n);
    }
    else if (ans == 'f')
    {
        float *arr_f = (float *)arr;
        fill_arr(arr_f, n);
        output(arr_f, n);
    }
    else
    {
        double *arr_d = (double *)arr;
        fill_arr(arr_d, n);
        output(arr_d, n);
    }

}