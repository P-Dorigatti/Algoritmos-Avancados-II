#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

const long long INF = 1e18;
const long long MAX_W = 1000000000LL;

struct Edge {
    int u, v;
    long long w;
};

int n, m, s, t;
long long L;
vector<Edge> edges;
vector<int> erased_idx;
vector<vector<pair<int,int>>> adj;

void apply_weights(long long X){
    long long k = erased_idx.size();
    if(k == 0) return;

    long long base = X / k;
    long long rem = X % k;

    for(int i = 0; i < k; i++){
        edges[erased_idx[i]].w = 1 + base + (i < rem ? 1 : 0);
    }
}

long long dijkstra(){
    vector<long long> dist(n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();

        if(d > dist[u]) continue;
        if(u == t) return d;

        for(auto [v, idx] : adj[u]){
            long long w = edges[idx].w;
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[t];
}

int main(){
    if(!(cin >> n >> m >> L >> s >> t)) return 0;

    edges.resize(m);
    adj.assign(n, vector<pair<int, int>>());

    for(int i = 0; i < m; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        adj[edges[i].u].push_back({edges[i].v, i});
        adj[edges[i].v].push_back({edges[i].u, i});

        if(edges[i].w == 0){
            erased_idx.push_back(i);
        }
    }

    if(erased_idx.empty()){
        if(dijkstra() == L){
            cout << "YES\n";
            for(const auto& e : edges){
                cout << e.u << " " << e.v << " " << e.w << endl;
            }
        }
        else{
            cout << "NO\n";
        }
        return 0;
    }

    long long k = erased_idx.size();
    long long max_X = k * (MAX_W - 1);

    apply_weights(0);
    if(dijkstra() > L){
        cout << "NO\n";
        return 0;
    }

    apply_weights(max_X);
    if(dijkstra() < L){
        cout << "NO\n";
        return 0;
    }

    long long low = 0, high = max_X, ans = max_X;
    while(low <= high){
        long long mid = low + (high - low)/2;
        apply_weights(mid);

        if(dijkstra() >= L){
            ans = mid;
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }

    apply_weights(ans);
    cout << "YES\n";
    for(const auto& e : edges){
        cout << e.u << " " << e.v << " " << e.w << endl;
    }

    return 0;
}