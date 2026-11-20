#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int MAXN = 55;
const long long INF = LLONG_MAX;

long long cap[MAXN][MAXN];

long long bfs(int s, int t, int n, vector<int>&parent){
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    queue<pair<int, long long>> q;
    q.push({s, INF});

    while(!q.empty()){
        int u = q.front().first;
        long long flow = q.front().second;
        q.pop();

        for(int v = 1; v <= n; v++){
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

long long solve(int s, int t, int n){
    long long max_flow = 0;
    vector<int> parent(n+1);
    long long new_flow;

    while((new_flow = bfs(s, t, n, parent)) > 0){
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

int main(){
    int n, m;

    while(cin >> n >> m && (n !=0 || m != 0)){
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= n; j++){
                cap[i][j] = 0;
            }
        }

        for(int i = 0; i < m; i++){
            int u, v;
            long long c;
            cin >> u >> v >> c;

            cap[u][v] += c;
            cap[v][u] += c;
        }
    
        cout << solve(1, 2, n) << endl;
    }

    return 0;
}