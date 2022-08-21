#include "std_lib_facilities.h"

class Year
{
    static constexpr int min = 1800;
    static constexpr int max = 2200;

public:
    class Invalid
    {
    };
    Year(int x) : y{x}
    {
        if (x < min || x > max)
            throw Invalid{};
    }
    int year()
    {
        return y;
    }

private:
    int y;
};

enum class Month
{
    jan = 1,
    feb,
    mar,
    apr,
    may,
    jun,
    jul,
    aug,
    sep,
    oct,
    nov,
    dec
};

class Date
{
public:
    Date(Year y, Month m, int d);

private:
    Year y;
    Month m;
    int d;
};

/*Month int_to_month(int x)
{
    if (x < int(Month::jan) || x > int(Month::dec))
        error("wrong input!");
    return Month(x);
    
}*/

Month operator++(Month &m)
{
    m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
    return m;
}

int main()
{
    Date(Year{1988},Month::mar,7);
}
