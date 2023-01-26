#include "../headers/accountservice.hpp"

void Account::create(std::string username, std::string password){
    if(std::filesystem::exists("data/accounts/" + username + ".account")){
        std::cout << "Account already exists" << std::endl;
        return;
    }
    this->user = username;
    SHA1((unsigned char*)password.c_str(), password.length(), hash);
    std::string buffer = username + ";" + std::string(reinterpret_cast< char const* >(hash)) + ";";
    std::ofstream file("data/accounts/" + user + ".account", std::ios::binary);
    file << buffer;
    file.close();
}

void Account::login(std::string username, std::string password){
    SHA1((unsigned char*)password.c_str(), password.length(), hash);
    std::string buffer = username + ";" + std::string(reinterpret_cast< char const* >(hash)) + ";";
    std::ifstream file("data/accounts/" + username + ".account", std::ios::binary);
    std::string line;
    while (std::getline(file, line)){
        if (line == buffer){
            storedHash = std::string(reinterpret_cast< char const* >(hash));
            user = username;
            return;
        }
    }
    std::cout << "Invalid username or password" << std::endl;
}

void Account::logout(){
    user.clear();
    memset(hash, 0, SHA_DIGEST_LENGTH);
}

bool Account::check(){
    std::string buffer = user + ";" + storedHash + ";";
    std::ifstream file("data/accounts/" + user + ".account", std::ios::binary);
    std::string line;
    while (std::getline(file, line)){
        if (line == buffer){
            return true;
        }
    }
    std::cout << "Check failed, please log in again." << std::endl;
    return false;
}

void Account::changepassword(std::string password){
    SHA1((unsigned char*)password.c_str(), password.length(), hash);
    std::string buffer = user + ";" + std::string(reinterpret_cast< char const* >(hash)) + ";";
    std::ofstream file("data/accounts/" + user + ".account", std::ios::binary);
    file << buffer;
    file.close();
}