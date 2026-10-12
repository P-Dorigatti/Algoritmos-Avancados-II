#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int combinacoes_string(int letra_atual, int letras_restantes, int soma_restante){
    if(letras_restantes == 0 && soma_restante == 0) return 1;

    if(letras_restantes == 0 || soma_restante < 0 || letra_atual > 26) return 0;

    int menor_soma = 0;
    for(int i = 0; i < letras_restantes; i++){
        menor_soma += letra_atual + i;
    }
    if(soma_restante < menor_soma) return 0;

    int maior_soma = 0;
    for(int i = 0; i < letras_restantes; i++){
        maior_soma += 26 - i;
    }
    if(maior_soma < soma_restante) return 0;


    int combinacoes = 0;

    combinacoes += combinacoes_string(letra_atual + 1, letras_restantes - 1, soma_restante - letra_atual);

    combinacoes += combinacoes_string(letra_atual + 1, letras_restantes, soma_restante);

    return combinacoes;
}

void solve(){
    int L, S;
    cin >> L >> S;

    int res = combinacoes_string(1, L, S);
    cout << res << endl;
}

int main(){
    int t;
    if(cin >> t){
        while(t--){
            solve();
        }
    }

    return 0;
}