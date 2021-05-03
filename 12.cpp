#include "Libra.h" //classes Book, Patron and Library

using namespace Libra;

int main()
{
    try
    {
        Book book1{"978-5-6040724-G", "Programming", "Bjarne Stroustrup", Book::Genre::periodicals, Date(2019, Month::apr, 11)};
        Patron user1{"Patrick", 1001, 100};
        Library lib;
        lib.add_book(book1);
        lib.add_patron(user1);
        lib.give_book_to_patron(book1,user1);
        lib.show_book_status(book1);
        vector<string> debtor_names = lib.get_debtor_names();
        for (int i = 0; i < debtor_names.size(); i++)
            cout << debtor_names[i] << endl;

        //Date date(2021, Month::may, 3);
        //cout << day_of_week(date) << endl;
        //cout << date.next_workday() << endl;
        //cout << next_Sunday(date) << endl;
        //cout << next_weekday(date) << endl;
    }
    catch (Date::Invalid &)
    {
        cerr << "error: Invalid date\n";
        return 1;
    }
    catch (exception &e)
    {
        cerr << "Exception: " << e.what() << endl;
    }
    catch (...)
    {
        cerr << "Exception\n";
    }
}