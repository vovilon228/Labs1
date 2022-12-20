#include "Graph.h"

//------Graph-------------
template <typename T>
template <typename T2>
bool Graph<T>::check_node(int N, T2 v){
    if(N < v.size()) return true;
    return false;
}

template <typename T>
void Graph<T>::show(){
    WinMain(hInstance, hPrevInst, lpszArgs, nWinMode);
}

template <typename T>
LRESULT Graph<T>::CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        default:
            return DefWindowProc (hwnd,message,wParam,lParam);
    }
}

//-------GraphM---------
template <typename T>
bool GraphM<T>::add_vertex(int N){
    if( GraphM<T>::check_node(N, GraphM::matrix) == true) return false;
    std::vector<T> new_vertex(GraphM::matrix.size() + 1, NULL);
    GraphM<T>::matrix.push_back(new_vertex);
    for(int i = 0, j = GraphM::matrix.size(); i < j; i++)
        matrix[i].resize(j);
    return true;
}

template <typename T>
bool GraphM<T>::add_rib(int N1, int N2, T weight){
    if(!GraphM::check_node(N1, GraphM::matrix)) return false;
    if(!GraphM::check_node(N2, GraphM::matrix)) return false;
    GraphM::matrix[N1][N2] = weight;
    GraphM::matrix[N2][N1] = weight;
    return true;
}

template <typename T>
bool GraphM<T>::del_vertex(int N){
    if(!GraphM::check_node(N, GraphM::matrix)) return false;
    GraphM::matrix.erase(GraphM::matrix.begin() + N);
    for(int i = 0, j = GraphM::matrix.size(); i < j; i++)
        GraphM::matrix[i].erase(GraphM::matrix[i].begin() + N);
    return true;
}

template <typename T>
bool GraphM<T>::del_rib(int N1, int N2){
    if(!GraphM::check_node(N1, GraphM::matrix)) return false;
    if(!GraphM::check_node(N2, GraphM::matrix)) return false;
    GraphM::matrix[N1][N2] = NULL;
    GraphM::matrix[N2][N1] = NULL;
    return true;
}

template <typename T>
bool GraphM<T>::check_connectivity(){
    if(GraphM::matrix.size() == 0) return true;
    int arr[GraphM::matrix.size()] = {0};
    arr[0] = 1;
    int x = 0;
    bool flag = true;
    while(flag){
        for(int i = 0; i < GraphM::matrix.size(); i++){
            if(arr[i] == 1){
                arr[i] = 2;
                for(int j = 0; j < GraphM::matrix.size(); j++){
                    if(GraphM::matrix[i][j] && arr[j] == 0) arr[j] = 1;
                }
            }
        }
        flag = false;
        for(int i = 0; i < GraphM::matrix.size(); i++)
            if(arr[i] == 1) flag = true;
    }
    for(int i = 0; i < GraphM::matrix.size(); i++)
        if(arr[i] == 0) return false;
    return true;
}

template <typename T>
int GraphM<T>::distance(int N1, int N2){
    bool arr[GraphM<T>::matrix.size()];
    int dist[GraphM<T>::matrix.size()];
    for(int i = 0, j= GraphM<T>::matrix.size(); i < j; i++){
        dist[i] = -1;
        arr[i] = false;
    }
    std::queue<int> q;
    q.push(N1);
    arr[N1] = true;
    dist[N1] = 0;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int i = 0, j= GraphM<T>::matrix.size(); i < j; i++){
            if(matrix[v][i] && !arr[i]){
                q.push(i);
                arr[i] = true;
                dist[i] = dist[v] + 1;
            }
        }
    }
    return dist[N2];
}

template <typename T>
void GraphM<T>::show_in_console(){
    int n = GraphM::matrix.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            std::cout << GraphM::matrix[i][j] <<" ";
        std::cout << "\n";
    }
}

