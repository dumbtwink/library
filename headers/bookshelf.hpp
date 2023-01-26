#ifndef BOOKSHELF_HPP
#define BOOKSHELF_HPP
#ifndef NOACCOUNTS
#ifndef ACCOUNTSERVICE_HPP
#include "accountservice.hpp"
#endif
#endif
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#endif

class Book{
    public:
        struct info{
            int id = -1;
            int releaseYear = -1;
            int pages = -1;
            int borrowDate = -1;
            int returnDate = -1;
            std::string author = "NULL";
            std::string title = "NULL";
            std::string borrowedBy = "NULL";
        };
        info data;
        void create(int id, int releaseYear, int pages, int borrowDate, int returnDate, std::string author, std::string title, std::string borrowedBy);
        void save();
        void load(int id);
        void printinfo();
        #ifdef NOACCOUNTS
        void loan(std::string user);
        void loan(std::string user, int UNIXborrowDate, int UNIXreturnDate);
        void returnBook();
        #else
        void loan(Account user);
        void loan(Account user, int UNIXborrowDate, int UNIXreturnDate);
        void returnBook(Account user);
        #endif
        int check();
    private:
        void write_str( std::ofstream& out, info& s );
        void read_str(std::ifstream& in, info& s);
};