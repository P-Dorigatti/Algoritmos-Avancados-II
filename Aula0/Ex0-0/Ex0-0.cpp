#include <iostream>
#include <vector>
#include <sstream>

// Você tem um robô na origem do eixo x (x = 0). Este robô receberá instruções e você
// deve imprimir o resultado final das instruções. Elas serão:
// • ESQUERDA: anda uma unidade para a esquerda
// • DIREITA: anda uma unidade para a direita
// • REPETE i: repete a instrução de número i (comece contando o número de instruções a partir do 0)


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
    return 0;
}