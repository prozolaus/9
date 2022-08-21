#include "Chrono.h"

struct Date
{
    int y;
    int m;
    int d;
};

void add_day(Date &dd, int n)
{
    dd.d += n;
}

ostream &operator<<(ostream &os, const Date &d)
{
    return os << '(' << d.y
              << ',' << d.m
              << ',' << d.d << ')';
}

int main()
{
    Date today;
    today.y = 1963;
    today.m = 5;
    today.d = 19;

    Date tomorrow = today;
    add_day(tomorrow, 1);

    cout << "today is " << today << endl;
    cout << "tomorrow is " << tomorrow << endl;
}
