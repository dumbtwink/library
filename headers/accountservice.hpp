#ifndef ACCOUNTSERVICE_HPP
#define ACCOUNTSERVICE_HPP
#include <openssl/sha.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <filesystem>
#endif

class Account{
    public:
        std::string user;
        std::string storedHash;
        unsigned char hash[SHA_DIGEST_LENGTH];
        void create(std::string user, std::string password);
        void changepassword(std::string password);
        void login(std::string user, std::string password);
        void logout();
        bool check();
};