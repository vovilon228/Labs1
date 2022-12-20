#include "Book.h"


Book::Book(Date d, int id, std::string name, std::string a, int n, std::string an){
    Book::date = d;
    Book::ID = id;
    Book::name = name;
    Book::auphtor = a;
    Book::N = n;
    Book::annotation = an;
}

Character::Character(std::string n, std::vector<Character::Node> b){
    this->name = n;
    this->books = b;
}
