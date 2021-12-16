#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm> 

using namespace std;

int infinity = 1000000;

// 1 и 2
bool bfs(vector<vector<int>>* graph, int s, int t, vector<int>* parent)
{
    vector<bool> visited(graph->size(), 0);
    queue<int> q;
    q.push(s);
    visited[s]=true;
    (*parent)[s]=-1;
    while (!q.empty())
    {
        int u=q.front();
        q.pop();
        for (int v=0; v<graph->size(); v++)
        {
            if (visited[v]==false && (*graph)[u][v]>0)
            {
                if (v==t)
                {
                    (*parent)[v]=u;
                    return true;
                }
                q.push(v);
                (*parent)[v]=u;
                visited[v]=true;
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<int>> graph, int s, int t)
{
    int u,v;
    vector<vector<int>> graphC(graph);
    vector<int> parent(graph.size());
    int max_flow=0;
    while (bfs(&graphC, s, t, &parent))
    {
        int path_flow=infinity;
        for (v=t; v!=s; v=parent[v])
        {
            u=parent[v];
            path_flow=min(path_flow, graphC[u][v]);
        }
        for (v=t; v!=s; v=parent[v])
        {
            u=parent[v];
            graphC[u][v]-=path_flow;
            graphC[v][u]+=path_flow;
        }
        max_flow+=path_flow;
    }
    return max_flow;
}

// 3
class Edge
{
public:
	int from, to, weight;
	Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
	Edge(const Edge& E)
	{
		from=E.from;
		to=E.to;
		weight=E.weight;
	}
	int operator<(Edge& E)
	{
		return (weight<E.weight);
	}
	friend ostream& operator<<(ostream& s, Edge& e);
};

ostream& operator<<(ostream& s, Edge& e)
{
	s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
	return s;
}

void paintgraph(vector<vector<int> >& matrix, vector <int>& color, int curr=0)
{
	//структура данных для цветов смежных вершин с исследуемой
	set<int> neighbours;

	//аналоги поиска в ширину
	queue<int> q;
	q.push(curr);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		//вершина уже закрашена?
		if (color[curr] != 0)
			continue;
		neighbours.clear();

		for (int next = 0; next < matrix.size(); next++)
			if (matrix[curr][next] != 0)
            {
                q.push(next);
                if (color[next]!=0)
                {
                    neighbours.insert(color[next]);
                }
            }

		//счетчик цветов - ищем допустимый цвет с наименьшим индексом
		int color_counter = 1;
		auto it = neighbours.begin();
		do
		{
			//есть ли этот номер цвета среди соседей?
			it = neighbours.find(color_counter);
			if(it==neighbours.end())
			    break;
			color_counter++;
		} while (true);

		//красим вершину в допустимый цвет
		color[curr] = color_counter;
	}
}

// 4
bool hamilton(vector<vector<int> >& mat, vector <bool>& visited, vector <int>& path, int curr)
{
	path.push_back(curr);
	//путь содержит все вершины: если есть связь последней вершины с исходной, цикл найден
	//если нет, откатываемся на шаг назад
	if(path.size() == mat[0].size())
	{
		//ищем г-в цикл - проверяем, что path[0] и curr смженые
		if(mat[curr][path[0]]>0)
			return true;
		else false;
	}
	//if(path.size() == mat[0].size())
		//return true;
	//г-в путь
	//return path.size() == mat[0].size()

	//вершина использована в пути
	visited[curr] = true;
	//проверить всех непосещенных соседей вершины curr
	for(int i = 0; i<mat.size(); i++)
	{
		if(mat[curr][i]>0 && !visited[i])
		{
			if (hamilton(mat, visited, path, i))
				return true;
		}
	}
	
	//этот путь не подходит, убираем вершину и откатываемся
	visited[curr] = false;
	path.pop_back();
	return false;
}

int main()
{
    // 1
    vector<vector<int>> matrix = {
        { 0, 9, 0, 2, 7, 4, 7, 8, 4 },
        { 9, 0, 5, 5, 0, 7, 8, 1, 5 },
        { 0, 5, 0, 6, 3, 9, 3, 3, 0 },
        { 2, 5, 6, 0, 3, 4, 3, 9, 5 },
        { 7, 0, 3, 3, 0, 0, 9, 0, 4 },
        { 4, 7, 9, 4, 0, 0, 5, 9, 6 },
        { 7, 8, 3, 3, 9, 5, 0, 9, 8 },
        { 8, 1, 3, 9, 0, 9, 9, 0, 1 },
        { 4, 5, 0, 5, 4, 6, 8, 1, 0 },};

    cout << "Max flow from 0 to " << matrix.size()-1 << ": " << fordFulkerson(matrix, 0, matrix.size()-1) << endl;
    
    // 2
    int n,m;
    n=4;
    m=8;
    vector<vector<int>> edges = {{4,5,7}, {5,6}, {4}, {4,6,7}};
    
    vector<vector<int>> pair_matrix;
    
    for (int i=0; i<(n+m+2); i++)
    {
        vector<int> n_edges((n+m+2), 0);
        pair_matrix.push_back(n_edges);
    }

    for (int i=0; i<n; i++)
    {
		pair_matrix[0][i+2]=1;
		pair_matrix[i+2][0]=-1;
        for (int j=0; j<edges[i].size(); j++)
        {
            pair_matrix[i+2][n+edges[i][j]+2]=1;
        }
	}
    
    for (int i=0; i<m; i++)
    {
		pair_matrix[1][n+i+2]=-1;
		pair_matrix[n+i+2][1]=1;
	}
    
    cout << "Max matching " << fordFulkerson(pair_matrix, 0, 1) << endl;

    // 3
    vector<int> color(matrix.size(), 0);
	paintgraph(matrix, color, 0);
	cout << "Color: ";
	for (int i=0; i<matrix.size(); i++) cout << color[i] << " ";
    cout << endl;

    // 4
    vector<bool> visited(matrix.size(), 0);
	vector<int> path;
    cout << "Hamilton: " << hamilton(matrix, visited, path, 0)<< ": ";
	for(int i=0; i<path.size(); i++)
		cout << path[i] << " ";
    cout << endl;
}
