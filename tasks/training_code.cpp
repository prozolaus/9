#include "std_lib_facilities.h"

class Date
{
public:
    class Invalid {};
    Date(int y, int m, int d);
    void printDate();
    void add_day(int);

private:
    int y, m, d;
    bool is_valid();
};

Date::Date(int yy, int mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    if (!is_valid()) throw Invalid{};
}

bool Date::is_valid()
{
    if (m<1 || 12<m) return false;
    return true;
}

void Date::printDate()
{
    cout << y << " " << m << " " << d << endl;
}

void Date::add_day(int dd)
{
    d+=dd;
}

//-------------------------------------------------------------

void f(int x, int y)
try
{
    Date dxy{2009,x,y};
    dxy.printDate();
    dxy.add_day(2);
    dxy.printDate();
}
catch(Date::Invalid)
{
    error("Wrong date!");
}

//-------------------------------------------------------------

int main()
{
    f(1,21);
}