#include "Chrono.h"

using Chrono::Month;

class Date
{
    int y;
    Month m;
    int d;

public:
    Date(int y, Month m, int d);
    void add_day(int n) { d += n; }
    int year() { return y; }
    Month month() { return m; }
    int day() { return d; }
};

Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
}

ostream &operator<<(ostream &os, Date &d)
{
    return os << '(' << d.year()
              << ',' << (int)d.month()
              << ',' << d.day() << ')';
}

int main()
{
    Date today{1963, Month::may, 19};

    Date tomorrow = today;
    tomorrow.add_day(1);

    cout << "today is " << today << endl;
    cout << "tomorrow is " << tomorrow << endl;
}
