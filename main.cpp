#include <iostream>
#include "Book.cpp"
#include <string>

int main()
{
    int n;
    std::cout << "Choose type of work:\n1 - Work with Graph\n2 - Work with Books\n3 - Exit()\n>>>";
    std::cin >> n;
    switch(n){
        case 1:
            std::cout << "Choose type of work:\n1 - Matrix\n2 - List\n>>>";
            int nn; std::cin >> nn;
            Graph<int>* G;
            if(nn == 1) G = new GraphM<int>();
            else G = new GraphL<int>();
            while(true){
                std::cout << "Choose command:\n1 - Add vertex\n2 - Add rib\n3 - Del vertex\n";
                std::cout << "4 - Del rib\n5 - Show Graph\n6 - Show in console\n7 - Check  connectivity\n8 - Distance\n9 - Exit()\n>>>";
                std::cin >> nn;
                int N1, N2, N3;
                switch(nn){
                    case 1:
                        std::cout << "Input vertex:";
                        std::cin >> N1;
                        if(!(G->add_vertex(N1))) std::cout << "Can't do that!\n";
                        break;
                    case 2:
                        std::cout << "Input vertex 1:";
                        std::cin >> N1;
                        std::cout << "Input vertex 2:";
                        std::cin >> N2;
                        std::cout << "Input weight:";
                        std::cin >> N3;
                        if(!(G->add_rib(N1, N2, N3))) std::cout << "Can't do that!\n";
                        break;
                    case 3:
                        std::cout << "Input vertex:";
                        std::cin >> N1;
                        if(!(G->del_vertex(N1))) std::cout << "Can't do that!\n";
                        break;
                    case 4:
                        std::cout << "Input vertex 1:";
                        std::cin >> N1;
                        std::cout << "Input vertex 2:";
                        std::cin >> N2;
                        if(!(G->del_rib(N1, N2))) std::cout << "Can't do that!\n";
                        break;
                    case 5:
                        G->show();
                        break;
                    case 6:
                        G->show_in_console();
                        break;
                    case 7:
                        if(G->check_connectivity()) std::cout << "Yes!\n";
                        else std::cout << "NO!\n";
                        break;
                    case 8:
                        int N1, N2;
                        std::cout << "Input vertex 1:";
                        std::cin >> N1;
                        std::cout << "Input vertex 2:";
                        std::cin >> N2;
                        std::cout << G->distance(N1, N2);
                        break;
                    case 9:
                        return 0;
                    default:
                        std::cout << "...";
                }
            }
        case 2:{
            std::vector<Book> books;
            std::vector<Character> characters;
            while(true){
                std::cout << "Choose command:\n1 - Add Book\n2 - Add Character\n3 - Show series\n4 - Exit()\n>>>";
                std::cin >> n;
                switch(n){
                    case 1:{
                        std::string name;
                        std::string auphtor;
                        std::string anotation;
                        int storinki;
                        Book::Date d;
                        std::cout << "Input date(day): ";
                        std::cin >> d.day;
                        std::cout << "Input date(month): ";
                        std::cin >> d.month;
                        std::cout << "Input date(year): ";
                        std::cin >> d.year;
                        std::cout << "Input name: ";
                        std::cin >> name;
                        std::cout << "Input auphtor: ";
                        std::cin >> auphtor;
                        std::cout << "Input kilkist storinok: ";
                        std::cin >> storinki;
                        std::cout << "Input anotation: ";
                        std::cin >> anotation;
                        Book b(d, books.size(), name, auphtor, storinki, anotation);
                        books.push_back(b);
                        break;
                    }
                    case 2:{
                        std::string name;
                        Character::Node node;
                        std::vector<Character::Node> nodes;
                        std::cout << "Input name: ";
                        std::cin >> name;
                        while(true){
                            std::cout << "Input book: ";
                            std::cin >> node.book_id;
                            node.book_id --;
                            std::cout << "Input level in books:\n1 - Main\n2 - Not main\n>>>";
                            std::cin >> node.level;
                            nodes.push_back(node);
                            std::cout << "Is it ALL? (Yes - 1/No - 2): ";
                            int nn; std::cin >> nn;
                            if(nn == 1) break;
                        }
                        Character c(name, nodes);
                        characters.push_back(c);
                        break;
                    }
                    case 3:{
                        GraphL<Character> G;
                        show_series(books, characters, &G);
                        G.show();
                        break;
                    }
                    case 4:
                        return 0;
                    default:
                        std::cout << "...";
                }
            }
        }
        case 3:
            return 0;
        default:
            std::cout << "...";
    }
}


