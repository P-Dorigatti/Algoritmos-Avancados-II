#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

class Robot {
public:
    int x = 0;
    vector<int> v;
    void move_to(string direction, int nro=0){
        int acao = -1;
        if (direction == "ESQUERDA"){
            acao = 0;
        }
        else if (direction == "DIREITA"){
            acao = 1;
        }
        else if(direction == "REPETE"){
            acao = v[nro];
        }

        if(acao == 0){
            x--;
            v.push_back(0);
        }
        else if(acao == 1){
            x++;
            v.push_back(1);
        }

    };

};

int main(){
    int n;
    int m;
    string linha;
    cin >> n;
    for(int i = 0; i<n; i++){
        cin >> m;
        Robot r;
        for(int j = 0; j<m; j++){
            cin >> ws;
            getline(cin, linha);
            stringstream ss(linha);

            string ordem;
            int nro = -1;

            ss >> ordem;
            if(!(ss >> nro)){
                nro = -1;
            }

            r.move_to(ordem, nro);
        }
        printf("%d\n", r.x);
    }
}