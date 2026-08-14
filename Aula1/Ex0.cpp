#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;


bool testa_soma(list<int> pedacos, int alvo){
    /*
    // Pedacos deve estar ordenado em ordem decrescente
    */

    while(pedacos.size() > 0){
        int dif = alvo - *pedacos.begin();
        pedacos.pop_front();
        for(auto i = pedacos.begin(); i != pedacos.end(); i++){
            if(*i <= dif){
                dif -= *i;

                pedacos.erase(i);

                if(dif == 0) break;
            }
        }

        if(dif != 0){
            return false;
        }
    }
    return true;
}

int combinar_pedaco(list<int> pedacos){
    int alvo = *pedacos.begin();
    while(!testa_soma(pedacos, alvo)){
        *pedacos.begin() += *pedacos.end();
        pedacos.pop_back();
        alvo = *pedacos.begin();
    }

    return alvo;
}

int main(){
    int n;
    cin >> n;
    while(n != 0){
        list<int> pedacos;
        for(int i = 0; i<n; i++){
            int valor;
            cin >> valor;
            pedacos.push_back(valor);
        }

        sort(pedacos.begin(), pedacos.end(), greater<int>());

        int menor_tamanho = combinar_pedaco(pedacos);

        printf("%d", menor_tamanho);
    }


    return 0;
}