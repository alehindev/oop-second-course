#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

int INF = 1000000000;

// 1
vector<vector<int>> PrimsAlg(vector<vector<int>> g)
{
    for (int i = 0; i < g.size(); i++)
        for (int j = 0; j < g.size(); j++)
            if (g[i][j] == 0)
                g[i][j] = INF;
    vector<vector<int>> res(g.size());
    for (int i = 0; i < g.size(); i++)
        res[i] = vector<int>(g.size(), 0);
    vector<bool> used(g.size());
    vector<int> min_e(g.size(), INF), sel_e(g.size(), -1);
    for (int i = 0; i < g.size(); i++)
    {
        int v = -1;
        for (int j = 0; j < g.size(); j++)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        used[v] = true;
        if (sel_e[v] != -1)
        {
            res[v][sel_e[v]] = g[v][sel_e[v]];
            res[sel_e[v]][v] = g[sel_e[v]][v];
        }
        for (int to = 0; to < g.size(); ++to)
            if (g[v][to] < min_e[to])
            {
                min_e[to] = g[v][to];
                sel_e[to] = v;
            }
    }
    return res;
}

// 2
vector<int> DFS(vector<vector<int>> g, int s)
{
    vector<int> res;
    vector<bool> used(g.size());
    stack<int> Stack;
    Stack.push(s);
    while (!Stack.empty())
    {
        int node = Stack.top();
        Stack.pop();
        if (used[node]) continue;
        used[node] = true;
        res.push_back(node);
        for (int i = 0; i < g.size(); i++)
            if (g[node][i] > 0 && !used[i])
                Stack.push(i);
    }
    return res;
}

// 3
vector<int> DijkstraAlg(vector<vector<int>> mat, int s)
{
    int INF = 1000000000;
    vector<int> d(mat.size(), INF), p(mat.size());
    d[s] = 0;
    vector<bool> u(mat.size());
    for (int i = 0; i < mat.size(); i++)
    {
        int v = -1;
        for (int j = 0; j < mat.size(); j++)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == INF)
            break;
        u[v] = true;
        for (size_t j = 0; j < mat.size(); j++)
        {
            if (mat[v][j] == 0) continue;
            if (d[v] + mat[v][j] < d[j])
            {
                d[j] = d[v] + mat[v][j];
                p[j] = v;
            }
        }
    }
    return d;
}

// 4
vector<int> BFS(vector<vector<int>> mat, int s)
{
    queue<int> q;
    q.push(s);
    vector<bool> used(mat.size());
    vector<int> d(mat.size()), p(mat.size());
    used[s] = true;
    p[s] = -1;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < mat[v].size(); i++)
        {
            int to = mat[v][i];
            if (!used[to])
            {
                used[to] = true;
                q.push(to);
                d[to] = d[v] + 1;
                p[to] = v;
            }
        }
    }
    return p;
}

vector<int> Degree(vector<vector<int>> mat)
{
    vector<int> res(mat.size(), 1);
    vector<int> p = BFS(mat, 0);
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i] == -1) res[i]--;
        for (int j = 0; j < p.size(); j++)
        {
            if (p[j] == i) res[i]++;
        }
    }
    return res;
}

float AVG(vector<vector<int>> a)
{
    vector<int> tmp = Degree(a);
    float res = 0;
    for (int i = 0; i < tmp.size(); i++)
    {
        res += tmp[i];
    }
    return res / tmp.size();
}

int main()
{
    // матрица смежности

    vector<vector<int> > mat =
    {
        { 0, 9, 7, 1, 5, 4, 5, 3, 8, 1, 0, 7, 4, 0, 8 },
        { 9, 0, 7, 3, 2, 7, 0, 9, 8, 5, 0, 6, 4, 1, 3 },
        { 7, 7, 0, 2, 2, 2, 2, 3, 9, 5, 1, 5, 0, 4, 4 },
        { 1, 3, 2, 0, 4, 4, 1, 0, 6, 9, 7, 2, 3, 6, 2 },
        { 5, 2, 2, 4, 0, 4, 4, 8, 4, 2, 4, 5, 7, 6, 9 },
        { 4, 7, 2, 4, 4, 0, 9, 0, 3, 1, 6, 4, 8, 8, 8 },
        { 5, 0, 2, 1, 4, 9, 0, 2, 2, 4, 5, 4, 2, 6, 1 },
        { 3, 9, 3, 0, 8, 0, 2, 0, 4, 1, 9, 9, 5, 5, 7 },
        { 8, 8, 9, 6, 4, 3, 2, 4, 0, 0, 7, 3, 7, 4, 1 },
        { 1, 5, 5, 9, 2, 1, 4, 1, 0, 0, 7, 6, 1, 2, 9 },
        { 0, 0, 1, 7, 4, 6, 5, 9, 7, 7, 0, 9, 6, 7, 8 },
        { 7, 6, 5, 2, 5, 4, 4, 9, 3, 6, 9, 0, 6, 2, 2 },
        { 4, 4, 0, 3, 7, 8, 2, 5, 7, 1, 6, 6, 0, 2, 7 },
        { 0, 1, 4, 6, 6, 8, 6, 5, 4, 2, 7, 2, 2, 0, 7 },
        { 8, 3, 4, 2, 9, 8, 1, 7, 1, 9, 8, 2, 7, 7, 0 },
    };

    vector<vector<int>> tree = PrimsAlg(mat);
    vector<int> dfs = DFS(tree, 0);
    vector<int> min_path = DijkstraAlg(mat, 0);
    vector<int> tree_deg = Degree(tree);
    cout << "\nTree: \n";
    for (int i = 0; i < tree.size(); i++)
    {
        for (int j = 0; j < tree.size(); j++)
            cout << tree[i][j] << " ";
        cout << endl;
    }
    cout << "\nDFS: ";
    for (int i = 0; i < dfs.size(); i++)
        cout << dfs[i] << " ";
    cout << "\nMin path: ";
    for (int i = 0; i < min_path.size(); i++)
        cout << min_path[i] << " ";
    cout << "\nDegree: ";
    for (int i = 0; i < tree_deg.size(); i++)
        cout << tree_deg[i] << " ";
    cout << "\nAVG: ";
    cout << AVG(tree);

    char c; cin >> c;
    return 0;
}