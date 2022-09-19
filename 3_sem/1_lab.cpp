#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void in_data(vector<int>& arr, vector<vector<int>>& mat, int& n_r)
{
    srand(time(0));
    cout << "Type in n" << endl;
    cin >> n_r;
    while(!cin.good() or n_r < 1 or n_r > 1000)
    {
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max()), '\n');
        cout << "Type the correct n" << endl;
        cin >> n_r;
    }
    cout << "Do you want to type the elements or not(Y/n)" << endl;
    char ans;
    cin >> ans; 
    ans = tolower(ans);
    while (ans != 'y' and ans != 'n')
    {
        cout << "Type the correct answere(Y/n)" << endl;
        cin >> ans;
        ans = tolower(ans);
    }
    if (ans == 'y')
        cout << "Type the elements of the array" << endl;
    for (int i = 0; i < n_r; i++)
    {
        if (ans == 'y')
        {
            int tmp;
            cin >> tmp;
            while(!cin.good() or tmp > 1000 or tmp < -1000)
            {
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max()), '\n');
                cout << "Type the correct element" << endl;
                cin >> tmp; 
            }
            arr.push_back(tmp);
        }
        else
            arr.push_back(-999 + rand() % 2000);
    }
    if (ans == 'y')
        cout << "Type the elems of the matrix" << endl;
    for (int i = 0; i < n_r; i++)
    {
        vector<int> tmp_v;
        for (int j = 0; j < n_r; j++)
        {
            if (ans == 'y')
            {
                int tmp;
                cin >> tmp;
                while(!cin.good() or tmp > 1000 or tmp < -1000)
                {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max()), '\n');
                    cout << "Type the correct element" << endl;
                    cin >> tmp; 
                }
                tmp_v.push_back(tmp);
            }
            else
                tmp_v.push_back(-999 + rand() % 2000);
        }
        mat.push_back(tmp_v);
    }
}

void solve(vector<int> arr, vector<vector<int>>& mat, int n)
{
    if (*(min_element(arr.begin(), arr.end())) == arr[n - 1])
    {
        for (auto &row: mat)
            for (auto &elem: row)
                elem += arr[n - 1];
    }
    else
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (j == i)
                    mat[i][j] += arr[n - 1];
    }
}

void out_data(vector<vector<int>> mat, vector<int> arr)
{
    cout << "Here's the array" << endl;
    for (auto elem: arr)
        cout << elem << " ";
    cout << endl;
    cout << "Here's the matrix" << endl;
    for (auto row: mat)
        {
            for (auto elem: row)
                cout << elem << " ";
            cout << endl;
        }
}

int main()
{
    vector<int> arr;
    vector<vector<int>> mat;
    int n;
    in_data(arr, mat, n);
    solve(arr, mat, n);
    out_data(mat, arr);
    return 0;
}