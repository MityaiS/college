#include <iostream>
#include <limits>
using namespace std;

class Integer
{
    long int value;

public:
    Integer() : value(0)
    {
    }

    Integer(int x) : value(x)
    {
    }

    Integer operator++()
    {
        ++value;
        return *this;
    }

    Integer operator++(int)
    {
        value++;
        return *this;
    }

    void Print_integer()
    {
        cout << value << endl;
    }

    friend Integer operator--(Integer &inst);
    friend Integer operator--(Integer &inst, int);
};

Integer operator--(Integer &inst)
{
    inst.value--;
    return inst;
}

Integer operator--(Integer &inst, int)
{
    inst.value--;
    return inst;
}

int main()
{
    cout << "Hello! Do you want to type the initial state of an integer or not(Y/n)" << endl;
    char ans;
    cin >> ans;
    ans = tolower(ans);
    while (ans != 'y' and ans != 'n')
    {
        cout << "Type the correct answere(Y/n)" << endl;
        cin >> ans;
        ans = tolower(ans);
    }
    long int n;
    if (ans == 'y')
    {
        cout << "Okay, then. Type the initial state of an integer(-1000 <= n <= 1000): ";
        cin >> n;
        while (!cin.good() or n > 1000 or n < -1000)
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max()), '\n');
            cout << endl
                 << "Type the correct n: ";
            cin >> n;
        }
        cout << endl;
    }
    else
        n = 0;

    Integer a(n);

    while (ans != 'e')
    {
        cout << "What do you want to do? To increment integer type 'i'. To decrement type 'd'." << endl
             << "To show the integer type 's'. To exit type 'e': ";
        cin >> ans;
        switch (ans)
        {
        case 'i':
            a++;
            break;
        case 'd':
            a--;
            break;
        case 's':
            a.Print_integer();
            break;
        case 'e':
            break;
        default:
            while (ans != 'i' and ans != 'd' and ans != 's' and ans != 'e')
            {
                cout << "Type the correct answere: ";
                cin >> ans;
            }
            break;
        }
    }
}