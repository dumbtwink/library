#include "../headers/bookshelf.hpp"
#ifndef NOACCOUNTS
#ifndef ACCOUNTSERVICE_HPP
#include "accountservice.hpp"
#endif
#endif
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>

void Book::create(int id, int releaseYear, int pages, int borrowDate, int returnDate, std::string author, std::string title, std::string borrowedBy){
    data.id = id;
    data.releaseYear = releaseYear;
    data.pages = pages;
    data.borrowDate = borrowDate;
    data.returnDate = returnDate;
    data.author = author;
    data.title = title;
    data.borrowedBy = borrowedBy;
}

void Book::save(){
   std::string path = "data/books/" + std::to_string(data.id) + ".book";
   std::string buffer = std::to_string(data.id) + ";" + std::to_string(data.releaseYear) + ";" + std::to_string(data.pages) + ";" + std::to_string(data.borrowDate) + ";" + std::to_string(data.returnDate) + ";" + data.author + ";" + data.title + ";" + data.borrowedBy + ";";
   std::ofstream file(path);
   file << buffer;
   file.close();
}

void Book::load(int id){
    std::string path = "data/books/" + std::to_string(id) + ".book";
    std::string buffer;
    std::string token;
    std::vector<std::string> splitbuffer;
    std::ifstream file(path);
    file >> buffer;
    for(int i=0; i < buffer.length(); i++){
        if(buffer.substr(i, 1).compare(";")){
            token.append(buffer.substr(i,1));
        } else {
            splitbuffer.push_back(token);
            token.clear();
        }
    }
    file.close();
    data.id = std::stoi(splitbuffer.at(0));
    data.releaseYear = std::stoi(splitbuffer.at(1));
    data.pages = std::stoi(splitbuffer.at(2));
    data.borrowDate = std::stoi(splitbuffer.at(3));
    data.returnDate = std::stoi(splitbuffer.at(4));
    data.author = splitbuffer.at(5);
    data.title = splitbuffer.at(6);
    data.borrowedBy = splitbuffer.at(7);
}
void Book::printinfo(){
    std::cout << "ID: " << data.id << std::endl;
    std::cout << "Title: " << data.title << std::endl;
    std::cout << "Author: " << data.author << std::endl;
    std::cout << "Release Year: " << data.releaseYear << std::endl;
    std::cout << "Pages: " << data.pages << std::endl;
    std::cout << "Borrowed By: " << data.borrowedBy << std::endl;
    std::cout << "Borrow Date: " << data.borrowDate << std::endl;
    std::cout << "Return Date: " << data.returnDate << std::endl;
}

#ifdef NOACCOUNTS
void Book::loan(std::string user){
    data.borrowedBy = user;
#else
void Book::loan(Account user){
    if(user.check()){
        data.borrowedBy = user.user;
    } else {
        std::cout << "User is not logged in!" << std::endl;
        return;
    }
#endif
    data.borrowDate = time(0);
    data.returnDate = time(0) + 604800;
    save();
}

#ifdef NOACCOUNTS
void Book::loan(std::string user, int UNIXborrowDate, int UNIXreturnDate){
    data.borrowedBy = user;
#else
void Book::loan(Account user, int UNIXborrowDate, int UNIXreturnDate){
    if(user.check()){
        data.borrowedBy = user.user;
    } else {
        std::cout << "User is not logged in!" << std::endl;
        return;
    }
#endif
    data.borrowDate = UNIXborrowDate;
    data.returnDate = UNIXreturnDate;
    save();
}

#ifdef NOACCOUNTS
void Book::returnBook(){
#else
void Book::returnBook(Account user){
    if(user.check()){
        if(user.user.compare(data.borrowedBy)!=0){
            std::cout << "User is not the borrower!" << std::endl;
            return;
        }
    } else {
        std::cout << "User is not logged in!" << std::endl;
        return;
    }
#endif
    data.borrowedBy = "NULL";
    data.borrowDate = -1;
    data.returnDate = -1;
    save();
}

int Book::check(){
    if(data.borrowedBy.compare("NULL")==0){
        return 0;
    }
    if(data.returnDate < time(0)){
        return 2;
    }else{
        return 1;
    }
}