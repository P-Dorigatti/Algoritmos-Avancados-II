#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

void solve() {
    int k;
    string s;
    if (!(cin >> k >> s)) return;

    int n = s.size();
    if (n == 0) {
        cout << 0 << "\n";
        return;
    }

    vector<int> dp_prev(26, INF);
    bool first_block = true;

    for (int start = 0; start < n; start += k) {
        int end = min(n, start + k);

        bool present[26] = {false};
        int distinct_count = 0;
        for (int idx = start; idx < end; idx++) {
            int ch = s[idx] - 'a';
            if (!present[ch]) {
                present[ch] = true;
                distinct_count++;
            }
        }

        vector<int> dp_curr(26, INF);

        if (first_block) {
            for (int last = 0; last < 26; last++) {
                if (present[last]) {
                    dp_curr[last] = distinct_count;
                }
            }
            first_block = false;
        } else {
            int min_prev = *min_element(dp_prev.begin(), dp_prev.end());

            for (int last = 0; last < 26; last++) {
                if (!present[last]) continue;

                for (int first = 0; first < 26; first++) {
                    if (!present[first]) continue;

                    if (distinct_count > 1 && first == last) continue;

                    int best_before = min(min_prev, dp_prev[first] - 1);
                    dp_curr[last] = min(dp_curr[last], best_before + distinct_count);
                }
            }
        }

        dp_prev = dp_curr;
    }

    int ans = *min_element(dp_prev.begin(), dp_prev.end());
    cout << ans << "\n";
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