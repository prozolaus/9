#include "Chrono.h"

namespace Chrono
{
    Date::Date(int yy, Month mm, int dd)
        : y{yy}, m{mm}, d{dd}
    {
        if (!is_date(yy, mm, dd))
            throw Invalid{};
    }

    const Date &default_date()
    {
        static Date dd{2001, Month::jan, 1}; //The beginning of the XXI century
        return dd;
    }

    Date::Date()
        : y{default_date().year()},
          m{default_date().month()},
          d{default_date().day()}
    {
    }

    void Date::add_day(int n)
    {
        //.........
    }

    void Date::add_month(int n)
    {
        //.........
    }

    void Date::add_year(int n)
    {
        if (m == Month::feb && d == 29 && !leapyear(y + n)) // in a common year, February 29 turns into March 1
        {
            m = Month::mar;
            d = 1;
        }
        y += n;
    }

    // secondary functions:
    bool is_date(int y, Month m, int d)
    {
        if (d <= 0)
            return false; // d must be positive
        if (m < Month::jan || m > Month::dec)
            return false;

        int days_in_month = 31; //no more than 31 days in a month
        switch (m)
        {
        case Month::feb:
            days_in_month = (leapyear(y)) ? 29 : 28;
            break;
        case Month::apr:
        case Month::jun:
        case Month::sep:
        case Month::nov:
            days_in_month = 30;
            break;
        }
        if (d > days_in_month)
            return false;
        return true;
    }
    
    // a leap year is disivible by 4, but not by 100, except if it is divisible by 400
    bool leapyear(int y)
    {
        if (y < 0) error("leapyear(): The year cannot be negative.");
        return y%4==0 && y%100!=0 || y%400==0;
    }

    bool operator==(const Date &a, const Date &b)
    {
        return a.year() == b.year() && a.month() == b.month() && a.day() == b.day();
    }

    bool operator!=(const Date &a, const Date &b)
    {
        return !(a == b);
    }

    ostream &operator<<(ostream &os, const Date &d)
    {
        return os << '(' << d.year()
                  << ',' << int(d.month())
                  << ',' << d.day() << ')';
    }

    istream &operator>>(istream &is, Date &dd)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if (!is)
            return is;
        if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') //a format error
        {
            is.clear(ios_base::failbit); // set an error bit
            return is;
        }
        dd = Date(y, Month(m), d); //update dd
        return is;
    }

    enum class Day
    {
        sunday,
        monday,
        tuesday,
        wednesday,
        thursday,
        friday,
        saturday
    };

    Day day_of_week(const Date& d)
    {
        //...
        return Day::friday;
    }

    Date next_Sunday(const Date& d)
    {
        //...
        return d;
    }
 
    Date next_weekday(const Date& d)
    {
        //...
        return d;
    }
}