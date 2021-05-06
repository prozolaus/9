#include "std_lib_facilities.h"

struct money_struct
{
    string currency;
    long banknote;
    int coin;
};

class Money
{
public:
    Money(string cur, long b, int coin);
    money_struct get_money() { return m_struct; }

private:
    long money;
    money_struct m_struct;
};

Money::Money(string cur, long b, int coin)
    : m_struct{cur, b, coin}
{
}

int main()
{
    Money m{"$",123,45};
    money_struct mn = m.get_money();
    cout << mn.currency << mn.banknote << "." << mn.coin << endl;
}