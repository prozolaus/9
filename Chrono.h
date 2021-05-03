#include "std_lib_facilities.h"

namespace Chrono
{
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
        class Invalid
        {
        }; //for generation of exceptions

        Date(int y, Month m, int d);

        Date(); //default constructor

        //non-modifying operations
        int day() const { return d; }
        Month month() const { return m; }
        int year() const { return y; }
        int days_in_current_year() const;
        long int days_since_day_zero() const;
        int week_of_year() const;
        Day next_workday();

        //modifying operations
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);

    private:
        int y;
        Month m;
        int d;
    };

    bool is_date(int y, Month m, int d); //true for correct date
    bool leapyear(int y);                //true for leap year
    bool operator==(const Date &a, const Date &b);
    bool operator!=(const Date &a, const Date &b);
    ostream &operator<<(ostream &os, const Date &d);
    ostream &operator<<(ostream &os, Day d);
    istream &operator>>(istream &is, Date &dd);
    Day day_of_week(const Date &dd);
    Date next_Sunday(const Date &dd);
    Date next_weekday(const Date &dd);
}