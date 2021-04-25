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

        //modifying operations
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);
        Day next_workday(const Day &d);
        int week_of_year();

    private:
        int y;
        Month m;
        int d;
        vector<int> days_in_month;
        vector<int> get_days_in_month();
    };

    bool is_date(int y, Month m, int d); //true for correct date
    bool leapyear(int y);                //true for leap year
    bool operator==(const Date &a, const Date &b);
    bool operator!=(const Date &a, const Date &b);
    ostream &operator<<(ostream &os, const Date &d);
    istream &operator>>(istream &is, Date &dd);
}