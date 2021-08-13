#include <iostream>
#include <stack>
#include <queue>
#include <array>
#include <vector>
#include <set>


// tested x64, c++17

using namespace std;

void TestStack()
{
    stack<int> s;

    s.push(5);
    s.push(3);
    s.push(7);
    s.pop();
    s.push(1);
    s.push(4);
    s.pop();

    cout << "test stack: ";
    while (!s.empty()) {
        cout << s.top() << ' ';
        s.pop();
    }
    cout << endl;
}

void TestQueue()
{
    queue<int> q;

    q.push(5);
    q.push(3);
    q.push(7);
    q.pop();
    q.push(1);
    q.push(4);
    q.pop();

    cout << "test queue: ";
    while (!q.empty()) {
        cout << q.front() << ' ';
        q.pop();
    }
    cout << endl;
}


int FactorialIterative(int n) {
    int result = 1;

    for (int i = 1; i <= n; ++i)
        result *= i;

    return result;
}

int FactorialRecursive(int n) {
    if (n <= 1)
        return 1;

    // n! = n * (n - 1)!
    return n * FactorialRecursive(n - 1);
}

void TestFactorial()
{
    cout << "반복적으로 구현:" << FactorialIterative(5) << endl;
    cout << "재귀적으로 구현:" << FactorialRecursive(5) << endl;
}


void TestAdjacencyMatrix()
{
    const int INF = 999999999;;

    int graph[3][3] = {
        {0, 7, 5},
        {7, 0, INF},
        {5, INF, 0}
    };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << graph[i][j] << ' ';
        }
        cout << endl;
    }
}

void TestAdjacencyList()
{
    vector<pair<int, int>> graph[3];

    graph[0].push_back({ 1, 7 }); // node 0, {node, dist}
    graph[0].push_back({ 2, 5 });
    graph[1].push_back({ 0, 7 }); // node 1
    graph[2].push_back({ 0, 5 }); // node 2

    for (int i = 0; i < 3; ++i) {
        for (auto& node : graph[i]) {
            cout << '(' << node.first << ',' << node.second << ')' << ' ';
        }
        cout << endl;
    }
}


vector<int> graph[9] = {
    {0}, {2, 3, 8}, {1, 7},
    {1, 4, 5}, {3, 5}, {3, 4},
    {7}, {2, 6, 8}, {1, 7}
};
array<bool, 9> visited = { false, };

void DFS(int node)
{
    visited[node] = true;
    cout << node << ' ';

    for (int next : graph[node]) {
        if (!visited[next])
            DFS(next);
    }
}

void BFS(int node)
{
    queue<int> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        int node_q = q.front();
        q.pop();
        cout << node_q << ' ';

        for (int next : graph[node_q]) {
            if (visited[next])
                continue;

            q.push(next);
            visited[next] = true;
        }
    }
}

void TestDfsBfs()
{
    cout << "DFS: ";
    visited.fill(false);
    DFS(1);

    cout << endl << "BFS: ";
    visited.fill(false);
    BFS(1);
}


const int size_x = 10;
const int size_y = 10;

// result 5
int graph_dfs[size_x][size_y] = {
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 1, 0, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 0, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 0, 1, 1, 1, 0,
    1, 0, 1, 1, 1, 0, 0, 1, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 1, 0, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0
};

bool DFS_EX(int x, int y)
{
    if (x <= -1 || x >= size_x || y <= -1 || y >= size_y)
        return false;

    if (graph_dfs[x][y] != 0)
        return false;

    graph_dfs[x][y] = 1;

    DFS_EX(x - 1, y); // up
    DFS_EX(x, y - 1); // left
    DFS_EX(x + 1, y); // down
    DFS_EX(x, y + 1); // right

    return true;
}

void TestDfs_Ex()
{
    /*int size_x, size_y;
    cin >> size_x >> size_y;

    for (int i = 0; i < size_x; ++i) {
        for (int j = 0; j < size_y; ++j) {
            cin >> graph_ex[i][j];
        }
    }*/
 
    int result = 0;
    for (int i = 0; i < size_x; ++i) {
        for (int j = 0; j < size_y; ++j) {
            if (DFS_EX(i, j)) {
                result += 1;
            }
        }
    }

    cout << result << endl;
}


int graph_bfs[size_x][size_y] = {
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1
};
int dx[] = { -1, 1, 0, 0 }; // up, down
int dy[] = { 0, 0, -1, 1 }; // left, right

