#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <list>
#include <cstddef>
#include <iostream>
#include <queue>
#include <windows.h>
#include <windowsx.h>
#include <cstdlib>

HINSTANCE hInstance;
HINSTANCE hPrevInst;
LPSTR lpszArgs;
int nWinMode;

template <typename T>
class Graph
{
    public:
        virtual bool add_vertex(int N) = 0;
        virtual bool add_rib(int N1, int N2, T weight) = 0;
        virtual bool del_vertex(int N) = 0;
        virtual bool del_rib(int N1, int N2) = 0;
        virtual bool check_connectivity() = 0;
        virtual int distance(int N1, int N2) = 0 ;
        void show();
        virtual void show_in_console() = 0;
        template <typename T2>
        bool check_node(int N, T2 v);
        static LRESULT CALLBACK WindowFunc(HWND, UINT, WPARAM, LPARAM);
    private:
        virtual int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode) = 0;
};

template <typename T>
class GraphM : public Graph<T>
{
    public:
        bool add_vertex(int N) override;
        bool add_rib(int N1, int N2, T weight) override;
        bool del_vertex(int N) override;
        bool del_rib(int N1, int N2) override;
        bool check_connectivity() override;
        int distance(int N1, int N2) override;
        void show_in_console() override;
    private:
        int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode) override;
        std::vector<std::vector<T> > matrix;
};

template <typename T>
class GraphL : public Graph<T>
{
    public:
        bool add_vertex(int N) override;
        bool add_rib(int N1, int N2, T weight) override;
        bool del_vertex(int N) override;
        bool del_rib(int N1, int N2) override;
        bool check_connectivity() override;
        int distance(int N1, int N2) override;
        void show_in_console() override;
    private:
        int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode) override;
        struct Node{
            int N;
            T weight;
        };
        std::vector<std::list<Node> > _list;
};
#endif // GRAPH_H
