#include "std_lib_facilities.h"
#include "Chrono.h"

using namespace Chrono;

class Book
{
private:
    string isbn;
    string book_name;
    string author_name;
    Date reg_date;
    bool handed_out = false;
    void isbn_check();

public:
    Book(string number, string book, string author, Date registration);
    string get_isbn() { return isbn; }
    string get_book_name() { return book_name; }
    string get_author_name() { return author_name; }
    Date get_reg_date() { return reg_date; }
    bool is_handed_out() { return handed_out; }
    string state_of_book() { return handed_out ? "The book was handed out." : "The book wasn't handed out."; }
};

Book::Book(string number, string book, string author, Date registration)
    : isbn{number}, book_name{book}, author_name{author}, reg_date{registration}
{
    isbn_check();
}

void Book::isbn_check()
{
    int pos1 = 0, pos2 = 0;
    const int sectors = 4;
    for (int sec = 0; sec < sectors; sec++)
    {
        if (sec < sectors - 1)  //first three sectors
        {
            pos2 = isbn.find("-", pos1);
            if (pos2 < 0)
                error("ISBN must contain three hyphens");
        }
        else    //fourth sector
        {
            pos2 = pos1 + 1;
            if (pos2 != isbn.size())
                error("Wrong ISBN (sector 4 must contain one symbol - an integer or a letter)");
        }
        for (int i = pos1; i < pos2; i++)
        {
            if (isbn[i] < '0' || isbn[i] > '9')
            {
                if (sec < sectors - 1)  //for first three sectors
                    error("Wrong ISBN (sector 1-3 must contain only integers)");
                else if ((isbn[i] < 'A' || isbn[i] > 'Z') && (isbn[i] < 'a' || isbn[i] > 'z')) //for fourth sector
                    error("Wrong ISBN (sector 4 must contain an integer or a letter)");
            }
        }
        pos1 = pos2 + 1;
    }
}

int main()
{
    Book book1{"978-5-6040724-G", "Programming", "Bjarne Stroustrup", Date(2019, Month::apr, 11)};
    cout << book1.get_isbn() << endl;
    cout << book1.get_book_name() << endl;
    cout << book1.get_author_name() << endl;
    cout << book1.get_reg_date() << endl;
    cout << book1.state_of_book() << endl;
}