void BFS_EX(int x, int y)
{
    queue<pair<int, int>> q;
    q.push({ x, y });
    graph_bfs[x][y] += 1;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        cout << x << ", " << y << endl;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= size_x || ny < 0 || ny >= size_y)
                continue;

            if (graph_bfs[nx][ny] == 0)
                continue;

            if (graph_bfs[nx][ny] != 1)
                continue;

            q.push({ nx, ny });
            graph_bfs[nx][ny] = graph_bfs[x][y] + 1;
        }
    }
}

void TestBfs_Ex()
{
    BFS_EX(0, 0);

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y)
            cout << graph_bfs[x][y] << ' ';
        cout << endl;
    }
}


// lowest common ancestor
const int MAX_NODE = 31;
const int MAX_EXPONENT = 11;

vector<int> graph_lca[MAX_NODE];
set<int> nodes_lca;

// 2^0, 2^1, 2^2 ~ 2^(MAX_EXPONENT-1) => 1, 2, 4, 8 ~
// node's 1, 2, 4, 8 ~ upper depth parent
int parent_lca[MAX_NODE][MAX_EXPONENT] = { 0, };
int depth_lca[MAX_NODE] = { 0, };
bool visited_lca[MAX_NODE] = { false, };

void InitData_LCA()
{
    vector<pair<int, int>> edges = {
        { 0, 1 }, { 0, 2 }, { 1, 3 }, { 1, 4 },
        { 2, 5 }, { 2, 6 }, { 3, 7 }, { 3, 8 },
        { 4, 9 }, { 4, 10 }, { 4, 11 }, { 8, 12 },
        { 8, 13 }, { 9, 14 }, { 10, 15 }, { 13, 16 },
        { 13, 17 }, { 14, 18 }, { 15, 19 }, { 17, 20 }
    };

    for (auto [fir, sec] : edges) {
        //cout << fir << ", " << sec << endl;
        graph_lca[fir].push_back(sec);
        graph_lca[sec].push_back(fir);
        nodes_lca.insert(fir);
        nodes_lca.insert(sec);
    }

    fill(&parent_lca[0][0], &parent_lca[0][0] + MAX_NODE * MAX_EXPONENT, -1);
    fill(depth_lca, depth_lca + MAX_NODE, -1);
}

void DFS_LCA(int node, int dep)
{
    visited_lca[node] = true;
    depth_lca[node] = dep;

    for (int next : graph_lca[node]) {
        if (visited_lca[next])
            continue;

        parent_lca[next][0] = node;
        DFS_LCA(next, dep + 1);
    }
}

void SetParent_LCA()
{
    DFS_LCA(0, 0);

    for (int exp = 1; exp < MAX_EXPONENT; ++exp) {
        for (int node = 0; node < nodes_lca.size(); ++node) {
            int close_parent = parent_lca[node][exp - 1];
            parent_lca[node][exp] = parent_lca[close_parent][exp - 1];
        }
    }
}

int LCA(int a, int b)
{
    if (depth_lca[a] > depth_lca[b])
        swap(a, b);

    for (int exp = MAX_EXPONENT - 1; exp >= 0; --exp) {
        if (depth_lca[b] - depth_lca[a] >= (1 << exp))
            b = parent_lca[b][exp];
    }

    if (a == b)
        return a;

    for (int exp = MAX_EXPONENT - 1; exp >= 0; --exp) {
        if (parent_lca[a][exp] == parent_lca[b][exp])
            continue;

        a = parent_lca[a][exp];
        b = parent_lca[b][exp];
    }

    return parent_lca[a][0];
}

void TestLca()
{
    InitData_LCA();
    SetParent_LCA();

    cout << "5, 7 LCA: " << LCA(5, 7) << endl;
    cout << "15, 20 LCA: " << LCA(15, 20) << endl;
    cout << "16, 17 LCA: " << LCA(16, 17) << endl;
    cout << "10, 9 LCA: " << LCA(10, 9) << endl;
    cout << "20, 8 LCA: " << LCA(20, 8) << endl;
}


int main()
{
    TestStack();
    TestQueue();
    TestFactorial();
    TestAdjacencyMatrix();
    TestAdjacencyList();
    TestDfsBfs();
    TestDfs_Ex();
    TestBfs_Ex();
    TestLca();

    return 0;
}

