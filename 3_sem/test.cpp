#include <iostream>
using namespace std;


void insertion_sort(int *arr, int size)
{
    int key;
    int j;
    for (int i = 1; i < size; i++)
    {
        key = arr[i];
        j = i;
        while(j > 0 && arr[j-1] < key)
        {
            arr[j] = arr[j-1];
            j--;
        }
        arr[j] = key;
    }
}

int main()
{
    int arr[5] = {1,2,3,4,5};
    insertion_sort(arr, 5);
    for (auto el: arr)
        cout << el << endl;
    cout << sizeof(double);
}