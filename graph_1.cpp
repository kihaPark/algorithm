#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>


// tested x64, c++17

using namespace std;

// disjoint set algorithm
// int parent[100]; index = node, value = parent

int GetParent(int* parent, int x)
{
    if (x == parent[x])
        return x;

    return parent[x] = GetParent(parent, parent[x]);
}

void UnionParent(int* parent, int a, int b)
{
    a = GetParent(parent, a);
    b = GetParent(parent, b);
    if (a < b)
        parent[b] = a;
    else
        parent[a] = b;
}

int FindParent(int* parent, int a, int b)
{
    a = GetParent(parent, a);
    b = GetParent(parent, b);
    return (a == b) ? 1 : 0;
}

void TestUnionFind()
{
    const int NODE_CNT = 11;
    int parent[NODE_CNT] = { 0, };
    for (int i = 1; i < NODE_CNT; ++i)
        parent[i] = i;

    UnionParent(parent, 1, 2);
    UnionParent(parent, 2, 3);
    UnionParent(parent, 3, 4);
    UnionParent(parent, 5, 6);
    UnionParent(parent, 6, 7);
    UnionParent(parent, 7, 8);

    for (int i = 1; i < NODE_CNT; ++i)
        cout << "(" << i << ", " << parent[i] << ") ";

    cout << endl << "1과 5는 연결되어 있나? "
        << (FindParent(parent, 1, 5) ? "yes" : "no") << endl;

    UnionParent(parent, 1, 5);

    for (int i = 1; i < NODE_CNT; ++i)
        cout << "(" << i << ", " << parent[i] << ") ";

    cout << endl << "1과 5는 연결되어 있나? "
        << (FindParent(parent, 1, 5) ? "yes" : "no") << endl;
}


void TestCycle()
{
    const int NODE_CNT = 11;
    int parent[NODE_CNT] = { 0, };
    for (int i = 1; i < NODE_CNT; ++i)
        parent[i] = i;

    bool cycle = false;
    UnionParent(parent, 2, 3);

    for (int i = 1; i < NODE_CNT - 1; ++i) {
        if (FindParent(parent, i, i + 1)) {
            cycle = true;
            break;
        }
        else {
            UnionParent(parent, i, i + 1);
        }
    }

    cout << (cycle ? "사이클 발생" : "사이클 없음") << endl;

    for (int i = 1; i < NODE_CNT; ++i)
        cout << "(" << i << ", " << parent[i] << ") ";
}


// kruskal algorithm, lowest cost spanning tree
void TestKruskal()
{
    const int NODE_CNT = 8;
    int parent[NODE_CNT] = { 0, };
    for (int i = 1; i < NODE_CNT; ++i)
        parent[i] = i;

    // tuple<cost, now_node, next_node>
    vector<tuple<int, int, int>> edges;
    edges.push_back(make_tuple(12, 1, 7));
    edges.push_back(make_tuple(28, 1, 4));
    edges.push_back(make_tuple(67, 1, 2));
    edges.push_back(make_tuple(17, 1, 5));
    edges.push_back(make_tuple(24, 2, 4));
    edges.push_back(make_tuple(62, 2, 5));
    edges.push_back(make_tuple(20, 3, 5));
    edges.push_back(make_tuple(37, 3, 6));
    edges.push_back(make_tuple(13, 4, 7));
    edges.push_back(make_tuple(45, 5, 6));
    edges.push_back(make_tuple(73, 5, 7));

    sort(edges.begin(), edges.end());

    for (auto [cost, now_node, next_node] : edges)
        cout << cost << ", " << now_node << ", " << next_node << endl;

    int total_cost = 0;
    for (auto [cost, now_node, next_node] : edges) {
        if (FindParent(parent, now_node, next_node)) // except cycle
            continue;

        UnionParent(parent, now_node, next_node);
        total_cost += cost;
    }

    cout << "total cost: " << total_cost << endl;

    for (int i = 1; i < NODE_CNT; ++i)
        cout << "(" << i << ", " << parent[i] << ") ";
}


