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

    
    vector<string> Library::get_debtor_names()
    {
        vector<string> v;
        for (int i = 0; i < patrons.size(); i++)
            if (!patrons[i].is_fee_paid())
                v.push_back(patrons[i].get_user_name());
        return v;
    }

    void Library::give_book_to_patron(Book &b, const Patron &p)
    {
        bool is_book_exist = false;
        bool is_patron_exist = false;

        for (int i = 0; i < books.size(); i++)
            if (b == books[i])
                is_book_exist = true;
        if (!is_book_exist)
            error("give_book_to_patron(): such book doesn't exist!");

        for (int i = 0; i < patrons.size(); i++)
            if (p == patrons[i])
                is_patron_exist = true;
        if (!is_patron_exist)
            error("give_book_to_patron(): such patron doesn't exist!");

        if (!p.is_fee_paid())
            error("give_book_to_patron(): the patron has a debt");

        if (b.is_handed_out())
            error("give_book_to_patron(): the book has already been handed out");

        Transaction tr{b, p, Date()}; //create a transaction with default date
        transactions.push_back(tr);

        b.give_out_book();
    }

    void Library::show_book_status(const Book &b)
    {
        for (int i = 0; i < books.size(); i++)
            if (b == books[i])
            {
                cout << b.state_of_book() << endl;
                return;
            }
        error("show_book_status(): there is no such book in the library!");
    }

    void Library::add_book(const Book &b)
    {
        for (int i = 0; i < books.size(); i++)
            if (b == books[i])
                error("add_book(): this book is already exist in the library");
        books.push_back(b);
    }

    void Library::add_patron(const Patron &p)
    {
        for (int i = 0; i < patrons.size(); i++)
            if (p == patrons[i])
                error("add_patron(): a patron with such a card number is already exist in the library base");
        patrons.push_back(p);
    }
}
