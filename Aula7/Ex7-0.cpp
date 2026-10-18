#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int u, v, w;
};

struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
        sz.assign(n + 1, 1);                 
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    int unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (sz[root_i] < sz[root_j])
                swap(root_i, root_j);
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
        }
        return sz[root_i];
    }
};

void solve() {
    int n, m;
    if (!(cin >> n >> m) || (n == 0 && m == 0)) return;

    vector<Edge> edges(m);
    int max_lpa = INT_MIN;

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        if (edges[i].w > max_lpa) {
            max_lpa = edges[i].w;
        }
    }

    DSU dsu(n);
    int max_cities = 0;

    for (int i = 0; i < m; i++) {
        if (edges[i].w == max_lpa) {
            int current_component_size = dsu.unite(edges[i].u, edges[i].v);
            if (current_component_size > max_cities) {
                max_cities = current_component_size;
            }
        }
    }

    cout << max_cities << "\n";
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}