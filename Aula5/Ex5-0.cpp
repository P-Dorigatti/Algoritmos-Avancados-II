#include <iostream>
#include <vector>

using namespace std; 

int main(){
    int t;
    if (!(cin >> t)) return 0;
    
    for(int i = 0; i < t; i++){
        int p, n;
        cin >> p >> n;
        vector<pair<int, int>> musicians;
        
        for(int j = 0; j < n; j++){
            int nro_musico;
            cin >> nro_musico;
            musicians.push_back({nro_musico, 1});
        }
        p = p - n;

        while(p > 0){
            int index = 0;
            for(int k = 1; k < n; k++){
                if((double)musicians[index].first / musicians[index].second < 
                   (double)musicians[k].first / musicians[k].second) {
                    index = k;
                }
            }
            musicians[index].second += 1;
            p--;
        }

        int index = 0;
        for(int k = 1; k < n; k++){
            if((double)musicians[index].first / musicians[index].second < 
               (double)musicians[k].first / musicians[k].second){
                index = k;
            }
        }
        
        int m = musicians[index].first;
        int s = musicians[index].second;
        cout << (m + s - 1) / s << endl;
    }
    return 0;
}