void TestTopologySort()
{
    const int NODE_CNT = 8;
    vector<int> graph[NODE_CNT];
    array <int, NODE_CNT> indegree = { 0, };

    graph[1].push_back(2); // node 1 -> node 2
    indegree[2] += 1;
    graph[1].push_back(5);
    indegree[5] += 1;
    graph[2].push_back(3);
    indegree[3] += 1;
    graph[3].push_back(4);
    indegree[4] += 1;
    graph[4].push_back(6);
    indegree[6] += 1;
    graph[5].push_back(6);
    indegree[6] += 1;
    graph[6].push_back(7);
    indegree[7] += 1;

    queue<int> q;
    vector<int> result;

    for (int i = 1; i < NODE_CNT; ++i) {
        if (indegree[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        int now_node = q.front();
        q.pop();
        result.push_back(now_node);

        for (int next_node : graph[now_node]) {
            indegree[next_node] -= 1;

            if (indegree[next_node] == 0)
                q.push(next_node);
        }
    }

    cout << endl << "topology sort result: ";
    for (int node : result)
        cout << node << ' ';
    cout << endl;
}


void QuizCityDivisionPlan()
{
    // kruskal algorithm, lowest cost spanning tree
    const int NODE_CNT = 8;
    int parent[NODE_CNT] = { 0, };
    for (int i = 1; i < NODE_CNT; ++i)
        parent[i] = i;

    // tuple<cost, now_node, next_node>
    vector<tuple<int, int, int>> edges;
    edges.push_back(make_tuple(12, 1, 7));
    edges.push_back(make_tuple(28, 1, 4));
    edges.push_back(make_tuple(67, 1, 2));
    edges.push_back(make_tuple(17, 1, 5));
    edges.push_back(make_tuple(24, 2, 4));
    edges.push_back(make_tuple(62, 2, 5));
    edges.push_back(make_tuple(20, 3, 5));
    edges.push_back(make_tuple(37, 3, 6));
    edges.push_back(make_tuple(13, 4, 7));
    edges.push_back(make_tuple(45, 5, 6));
    edges.push_back(make_tuple(73, 5, 7));

    sort(edges.begin(), edges.end());

    for (auto [cost, now_node, next_node] : edges)
        cout << cost << ", " << now_node << ", " << next_node << endl;

    int total_cost = 0;
    int last_cost = 0;
    for (auto [cost, now_node, next_node] : edges) {
        if (FindParent(parent, now_node, next_node)) // except cycle
            continue;

        UnionParent(parent, now_node, next_node);
        total_cost += cost;
        last_cost = cost;
    }

    cout << "total cost: " << total_cost
        << ", last cost: " << last_cost << endl;

    for (int i = 1; i < NODE_CNT; ++i)
        cout << "(" << i << ", " << parent[i] << ") ";
}


void QuizCurriculumPlan()
{
    // topology sort
    const int NODE_CNT = 8;
    vector<int> graph[NODE_CNT];
    array <int, NODE_CNT> indegree = { 0, };

    graph[1].push_back(2); // node 1 -> node 2
    indegree[2] += 1;
    graph[1].push_back(5);
    indegree[5] += 1;
    graph[2].push_back(3);
    indegree[3] += 1;
    graph[3].push_back(4);
    indegree[4] += 1;
    graph[4].push_back(6);
    indegree[6] += 1;
    graph[5].push_back(6);
    indegree[6] += 1;
    graph[6].push_back(7);
    indegree[7] += 1;

    queue<int> q;
    vector<int> result;

    for (int i = 1; i < NODE_CNT; ++i) {
        if (indegree[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        int now_node = q.front();
        q.pop();
        result.push_back(now_node);

        for (int next_node : graph[now_node]) {
            indegree[next_node] -= 1;

            if (indegree[next_node] == 0)
                q.push(next_node);
        }
    }

    cout << endl << "quiz curriculum: ";
    for (int node : result)
        cout << node << ' ';
}


int main()
{
    TestUnionFind();
    TestCycle();
    TestKruskal();
    TestTopologySort();
    QuizCityDivisionPlan();
    QuizCurriculumPlan();

    return 0;
}

