#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <vector>
#include "Graph.cpp"

class Book
{
    public:
        struct Date{
            int year;
            int month;
            int day;
        };
        Book(Date d, int id, std::string name, std::string a, int n, std::string an);
        int ID;
        std::string name;
        std::string auphtor;
        Date date;
        int N;
        std::string annotation;
};

class Character{
    public:
        struct Node{
            int book_id;
            int level;
        };
        Character(std::string n, std::vector<Node> b);
        std::string name;
        std::vector<Node> books;
};

void show_series(std::vector<Book> books, std::vector<Character> characters, Graph<Character>* G){
    std::vector<std::vector<int> > series;
    for(int i = 0, j = books.size(); i < j; i++) G->add_vertex(i);
    for(int q = 0; q < characters.size(); q++){
        int j = characters[q].books.size();
        if(j > 1)
            for(int i = 0; i < j; i++)
                for(int g = i + 1; g < j; g++)
                    G->add_rib(characters[q].books[i].book_id, characters[q].books[g].book_id, characters[q]);
    }
    for(int q = 0; q < characters.size(); q++){
        int j = characters[q].books.size();
        std::cout << "Serie #" << q <<":\n";
        for(int i = 0; i < j; i++){
            Book b = books[characters[q].books[i].book_id];
            std::cout <<b.ID<<" "<< b.name <<" "<<b.date.day<<"."<<
            b.date.month<<"."<<b.date.year<<" "<< b.auphtor
            <<" "<<b.N<<" "<<b.annotation<< "\n";
        }
    }
}

#endif // BOOK_H
