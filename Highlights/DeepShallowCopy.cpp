/**
 * \brief Shallow & Deep Copy.
 * Got this task from ChatGPT. The code demonstrates shallow & deep copy methods while constructing objects.
*/

#include <iostream>
#include <cstring>
using namespace std;

class Point
{
public:
    Point(int x, int y) : m_x(x), m_y(y)
    {
        cout << "Point: Parameterized Constructor called.\t" << this << "\tx: " << x << "\ty: " << y << endl;
    }

    ~Point()
    {
        cout << "Point: Destructor called.\t" << this << "\tx: " << m_x << "\ty: " << m_y << endl;
    }

    int getPointX() { return m_x; }
    int getPointY() { return m_y; }

    void setPoint(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

private:
    int m_x;
    int m_y;
};

class Line
{
public:
    Line(Point *ptA, Point *ptB)
    {
        cout << "Line: Parameterized Constructor called. " << this << endl;
        // Shallow copy, both objects share the same address & data.
        m_start = ptA;
        m_end = ptB;
    }

    Line(Line &obj)
    {
        // Deep copy. These objects now have different addresses.
        cout << "Line: Copy Constructor called.\t" << this << endl;
        m_start = new Point(obj.m_start->getPointX(), obj.m_start->getPointY());
        m_end = new Point(obj.m_end->getPointX(), obj.m_end->getPointY());
    }

    ~Line() { cout << "Line: Destroyed \t" << this << endl; }

    void displayCoordinates() const
    {
        cout << "Line: Coordinate start(" << m_start << ")(" << m_start->getPointX() << ", " << m_start->getPointY() << ")\t";
        cout << "end(" << m_end << ")(" << m_end->getPointX() << ", " << m_end->getPointY() << ")\n";
    }

private:
    // To demonstrate the internal working effectively, pointers were used as opposed to references or value objects.
    Point *m_start, *m_end;
};

int main()
{
    // Initialisation of Points.
    Point start(1, 1);
    Point end(100, 100);

    // Parameterized Constructor called. obj1 built with Shallow copy.
    Line obj1(&start, &end);

    // Copy Constructor called. obj2 built with Deep Copy.
    Line obj2(obj1);

    // At this point, both obj1 & obj2's coordinate have same data.
    cout << "\n";
    obj1.displayCoordinates();
    obj2.displayCoordinates();
    cout << "\n";

    // As obj1 is built with shallow copy, changing the start coordinate changes obj1's m_start as well,
    // but since obj2 is built with deep copy, obj2's m_start does not change.
    start.setPoint(200, 200);

    // At this point, obj1 will have different start point & obj2's coordinate will be the same.
    cout << "\n";
    obj1.displayCoordinates();
    obj2.displayCoordinates();
    cout << "\n";

    return 0;
}