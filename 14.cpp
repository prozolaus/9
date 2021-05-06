#include "std_lib_facilities.h"

class Money
{
public:
    Money();
    Money(string cur, double d);
    string get_currency() const { return currency; }
    int get_banknote() const { return banknote; }
    int get_coin() const { return coin; }

private:
    string currency;
    double money;
    long banknote;
    int coin;
    int rounding_coins();
};

Money::Money()
{
    currency = "$";
    money = 0;
    banknote = 0;
    coin = 0;
}

int Money::rounding_coins()
{
    int temp = (money - banknote) * 1000;
    return (temp%100 >= 5) ? temp/10 + 1 : temp/10;
}

Money::Money(string cur, double d)
    : currency{cur}, money{d}
{
    banknote = (long)money;
    coin = rounding_coins();
}

istream &operator>>(istream &is, Money &m)
{
    string currency;
    double d;
    char ch1;
    is >> currency >> d;
    if (!is)
        return is;
    m = Money(currency, d);
    return is;
}

ostream &operator<<(ostream &os, const Money &m)
{
    return os << m.get_currency() << " " << m.get_banknote() << "." << m.get_coin();
}

int main()
{
    //Money m{"UAH", 100.91};
    Money m;
    cin >> m;
    cout << m << endl;
}