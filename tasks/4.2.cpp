#include "Chrono.h"

struct Date
{
    int y, m, d;
    Date(int y, int m, int d);
};

Date::Date(int yy, int mm, int dd)
       : y{yy}, m{mm}, d{dd}
{
}

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
    Date today{1963,5,19};

    Date tomorrow = today;
    add_day(tomorrow, 1);

    cout << "today is " << today << endl;
    cout << "tomorrow is " << tomorrow << endl;
}
