#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>


// tested x64, c++17

using namespace std;

constexpr int INF = static_cast<int>(1e9);
constexpr int MAX_NODE_CNT = 7;

// except 0 node, start node 1 ~
vector<pair<int, int>> graph[MAX_NODE_CNT]; // pair<next_node, cost>, line info
array<int, MAX_NODE_CNT> shortest = { 0, };
array<bool, MAX_NODE_CNT> visited = { false, };

void InitData()
{
    /*int graph[MAX_NODE_CNT][MAX_NODE_CNT] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 5, 1, INF, INF},
        {0, 2, 0, 3, 2, INF, INF},
        {0, 5, 3, 0, 3, 1, 5},
        {0, 1, 2, 3, 0, 1, INF},
        {0, INF, INF, 1, 1, 0, 2},
        {0, INF, INF, 5, INF, 2, 0}
    };*/

    graph[1].push_back(make_pair(2, 2));
    graph[1].push_back(make_pair(3, 5));
    graph[1].push_back(make_pair(4, 1));

    graph[2].push_back(make_pair(1, 2));
    graph[2].push_back(make_pair(3, 3));
    graph[2].push_back(make_pair(4, 2));

    graph[3].push_back(make_pair(1, 5));
    graph[3].push_back(make_pair(2, 3));
    graph[3].push_back(make_pair(4, 3));
    graph[3].push_back(make_pair(5, 1));
    graph[3].push_back(make_pair(6, 5));

    graph[4].push_back(make_pair(1, 1));
    graph[4].push_back(make_pair(2, 2));
    graph[4].push_back(make_pair(3, 3));
    graph[4].push_back(make_pair(5, 1));

    graph[5].push_back(make_pair(3, 1));
    graph[5].push_back(make_pair(4, 1));
    graph[5].push_back(make_pair(6, 2));

    graph[6].push_back(make_pair(3, 5));
    graph[6].push_back(make_pair(5, 2));

    shortest.fill(INF);
    visited.fill(false);
}

int GetSmallestNode()
{
    // not visited, shortest cost
    int min_value = INF;
    int index = 0;
    for (int i = 1; i < MAX_NODE_CNT; ++i) {
        if (visited[i])
            continue;

        if (shortest[i] >= min_value)
            continue;

        min_value = shortest[i];
        index = i;
    }
    return index;
}

void Dijkstra1(int start)
{
    shortest.fill(INF);
    visited.fill(false);

    shortest[start] = 0;
    visited[start] = true;

    for (auto [next_node, cost] : graph[start])
        shortest[next_node] = cost;

    int node_cnt = MAX_NODE_CNT - 2; // except 0 node, start node

    for (int i = 0; i < node_cnt; ++i) {
        int now_node = GetSmallestNode();
        visited[now_node] = true;

        for (auto [next_node, cost] : graph[now_node]) {
            int acc_cost = shortest[now_node] + cost;

            if (acc_cost < shortest[next_node])
                shortest[next_node] = acc_cost;
        }
    }

    cout << "shortest cost: ";
    for (int n : shortest)
        cout << n << ", ";
}

void Dijkstra2(int start)
{
    shortest.fill(INF);
    priority_queue<pair<int, int>> pq; // pair<cost, node>

    pq.push({ 0, start });
    shortest[start] = 0;

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int now_node = pq.top().second;
        pq.pop();

        if (shortest[now_node] < cost)
            continue;

        for (auto [next_node, next_cost] : graph[now_node]) {
            int acc_cost = cost + next_cost;

            if (acc_cost < shortest[next_node]) {
                shortest[next_node] = acc_cost;
                pq.push(make_pair(-acc_cost, next_node));
            }
        }
    }

    cout << endl << "shortest cost: ";
    for (int n : shortest)
        cout << n << ", ";
}

void TestDijkstra()
{
    InitData();

    Dijkstra1(1);

    Dijkstra2(1);
}


void TestFloydWarshall()
{
    const int NODE_CNT = 4;

    // graph[now_node][next_node]
    int graph[NODE_CNT][NODE_CNT] = {
        {0, 5, INF, 8},
        {7, 0, 9, INF},
        {2, INF, 0, 4},
        {INF, INF, 3, 0}
    };

    int result[NODE_CNT][NODE_CNT] = { 0, };
    //for (int i = 0; i < NODE_CNT; ++i) {
    //    fill(result[i], result [i] + NODE_CNT, INF);
    //    result[i][i] = 0;
    //}

    copy(&graph[0][0], &graph[0][0] + NODE_CNT * NODE_CNT, &result[0][0]);

    for (int center = 0; center < NODE_CNT; ++center) {
        for (int begin = 0; begin < NODE_CNT; ++begin) {
            for (int end = 0; end < NODE_CNT; ++end) {
                result[begin][end] = 
                    min(result[begin][end], result[begin][center] + result[center][end]);
            }
        }
    }

    cout << endl << "result floyd warshall" << endl;

    for (int i = 0; i < NODE_CNT; ++i) {
        for (int j = 0; j < NODE_CNT; ++j) {
            if (result[i][j] == INF)
                cout << "INF" << ' ';
            else
                cout << result[i][j] << ' ';
        }
        cout << endl;
    }
}


int main()
{
    TestDijkstra();
    TestFloydWarshall();

    return 0;
}

