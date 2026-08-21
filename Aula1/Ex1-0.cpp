#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pegar_divisores_ordenada(int n){
    vector<int> divisores;
    for(int i = 1; i*i <= n; i++){
        if(n % i == 0){
            divisores.push_back(i);
            
            int par_do_i = n/i;
            if(par_do_i != i){
                divisores.push_back(par_do_i);
            }
        }
    }

    sort(divisores.begin(), divisores.end());

    return divisores;
}

bool tenta_agrupar(const vector<int>& pedacos, vector<bool>& visitado, int alvo, int soma_atual, int indice_atual, int grupos_restantes) {
    if (grupos_restantes == 0) return true;

    if (soma_atual == alvo) {
        return tenta_agrupar(pedacos, visitado, alvo, 0, 0, grupos_restantes - 1);
    }

    for (int i = indice_atual; i < pedacos.size(); i++) {
        if (visitado[i] || soma_atual + pedacos[i] > alvo) {
            continue;
        }

        visitado[i] = true;
        if (tenta_agrupar(pedacos, visitado, alvo, soma_atual + pedacos[i], i + 1, grupos_restantes)) {
            return true;
        }
        visitado[i] = false;

        if (soma_atual == 0) break;
        if (soma_atual + pedacos[i] == alvo) break;

        while (i + 1 < pedacos.size() && pedacos[i] == pedacos[i + 1]) {
            i++;
        }
    }

    return false;
}

int combinar_pedaco(const vector<int>& pedacos) {
    int soma_pedacos = 0;
    for (int pedaco : pedacos) {
        soma_pedacos += pedaco;
    }

    vector<int> divisores = pegar_divisores_ordenada(soma_pedacos);

    int maior_pedaco = pedacos[0]; 

    auto alvo_iterador = lower_bound(divisores.begin(), divisores.end(), maior_pedaco);

    while (alvo_iterador != divisores.end()) {
        int alvo = *alvo_iterador;
        int grupos_necessarios = soma_pedacos / alvo;
        
        vector<bool> visitado(pedacos.size(), false);

        if (tenta_agrupar(pedacos, visitado, alvo, 0, 0, grupos_necessarios)) {
            return alvo;
        }

        alvo_iterador++;
    }

    return soma_pedacos; 
}

int main(){
    int n;
    while(cin >> n && n != 0){
        vector<int> pedacos;
        for(int i = 0; i<n; i++){
            int valor;
            cin >> valor;
            pedacos.push_back(valor);
        }

        sort(pedacos.begin(), pedacos.end(), greater<int>());

        int menor_tamanho = combinar_pedaco(pedacos);

        cout << menor_tamanho << endl;
    }

    return 0;
}