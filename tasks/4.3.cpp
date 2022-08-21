#include "Chrono.h"

class Date
{
    int y, m, d;

public:
    Date(int y, int m, int d);
    void add_day(int n) { d += n; }
    int year() { return y; }
    int month() { return m; }
    int day() { return d; }
};

Date::Date(int yy, int mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
}

ostream &operator<<(ostream &os, Date &d)
{
    return os << '(' << d.year()
              << ',' << d.month()
              << ',' << d.day() << ')';
}

int main()
{
    Date today{1963, 5, 19};

    Date tomorrow = today;
    tomorrow.add_day(1);

    cout << "today is " << today << endl;
    cout << "tomorrow is " << tomorrow << endl;
}
