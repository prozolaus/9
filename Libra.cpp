#include "Libra.h"

namespace Libra
{
    Patron::Patron(string user, int lib_card_number, double memb_fee)
        : user_name{user}, library_card_number{lib_card_number}, membership_fee{memb_fee}
    {
    }

    bool operator==(const Patron &a, const Patron &b)
    {
        return a.get_library_card_number() == b.get_library_card_number();
    }

    Book::Book(string number, string book, string author, Genre genre, Chrono::Date registration)
        : isbn{number}, book_name{book}, author_name{author}, book_genre{genre}, reg_date{registration}
    {
        isbn_check();
    }

    void Book::return_book()
    {
        if (!handed_out)
            error("book_return(): the book has been already returned!");
        handed_out = false;
    }

    void Book::give_out_book()
    {
        if (handed_out)
            error("give_out_book(): the book has been already given out!");
        handed_out = true;
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
                if (isbn[i] < '0' || isbn[i] > '9')  //isdigit()
                {
                    if (sec < sectors - 1) //for first three sectors
                        error("Wrong ISBN (sector 1-3 must contain only integers)");
                    else if ((isbn[i] < 'A' || isbn[i] > 'Z') && (isbn[i] < 'a' || isbn[i] > 'z')) //for fourth sector //isalpha()
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
}
