#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int MAXV = 205;
const long long INF = 1e15;

long long cap[MAXV][MAXV];
vector<int> adj[MAXV];

void add_edge(int u, int v, long long c){
    adj[u].push_back(v);
    adj[v].push_back(u);
    cap[u][v] += c;
}

long long bfs(int s, int t, int total_nodes, vector<int>& parent){
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    queue<pair<int, long long>> q;
    q.push({s, INF});

    while(!q.empty()){
        int u = q.front().first;
        long long flow = q.front().second;
        q.pop();

        for(int v : adj[u]){
            if(parent[v] == -1 && cap[u][v] > 0){
                parent[v] = u;
                long long new_flow = min(flow, cap[u][v]);

                if(v == t){
                    return new_flow;
                }
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}

long long edmonds_karp(int s, int t, int total_nodes){
    long long max_flow = 0;
    vector<int> parent(total_nodes);
    long long new_flow;

    while((new_flow = bfs(s, t, total_nodes, parent)) > 0){
        max_flow += new_flow;

        int curr = t;
        while(curr != s){
            int prev = parent[curr];
            cap[prev][curr] -= new_flow;
            cap[curr][prev] += new_flow;
            curr = prev;
        }
    }

    return max_flow;
}

void solve(){
    int n;
    if(!(cin >> n)) return;

    int S = 0;
    int T = 2 * n + 1;
    int total_nodes = 2 * n + 2;

    for(int i = 0; i < total_nodes; i++){
        adj[i].clear();
        for(int j = 0; j < total_nodes; j++){
            cap[i][j] = 0;
        }
    }

    for(int i = 1; i <= n; i++){
        long long c;
        cin >> c;
        add_edge(i, i + n, c);
    }

    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        int u, v;
        long long c;
        cin >> u >> v >> c;
        add_edge(u + n, v, c);
    }

    int b, d;
    cin >> b >> d;

    for(int i = 0; i < b; i++){
        int u;
        cin >> u;
        add_edge(S, u, INF);
    }

    for(int i = 0; i < d; i++){
        int v;
        cin >> v;
        add_edge(v + n, T, INF);
    }

    cout << edmonds_karp(S, T, total_nodes) << endl;
}

int main(){
    int t;
    if(cin >> t){
        while(t--){
            solve();
        }
    }

    return 0;
}