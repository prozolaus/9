#include "Chrono.h" //class Date

using namespace Chrono;

namespace Libra
{
    class Patron
    {
    private:
        string user_name;
        int library_card_number;
        double membership_fee;
        const double membership_fee_sum = 100;

    public:
        Patron(string user, int lib_card_number, double memb_fee);
        string get_user_name() const { return user_name; }
        int get_library_card_number() const { return library_card_number; }
        double get_membership_fee() const { return membership_fee; }
        void set_membership_fee(double d) { membership_fee = d; }
        bool is_fee_paid() const { return (membership_fee >= membership_fee_sum) ? true : false; }
    };
    bool operator==(const Patron &a, const Patron &b);

    class Book
    {
    public:
        enum class Genre
        {
            fiction,
            prose,
            periodicals,
            biography,
            childrens_literature
        };
        Book(string number, string book, string author, Genre genre, Date registration);
        string get_isbn() const { return isbn; }
        string get_book_name() const { return book_name; }
        string get_author_name() const { return author_name; }
        Genre get_genre() const { return book_genre; }
        Date get_reg_date() const { return reg_date; }
        bool is_handed_out() const { return handed_out; }
        void give_out_book();
        void return_book();
        string state_of_book() const { return handed_out ? "The book was handed out." : "The book wasn't handed out."; }

    private:
        string isbn;
        string book_name;
        string author_name;
        Genre book_genre;
        Date reg_date;
        bool handed_out = false;
        void isbn_check();
    };
    bool operator==(const Book &b1, const Book &b2);
    bool operator!=(const Book &b1, const Book &b2);
    ostream &operator<<(ostream &os, const Book b);
}
