#include <iostream>
#include <queue>
#define inf 1e9

using namespace std;

int n, m;
int** matrix;
int* S;
int* av;

struct Pair
{
    int first;
    int second;
};

bool operator > (const Pair& p1, const Pair& p2)
{
    return p1.second > p2.second;
}



priority_queue<Pair, vector<Pair>,greater<Pair>> Q;
void reorder()
{
    priority_queue<Pair, vector<Pair>, greater<Pair>> T;
    while (!Q.empty()) 
    {
        Pair tmp;
        tmp.first = Q.top().first;
        tmp.second = Q.top().second;
        for (int i = 0; i < n + 1; i++) {
            if (tmp.first == i)
            {
                tmp.second = av[i];
                break;
            }
        }
        T.push(tmp);
        Q.pop();
    }
    Q = T;
}

void Prim(){
    while(!Q.empty()){
        int u = Q.top().first;
        Q.pop();
        S[u] = 0;//used
        for (int j = 1; j < n+1; j++)
		{
            if (matrix[u][j] != inf && S[j] == 1 && matrix[u][j] < av[j])
            {
                av[j] = matrix[u][j];
            }
		}
        reorder();
    }
}


int main() {
    //init 
    cin >> n >> m;
    matrix = new int* [n + 1];
    for (int i = 0; i < n + 1;i++)
    {
        matrix[i] = new int[n+1];
    }
    for (int i = 0; i < n + 1;i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            matrix[i][j] = inf;
        }
    }

    S = new int[n + 1];
    av = new int[n + 1];

    for (int i = 1; i < n+1; i++)
    {
        Pair v;
        v.first = i;
        v.second = inf;
        Q.push(v);
    }

    for (int k = 0; k < m; k++)
    {
        int i,j;
        cin >> i>>j;
        cin >> matrix[i][j];
        matrix[j][i] = matrix[i][j];
    }

    for (int i = 1; i < n+1; i++)
    {
        S[i] = 1;
    }
    for (int i = 0; i < n + 1; i++)
    {
        av[i] = inf;
    }

    //Prim
    Prim();
    int sum = 0;
    for (int i = 2; i < n + 1; i++)
    {
        sum += av[i];
    }
    cout << sum;

    return 0;
}