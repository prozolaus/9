#include "Libra.h" //classes Book and Patron

using namespace Libra;

class Library
{
public:
    //modifying functions
    void add_book(const Book &b);
    void add_patron(const Patron &p);
    void show_book_status(const Book &b);
    void give_book_to_patron(Book &b, const Patron &p);
    vector<string> get_debtor_names();

private:
    struct Transaction
    {
        Book book;
        Patron patron;
        Date date;
    };
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;
};

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

    Transaction tr{b, p, Date()};   //create a transaction with default date
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

int main()
{
    Book book1{"978-5-6040724-G", "Programming", "Bjarne Stroustrup", Book::Genre::periodicals, Date(2019, Month::apr, 11)};
    Patron user1{"Patrick", 1001, 100};
    Library lib;
    lib.add_book(book1);
    lib.add_patron(user1);
    //lib.give_book_to_patron(book1,user1);
    //lib.show_book_status(book1);

    vector<string> debtor_names = lib.get_debtor_names();
    for (int i = 0; i < debtor_names.size(); i++)
        cout << debtor_names[i] << endl;
}