template <typename T>
int GraphM<T>::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode){
    char szWinName[] = "GraphWindow";
    char szTitle[] = "Graph";
    MSG msg = {0};
    WNDCLASS wc;
    ZeroMemory(&wc,sizeof(wc));
    wc.hInstance = hInstance;
    wc.lpszClassName = szWinName;
    wc.lpfnWndProc = this->WindowFunc;
    wc.style = 0;
    wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    RegisterClass (&wc);
    int width = 60*matrix.size();
    int haigh = 30*matrix.size();
    int k = 20;
    HWND hwnd = CreateWindow (
        szWinName, szTitle,
        WS_OVERLAPPEDWINDOW,
        400, 100,
        width, haigh,
        HWND_DESKTOP, NULL,
        hInstance, NULL);
    ShowWindow (hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    int X[matrix.size()] = {0};
    int Y[matrix.size()] = {0};
            srand(rand());
    for(int i = 0, j = matrix.size(); i < j; i++){
        X[i] = (width/j)*i + k;
        Y[i] = rand()%(haigh - k*4 + 1) + k;
    }
    HBRUSH hBrush1 = CreateSolidBrush(RGB(255,255,255));
    HDC hdc = GetDC(hwnd);
    SelectObject(hdc, hBrush1);
    for(int i = 0, j = matrix.size(); i < j; i++){
        for(int q = 0; q < j; q++){
            if(matrix[i][q]){
                MoveToEx(hdc, X[i], Y[i], NULL);
                LineTo(hdc, X[q], Y[q]);
            }
        }
    }
    for(int i = 0, j = matrix.size(); i < j; i++){
        Ellipse(hdc, X[i]-k, Y[i]-k, X[i]+k, Y[i]+k);
        char message[2] = {i + '0', '\0'};
        RECT rect;
        rect.left=X[i] - 5;
        rect.top=Y[i] - 7;
        DrawText(hdc, (message), -1, &rect, DT_SINGLELINE | DT_NOCLIP  ) ;
    }
    while (GetMessage(&msg, NULL, 0, 0) > 0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

//---------GraphL----------
template <typename T>
bool GraphL<T>::add_vertex(int N){
    if(GraphL::check_node(N, GraphL::_list)) return false;
    std::list <GraphL::Node> new_vertex;
    GraphL::_list.push_back(new_vertex);
    return true;
}

template <typename T>
bool GraphL<T>::add_rib(int N1, int N2, T weight){
    if(!GraphL::check_node(N1, GraphL::_list)) return false;
    if(!GraphL::check_node(N2, GraphL::_list)) return false;
    GraphL::Node node1 = {N2, weight};
    GraphL::Node node2 = {N1, weight};
    typename std::list<GraphL::Node>::iterator it;
    for(it = GraphL::_list[N1].begin(); it != GraphL::_list[N1].end(); ){
        if((*it).N > N2){
            it--;
            break;
        }
        it++;
    }
    GraphL::_list[N1].insert(it, node1);
    for(it = GraphL::_list[N2].begin(); it != GraphL::_list[N2].end(); ){
        if((*it).N > N1){
            it--;
            break;
        }
        it++;
    }
    GraphL::_list[N2].insert(it , node2);
    return true;
}

template <typename T>
bool GraphL<T>::del_vertex(int N){
    if(!GraphL::check_node(N, GraphL::_list)) return false;
    GraphL::_list.erase(GraphL::_list.begin() + N);
    for(int i = 0, j = GraphL::_list.size(); i < j; i++){
        typename std::list<GraphL::Node>::iterator it;
        for(it = GraphL::_list[i].begin(); it != GraphL::_list[i].end(); it++){
            if((*it).N > N) break;
            if((*it).N == N){
                GraphL::_list[i].erase(it);
                break;
            }
        }
    }
    return true;
}

template <typename T>
bool GraphL<T>::del_rib(int N1, int N2){
    if(!GraphL::check_node(N1, GraphL::_list)) return false;
    if(!GraphL::check_node(N2, GraphL::_list)) return false;
    typename std::list<GraphL::Node>::iterator it;
    for(it = GraphL::_list[N1].begin(); it != GraphL::_list[N1].end(); it++){
        if((*it).N == N2){
            GraphL::_list[N1].erase(it);
            break;
        }
    }
    for(it = GraphL::_list[N2].begin(); it != GraphL::_list[N2].end(); it++){
        if((*it).N == N1){
            GraphL::_list[N2].erase(it);
            break;
        }
    }
    return true;
}

template <typename T>
bool GraphL<T>::check_connectivity(){
    if(GraphL::_list.size() == 0) return true;
    int arr[GraphL::_list.size()] = {0};
    arr[0] = 1;
    int x = 0;
    bool flag = true;
    while(flag){
        for(int i = 0; i < GraphL::_list.size(); i++){
            if(arr[i] == 1){
                arr[i] = 2;
                typename std::list<GraphL::Node>::iterator it;
                for(it = GraphL::_list[i].begin(); it != GraphL::_list[i].end(); it++){
                    if(arr[(*it).N] == 0) arr[(*it).N] = 1;
                }
            }
        }
        flag = false;
        for(int i = 0; i < GraphL::_list.size(); i++)
            if(arr[i] == 1) flag = true;
    }
    for(int i = 0; i < GraphL::_list.size(); i++)
        if(arr[i] == 0) return false;
    return true;
}

template <typename T>
int GraphL<T>::distance(int N1, int N2){
    bool arr[GraphL<T>::_list.size()];
    int dist[GraphL<T>::_list.size()];
    for(int i = 0, j= GraphL<T>::_list.size(); i < j; i++){
        dist[i] = -1;
        arr[i] = false;
    }
    std::queue<int> q;
    q.push(N1);
    arr[N1] = true;
    dist[N1] = 0;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        typename std::list<GraphL::Node>::iterator it;
        for(it = GraphL::_list[v].begin(); it != GraphL::_list[v].end(); it++){
            if(!arr[(*it).N]){
                q.push((*it).N);
                arr[(*it).N] = true;
                dist[(*it).N] = dist[v] + 1;
            }
        }
    }
    return dist[N2];
}

template <typename T>
int GraphL<T>::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode){
    char szWinName[] = "GraphWindow";
    char szTitle[] = "Graph";
    MSG msg = {0};
    WNDCLASS wc;
    ZeroMemory(&wc,sizeof(wc));
    wc.hInstance = hInstance;
    wc.lpszClassName = szWinName;
    wc.lpfnWndProc = this->WindowFunc;
    wc.style = 0;
    wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    RegisterClass (&wc);
    int width = 60*_list.size() + 100;
    int haigh = 30*_list.size() + 100;
    int k = 20;
    HWND hwnd = CreateWindow (
        szWinName, szTitle,
        WS_OVERLAPPEDWINDOW,
        400, 100,
        width, haigh,
        HWND_DESKTOP, NULL,
        hInstance, NULL);
    ShowWindow (hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    int X[_list.size()] = {0};
    int Y[_list.size()] = {0};
    srand(rand());
    for(int i = 0, j = _list.size(); i < j; i++){
        X[i] = (width/j)*i + k;
        Y[i] = rand()%(haigh - k*4 + 1) + k;
    }
    HBRUSH hBrush1 = CreateSolidBrush(RGB(255,255,255));
    HDC hdc = GetDC(hwnd);
    SelectObject(hdc, hBrush1);
    for(int i = 0, j = _list.size(); i < j; i++){
        typename std::list<GraphL::Node>::iterator it;
        for(it = _list[i].begin(); it != _list[i].end(); it++){
            MoveToEx(hdc, X[i], Y[i], NULL);
            LineTo(hdc, X[(*it).N], Y[(*it).N]);
        }
    }
    for(int i = 0, j = _list.size(); i < j; i++){
        Ellipse(hdc, X[i]-k, Y[i]-k, X[i]+k, Y[i]+k);
        char message[2] = {i + '0', '\0'};
        RECT rect;
        rect.left=X[i] - 5;
        rect.top=Y[i] - 7;
        DrawText(hdc, (message), -1, &rect, DT_SINGLELINE | DT_NOCLIP  ) ;
    }
    while (GetMessage(&msg, NULL, 0, 0) > 0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

template <typename T>
void GraphL<T>::show_in_console(){
    int n = GraphL::_list.size();
    for(int i = 0; i < n; i++){
        std::cout << i << "->";
        typename std::list<GraphL::Node>::iterator it;
        for(it = GraphL::_list[i].begin(); it != GraphL::_list[i].end(); it++){
            std::cout << (*it).N << " ";
        }
        std::cout << "\n";
    }
}
