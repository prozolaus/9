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
        static Date dd{1970, Month::jan, 1}; //The day zero - thursday
        return dd;
    }

    Date::Date()
        : y{default_date().year()},
          m{default_date().month()},
          d{default_date().day()}
    {
    }

    const Date zero = default_date(); //The day zero - thursday
    int day_zero = (int)Day::thursday; // 01.01.1970 was a thursday

    void Date::add_day(int n)
    {
        vector<int> v = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //from january to december
        int days = n, i = int(m) - 1, dd = d;                             //we use dd as a copy of d because d can be changed with add_month()
        int sum = days + d;

        if (sum <= v[i]) // if we add days within one month
        {
            d = sum;
            return;
        }

        // when we transfer days to next months
        while (days >= v[1])
        {
            v[1] = (leapyear(y)) ? 29 : 28;
            days -= v[i++];
            add_month(1);
            i = (i == 12) ? 0 : i; // when we transfer days to the next year
        }

        dd += days;

        if (dd > v[i])
        {
            add_month(1);
            dd %= v[i]; //transfer extra days to next month
        }

        d = dd;
    }

    void Date::add_month(int n)
    {
        int mnth = n % 12;
        int yrs = n / 12;
        int t = mnth + (int)m;
        if (t > 12)
            yrs++;
        if (yrs > 0)
            add_year(yrs);
        m = (t > 12) ? Month(t % 12) : Month(t);

        if (m == Month::feb && d > 28)
            d = (leapyear(y)) ? 29 : 28;
        else if ((m == Month::apr || m == Month::jun || m == Month::sep || m == Month::nov) && d == 31)
            d = 30;
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
        //if (y < zero.year())
            //return false;
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
        if (y < 0)
            error("leapyear(): The year cannot be negative.");
        return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
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

    ostream &operator<<(ostream &os, Day d)
    {
        switch (d)
        {
        case Day::sunday:
            os << "Sunday";
            break;
        case Day::monday:
            os << "Monday";
            break;
        case Day::tuesday:
            os << "Tuesday";
            break;
        case Day::wednesday:
            os << "Wednesday";
            break;
        case Day::thursday:
            os << "Thursday";
            break;
        case Day::friday:
            os << "Friday";
            break;
        case Day::saturday:
            os << "Saturday";
            break;
        }
        return os;
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

    Day Date::next_workday()
    {
        long int d = days_since_day_zero();
        int day = d % 7; // day regarding thursday
        if (day == 1 || day == 2)
            day = 3;
        return Day((day_zero + day + 1) % 7);
    }

    int Date::days_in_current_year() const
    {
        vector<int> v = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30}; //from january to november
        if (leapyear(y))
            v[1] = 29;
        int sum = d; //sum - number of days since January 1
        for (int i = 0, n = (int)m - 1; i < n; i++)
            sum += v[i];
        return sum - 1;
    }

    int Date::week_of_year() const
    {
        int sum = days_in_current_year(), rem = sum % 7;
        return (rem > 0) ? (sum / 7 + 1) : (sum / 7);
    }

    int number_of_leapyears(int y1, int y2)
    {
        int sum = 0;
        while (y1 < y2)
        {
            if (leapyear(y1))
            {
                sum++;
                y1 += 4;
            }
            else
                y1++;
        }
        return sum;
    }

    long int Date::days_since_day_zero() const
    {
        /*
        while (zero.y < y)
        {
            if (leapyear(zero.y))
                sum++;
            zero.add_year(1);
        }
        sum += days_in_current_year();
        */
        if (y - zero.y < 0)
            error("days_since_day_zero(): negative year!");
        return (y - zero.y) * 365 + number_of_leapyears(zero.y, y) + days_in_current_year();
    }

    Day day_of_week(const Date &dd)
    {
        long int day = dd.days_since_day_zero();
        return Day((day + day_zero) % 7); // day regarding thursday
    }

    Date next_Sunday(const Date &dd)
    {
        Day dow = day_of_week(dd);
        Date ns_date = dd;
        ns_date.add_day(7 - (int)dow);
        return ns_date;
    }

    Date next_weekday(const Date &dd)
    {
        Date nw_date = dd;
        Day dnw = day_of_week(dd);
        int x = (dnw < Day::saturday) ? 6 : 1;
        nw_date.add_day(x - int(dnw));
        return nw_date;
    }
}