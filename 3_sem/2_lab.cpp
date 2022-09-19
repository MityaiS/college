#include <iostream>
#include <cmath>
using namespace std;

struct Point
{
    double x, y;
};

class Figure
{

protected:
    Point A, B, C;
    double AB, BC, CA;

public:
    Figure(Point p1, Point p2, Point p3)
    {
        A = p1;
        B = p2;
        C = p3;
        AB = pow(pow(B.x - A.x, 2) + pow(B.y - A.y, 2), 0.5);
        BC = pow(pow(C.x - B.x, 2) + pow(C.y - B.y, 2), 0.5);
        CA = pow(pow(A.x - C.x, 2) + pow(A.y - C.y, 2), 0.5);
        if (get_area() == 0)
            throw "Figure is not valid";
    }

    virtual double get_perimeter()
    {
        return AB + BC + CA;
    }

    virtual double get_area()
    {
        return abs((1 / 2.0) * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)));
    }

    Point get_centroid()
    {
        return {(1 / 3.0) * (A.x + B.x + C.x), (1 / 3.0) * (A.y + B.y + C.y)};
    }
};

class Rectangle : public Figure
{
    Point D;
    double CD, DA, BD;

public:
    Rectangle(Point p1, Point p2, Point p3, Point p4) : Figure(p1, p2, p3)
    {
        D = p4;
        CD = pow(pow(D.x - C.x, 2) + pow(D.y - C.y, 2), 0.5);
        DA = pow(pow(A.x - D.x, 2) + pow(A.y - D.y, 2), 0.5);
        BD = pow(pow(D.x - B.x, 2) + pow(D.y - B.y, 2), 0.5);
        if (BD != CA or AB > CA or BC > CA)
            throw "Rectangle is not valid";
    }

    double get_perimeter() override
    {
        return AB + BC + CD + DA;
    }

    double get_area() override
    {
        return AB * BC;
    }

    Point get_centre()
    {
        return {(1 / 4.0) * (A.x + B.x + C.x + D.x), (1 / 4.0) * (A.y + B.y + C.y + D.y)};
    }
};

int main()
{
    Point points[4];
    cout << "Type in 3 points of a triangle" << endl;
    for (int i = 0; i < 6; i++)
    {
        if (i % 2 == 0)
        {
            cout << "Type x coordinate of a point: ";
            cin >> points[i / 2].x;
        }
        else
        {
            cout << "Type y coordinate of a point: ";
            cin >> points[i / 2].y;
        }
        while (!cin.good())
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max()), '\n');
            cout << "Type the correct coordinate: ";
            if (i % 2 == 0)
                cin >> points[i / 2].x;
            else
                cin >> points[i / 2].y;
        }
    }
    cout << endl;
    try
    {
        Figure f1(points[0], points[1], points[2]);
        cout << "The centroid of a figure in (" << f1.get_centroid().x << ", "
             << f1.get_centroid().y << ")" << endl;
        cout << "The area of a figure is " << f1.get_area() << endl;
        cout << "The perimeter of a figure is " << f1.get_perimeter() << endl;
    }
    catch (const char *txtException)
    {
        cout << "Exception: " << txtException << endl;
    }

    cout << "-------------------------------------" << endl;

    cout << "Type in 4 points of a rectangle" << endl;
    for (int i = 0; i < 8; i++)
    {
        if (i % 2 == 0)
        {
            cout << "Type x coordinate of a point: ";
            cin >> points[i / 2].x;
        }
        else
        {
            cout << "Type y coordinate of a point: ";
            cin >> points[i / 2].y;
        }
        while (!cin.good())
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max()), '\n');
            cout << "Type the correct coordinate: ";
            if (i % 2 == 0)
                cin >> points[i / 2].x;
            else
                cin >> points[i / 2].y;
        }
    }
    cout << endl;

    try
    {
        Rectangle r1(points[0], points[1], points[2], points[3]);
        cout << "The centre of a rectangle in (" << r1.get_centre().x << ", "
             << r1.get_centre().y << ")" << endl;
        cout << "The area of a rectangle is " << r1.get_area() << endl;
        cout << "The perimeter of a rectangle is " << r1.get_perimeter() << endl;
    }
    catch (const char *txtException)
    {
        cout << "Exception: " << txtException << endl;
    }
}