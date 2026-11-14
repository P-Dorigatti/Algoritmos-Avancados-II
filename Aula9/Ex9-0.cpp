#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, p, q;
    if (!(cin >> n >> p >> q)) return;

    vector<int> pos_sheik(n * n + 1, -1);

    for (int i = 0; i <= p; i++) {
        int cell;
        cin >> cell;
        pos_sheik[cell] = i;
    }

    vector<int> tails;
    tails.reserve(q + 1);

    for (int j = 0; j <= q; j++) {
        int cell;
        cin >> cell;
        int idx = pos_sheik[cell];

        if (idx != -1) {
            auto it = lower_bound(tails.begin(), tails.end(), idx);

            if (it == tails.end()) {
                tails.push_back(idx);
            } else {
                *it = idx;
            }
        }
    }

    cout << tails.size() << "\n";
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