#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

void solve(int caso){
    int n;
    if(!(cin >> n)) return;

    vector<string> nome_bebida(n);
    unordered_map<string, int> id_bebida;

    for (int i = 0; i < n; i++) {
        cin >> nome_bebida[i];
        id_bebida[nome_bebida[i]] = i;
    }

    int m;
    cin >> m;

    vector<vector<int>> adj(n);
    vector<int> in_degree(n, 0);

    for (int i = 0; i < m; i++) {
        string b1, b2;
        cin >> b1 >> b2;
        int u = id_bebida[b1];
        int v = id_bebida[b2];

        adj[u].push_back(v);
        in_degree[v]++; 
    }

    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> ordem_final;
    while (!pq.empty()) {
        int atual = pq.top();
        pq.pop();

        ordem_final.push_back(atual);

        for (int vizinho : adj[atual]) {
            in_degree[vizinho]--;
            if (in_degree[vizinho] == 0) {
                pq.push(vizinho);
            }
        }
    }

    cout << "Caso #" << caso << ": Heiter deve beber as bebidas nesta ordem:";
    for (int id : ordem_final) {
        cout << " " << nome_bebida[id];
    }
    cout << ".\n";
}


int main(){
    int t;
    if(cin >> t){
        for (int c = 1; c <= t; ++c) {
            solve(c);
        }
    }

    return 0;
}