#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int a, b, u, v, ne = 1;
    int visited[10] = {0}, mincost = 0, cost[10][10];
    int n = 0;
    int path[100] = {0};
    int path_index = 0;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter adjacency matrix: ";

    for(int i = 1; i <= n; i++)
    {
        for(int k = 1; k <= n; k++)
        {
            cin >> cost[i][k];
            if(cost[i][k] == 0)
                cost[i][k] = 999;
        }
    }
    visited[1] = 1;
    cout << '\n';
    while (ne < n)
    {
        int min_ = 999;
        int i = 1;
        for(; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(cost[i][j] < min_)
                {
                    if(visited[i] != 0)
                    {
                        min_ = cost[i][j];
                        a = u = i;
                        b = v = j;
                    }
                }
            }
        }
    if(visited[u] == 0 || visited[v] == 0)
    {
        path[path_index] = b;
        path_index++;
        ne++;
        mincost += min_;
        visited[b] = 1;
    }
    cost[a][b] = cost[b][a] = 999;
    }
    cout << '\n';
    cout << 1  << " --> ";
    for(int i = 0; i < n-1; i++)
    {
        cout << path[i];
        if(i < n-2) cout << " --> ";
    }
    cout << "\n Minimum cost: " << mincost << std::endl;
    return 0;
}
