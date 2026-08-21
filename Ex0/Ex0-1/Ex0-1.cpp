#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> find_sums(vector<int> l1, vector<int> l2, int k){
    priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

    for (int i = 0; i < k; i++) {
        pq.push({l1[i] + l2[0], 0});
    }

    vector<int> result;

    for (int i = 0; i<k; i++){
        int current_sum = pq.top().first;
        int index_l2 = pq.top().second;
        pq.pop();

        result.push_back(current_sum);

        if(index_l2 + 1 < k){
            int next_sum = current_sum - l2[index_l2] + l2[index_l2 + 1];
            pq.push({next_sum, index_l2 + 1});
        }
    }

    return result;
}

int main(){
    int k;
    while(cin >> k){
        vector<vector<int>> matrix(k, vector<int>(k, 0));
        for(int i = 0; i<k; i++){
            for(int j = 0; j<k; j++){
                cin >> matrix[i][j];
            }
            sort(matrix[i].begin(), matrix[i].end());
        }

        vector<int> solution = matrix[0];
        for(int i = 1; i < k; i++){
            solution = find_sums(solution, matrix[i], k);
        }

        for (int i = 0; i < k; i++) {
            cout << solution[i] << (i == k - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
