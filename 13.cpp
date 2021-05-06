#include "std_lib_facilities.h"

class Rational
{
public:
    Rational(int n, int d);
    Rational();

    //non-modifying functions
    int get_numerator() const { return numerator; }
    int get_denominator() const { return denominator; }
    double rational_to_double() const;

    //modifying functions
    void reduce_rational();

private:
    int numerator;
    int denominator;
    //non-modifying function
    const int div_by_zero(const int &n);
    //modifying function
    void minus_check();
};

Rational::Rational(int n, int d)
    : numerator{n}, denominator{div_by_zero(d)}
{
    minus_check();
}

const Rational &default_rational()
{
    static Rational r{0, 1};
    return r;
}

Rational::Rational()
    : numerator{default_rational().numerator},
      denominator{default_rational().denominator}
{
}

const int Rational::div_by_zero(const int &n)
{
    if (n == 0)
        error("Division by zero!");
    return n;
}

ostream &operator<<(ostream &os, const Rational &r)
{
    return os << "(" << r.get_numerator()
              << "/" << r.get_denominator() << ")";
}

istream &operator>>(istream &is, Rational &r)
{
    int n, d;
    char ch1, ch2, ch3;
    is >> ch1 >> n >> ch2 >> d >> ch3;
    if (!is)
        return is;
    if (ch1 != '(' || ch2 != '/' || ch3 != ')') //a format error
    {
        is.clear(ios_base::failbit); //set an error bit
        return is;
    }
    r = Rational(n, d); //update r
    return is;
}

double Rational::rational_to_double() const
{
    return (double)numerator / denominator;
}

Rational operator+(const Rational &a, const Rational &b)
{
    int num, den;
    num = a.get_numerator() * b.get_denominator() + a.get_denominator() * b.get_numerator();
    den = a.get_denominator() * b.get_denominator();
    Rational res{num, den};
    return res;
}

Rational operator-(const Rational &a, const Rational &b)
{
    int num, den;
    num = a.get_numerator() * b.get_denominator() - a.get_denominator() * b.get_numerator();
    den = a.get_denominator() * b.get_denominator();
    Rational res{num, den};
    return res;
}

Rational operator*(const Rational &a, const Rational &b)
{
    int num, den;
    num = a.get_numerator() * b.get_numerator();
    den = a.get_denominator() * b.get_denominator();
    Rational res{num, den};
    return res;
}

Rational operator/(const Rational &a, const Rational &b)
{
    int num, den;
    num = a.get_numerator() * b.get_denominator();
    den = a.get_denominator() * b.get_numerator();
    Rational res{num, den};
    return res;
}

bool operator==(const Rational &a, const Rational &b)
{
    return a.get_numerator() == b.get_numerator() && a.get_denominator() == b.get_denominator();
}

bool operator!=(const Rational &a, const Rational &b)
{
    return !(a == b);
}

void Rational::minus_check()
{
    if (denominator < 0)
    {
        if (numerator >= 0)
            numerator = -numerator;
        denominator = -denominator;
    }
}

void Rational::reduce_rational()
{
    int a = numerator, b = denominator;
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    if (abs(a) > 1)
    {
        numerator /= a;
        denominator /= a;
    }
    minus_check();
}

int main()
{
    Rational a{-10, 22};
    Rational b;
    Rational c{-17, -100};
    Rational d{48, 6};
    cin >> b;
    b.reduce_rational();
    cout << b << endl;
    cout << b.rational_to_double() << endl;
}