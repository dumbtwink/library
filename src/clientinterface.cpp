#include "../headers/bookshelf.hpp"
#ifndef NOACCOUNTS
#ifndef ACCOUNTSERVICE_HPP
#include "accountservice.hpp"
#endif
#endif
#include <vector>
#include <algorithm>
#include <climits>
#include <memory>

std::string command;
#ifdef NOACCOUNTS
std::vector<std::string> possibleInputs = {"READ", "CREATE", "LOAN", "RETURN", "CHECK", "HELP", "EXIT"};
#else
std::vector<std::string> possibleInputs = {"READ", "CREATE", "LOAN", "RETURN", "CHECK", "HELP", "EXIT", "LOGIN", "LOGOUT", "REGISTER", "CHANGEPASS"};
Account user;
#endif

std::vector<std::string> splitArgs(const std::string str) {
    std::vector<std::string> result;
    std::string token;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] != ' ') {
            token += str[i];
        } else {
            result.push_back(token);
            token.clear();
        }
    }
    if(!token.empty()){
        result.push_back(token);
    }
    return result;
}

bool toofewargs(std::string input, int args){
    if(splitArgs(input).size() < args){
        std::cout << "ERROR: Too few arguments" << std::endl;
        return true;
    }
    return false;
}

void showHelp(){
    #ifdef NOACCOUNTS
    std::cout << "__Available commands__\nRead [ID]\nCreate [ID]\nLoan [ID] [USER]\nReturn [ID]\nCheck [ID]\nHelp\nExit" << std::endl;
    #else
    std::cout << "__Available commands__\nRead [ID]\nCreate [ID]\nLoan [ID] [USER]\nReturn [ID]\nCheck [ID]\nHelp\nExit\nLogin [USER] [PASSWORD]\nLogout\nRegister [USER] [PASSWORD]\nChangepass [PASSWORD]" << std::endl;
    #endif
}

int checkPos(std::string input, std::vector<std::string> index) {
    for(int i=0; i<index.size(); i++){
        if(splitArgs(input)[0].compare(index[i])==0){
            return i;
        }
    }
    return -1;
}

int main(){
    std::cout << "LIBRARY SOFTWARE - DEVELOPED BY ALEX ROOTH" << std::endl;
    while(true){
        int id, releaseYear, pages, borrowDate, returnDate;
        std::string author, title, borrowedBy;
        Book buffer;
        std::cout << ">> ";
        std::getline(std::cin, command);
        std::transform(command.begin(), command.end(),command.begin(), ::toupper);
        try{
            switch(checkPos(command, possibleInputs)){
                case 0:
                    if(toofewargs(command, 2)){
                        break;
                    }
                    buffer.load(std::stoi(splitArgs(command)[1]));
                    buffer.printinfo();
                    break;
                case 1:
                    id = std::stoi(splitArgs(command)[1]);
                    std::cout << "Title: ";
                    std::cin >> title;
                    std::cout << "Author: ";
                    std::cin >> author;
                    std::cout << "Release Year: ";
                    std::cin >> releaseYear;
                    std::cout << "Pages: ";
                    std::cin >> pages;
                    borrowDate = -1;
                    returnDate = -1;
                    borrowedBy = "NULL";
                    buffer.create(id, releaseYear, pages, borrowDate, returnDate, author, title, borrowedBy);
                    buffer.save();
                    break;
                case 2:
                    #ifndef NOACCOUNTS
                    if(toofewargs(command, 2)){
                        break;
                    }
                    #else
                    if(toofewargs(command, 3)){
                        break;
                    }
                    #endif
                    buffer.load(std::stoi(splitArgs(command)[1]));
                    #ifdef NOACCOUNTS
                    buffer.loan(splitArgs(command)[2]);
                    #else
                    buffer.loan(user);
                    #endif
                    break;
                case 3:
                    if(toofewargs(command, 2)){
                        break;
                    }
                    buffer.load(std::stoi(splitArgs(command)[1]));
                    if(buffer.check()==2){
                        std::cout << "Return is overdue" << std::endl;
                    }
                    #ifdef NOACCOUNTS
                    buffer.returnBook();
                    #else
                    buffer.returnBook(user);
                    #endif
                    break;
                case 4:
                    if(toofewargs(command, 2)){
                        break;
                    }
                    buffer.load(std::stoi(splitArgs(command)[1]));
                    switch(buffer.check()){
                        case 0:
                            std::cout << "Status (0): Not loaned" << std::endl;
                            break;
                        case 1:
                            std::cout << "Status (1): Loaned" << std::endl;
                            break;
                        case 2:
                            std::cout << "Status (2): Overdue" << std::endl;
                            break;
                    }
                    break;
                case 5:
                    showHelp();
                    break;
                case 6:
                    return 0;
                #ifndef NOACCOUNTS
                case 7:
                    if(toofewargs(command, 3)){
                        break;
                    }
                    user.login(splitArgs(command)[1], splitArgs(command)[2]);
                    break;
                case 8:
                    user.logout();
                    break;
                case 9:
                    if(toofewargs(command, 3)){
                        break;
                    }
                    user.create(splitArgs(command)[1], splitArgs(command)[2]);
                    break;
                case 10:
                    if(toofewargs(command, 2)){
                        break;
                    }
                    user.changepassword(splitArgs(command)[1]);
                    break;
                #endif
                default:
                    std::cout << "ERROR: Invalid command" << std::endl;
                    showHelp();
                    break;
            }
        }
        catch(...)
        {
                    std::cout << "ERROR: Syntax error" << std::endl;
                    showHelp();
        }
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        command.clear(); 
    }
}