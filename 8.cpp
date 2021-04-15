#include "std_lib_facilities.h"
#include "Chrono.h"

using namespace Chrono;

enum class Genre
{
    fiction,
    prose,
    periodicals,
    biography,
    childrens_literature
};

class Patron
{
private:
    string user_name;
    int library_card_number;
    double membership_fee;
    const double membership_fee_sum = 100;
public:
    Patron(string user, int lib_card_number, double memb_fee);
    string get_user_name() { return user_name; }
    int get_library_card_number() { return library_card_number; }
    double get_membership_fee() { return membership_fee; }
    void set_membership_fee(double d) { membership_fee = d; }
    bool is_fee_paid() { return (membership_fee>=membership_fee_sum)?true:false; }
};

Patron::Patron(string user, int lib_card_number, double memb_fee)
        : user_name{user}, library_card_number{lib_card_number}, membership_fee{memb_fee}
{
}

class Book
{
private:
    string isbn;
    string book_name;
    string author_name;
    Genre book_genre;
    Date reg_date;
    bool handed_out = false;
    void isbn_check();

public:
    Book(string number, string book, string author, Genre genre, Date registration);
    string get_isbn() const { return isbn; }
    string get_book_name() const { return book_name; }
    string get_author_name() const { return author_name; }
    Genre get_genre() const { return book_genre; }
    Date get_reg_date() const { return reg_date; }
    bool is_handed_out() const { return handed_out; }
    string state_of_book() { return handed_out ? "The book was handed out." : "The book wasn't handed out."; }
};

Book::Book(string number, string book, string author, Genre genre, Date registration)
    : isbn{number}, book_name{book}, author_name{author}, book_genre{genre}, reg_date{registration}
{
    isbn_check();
}

void Book::isbn_check()
{
    int pos1 = 0, pos2 = 0;
    const int sectors = 4;
    for (int sec = 0; sec < sectors; sec++)
    {
        if (sec < sectors - 1) //first three sectors
        {
            pos2 = isbn.find("-", pos1);
            if (pos2 < 0)
                error("ISBN must contain three hyphens");
        }
        else //fourth sector
        {
            pos2 = pos1 + 1;
            if (pos2 != isbn.size())
                error("Wrong ISBN (sector 4 must contain one symbol - an integer or a letter)");
        }
        for (int i = pos1; i < pos2; i++)
        {
            if (isbn[i] < '0' || isbn[i] > '9')
            {
                if (sec < sectors - 1) //for first three sectors
                    error("Wrong ISBN (sector 1-3 must contain only integers)");
                else if ((isbn[i] < 'A' || isbn[i] > 'Z') && (isbn[i] < 'a' || isbn[i] > 'z')) //for fourth sector
                    error("Wrong ISBN (sector 4 must contain an integer or a letter)");
            }
        }
        pos1 = pos2 + 1;
    }
}

bool operator==(const Book &b1, const Book &b2)
{
    return b1.get_isbn() == b2.get_isbn();
}

bool operator!=(const Book &b1, const Book &b2)
{
    return !(b1 == b2);
}

ostream &operator<<(ostream &os, const Book b)
{
    return os << b.get_book_name() << endl
              << b.get_author_name() << endl
              << b.get_isbn() << endl;
}

int main()
{
    //Book book1{"978-5-6040724-G", "Programming", "Bjarne Stroustrup", Genre::periodicals, Date(2019, Month::apr, 11)};
    //cout << book1;
    //cout << (int)book1.get_genre() << endl;
    //cout << book1.get_reg_date() << endl;
    //cout << book1.state_of_book() << endl;
    Patron user1 {"Patrick",123,0};
    cout << user1.get_user_name() << endl;
    cout << user1.get_library_card_number() << endl;
    cout << user1.get_membership_fee() << endl;
    cout << user1.is_fee_paid() << endl;
    user1.set_membership_fee(100);
    cout << user1.is_fee_paid() << endl;
}