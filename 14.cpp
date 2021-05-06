#include "std_lib_facilities.h"

class Money
{
public:
    Money();
    Money(string cur, double d);
    string get_currency() const { return currency; }
    double get_money() const { return money; }
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
    if (temp >= 995 && temp <= 999)
    {
        banknote++;
        money++;
        return 0;
    }
    return (temp % 10 >= 5) ? temp / 10 + 1 : temp / 10;
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

Money operator+(const Money &m1, const Money &m2)
{
    if (m1.get_currency() != m2.get_currency())
        error("Different currencies");
    return Money(m1.get_currency(), m1.get_money() + m2.get_money());
}

Money operator-(const Money &m1, const Money &m2)
{
    if (m1.get_currency() != m2.get_currency())
        error("Different currencies");
    return Money(m1.get_currency(), m1.get_money() - m2.get_money());
}

Money operator*(const Money &m1, int n)
{
    return Money(m1.get_currency(), m1.get_money() * n);
}

Money operator/(const Money &m1, int n)
{
    double tre = m1.get_money() / n;
    return Money(m1.get_currency(), m1.get_money() / n);
}

int main()
{
    Money m1{"UAH", 1.99};
    Money m2{"UAH", 1.01};
    cout << m1 / 2 << endl;
    cout << m2 / 2 << endl;

}