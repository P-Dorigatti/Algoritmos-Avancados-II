#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calcular_distancia_hamming(string str1, string str2){
    string maior_igual_string;
    string menor_igual_string;

    int diferenca_tamanho = str1.length() - str2.length();
    if(diferenca_tamanho < 0){
        menor_igual_string = str1;
        maior_igual_string = str2;
    }
    else{
        menor_igual_string = str2;
        maior_igual_string = str1;
    }

    diferenca_tamanho = abs(diferenca_tamanho);
    int menor_distancia = -1;

    for(int i = 0; i < diferenca_tamanho + 1; i++){
        int distancia = 0;
        for(int j = 0; j < menor_igual_string.length(); j++){
            if(maior_igual_string[i+j] != menor_igual_string[j]){
                distancia += 1;
            }
        }
        if(menor_distancia > distancia || menor_distancia == -1){
            menor_distancia = distancia;
        }
    }

    //cout << menor_distancia << endl;
    
    return menor_distancia;
    
}

string ler_string(){
    string linha;
    cin >> linha;
    return linha;
}


int main(){
    int M, Q;
    cin >> M;
    cin >> Q;

    vector<string> banco_de_dados;
    vector<string> clipes;
    for(int i = 0; i < M; i++){
        string linha = ler_string();
        banco_de_dados.push_back(linha);
    }

    for(int i = 0; i < Q; i++){
        string linha = ler_string();
        clipes.push_back(linha);
    }

    for(int i = 0; i < Q; i++){
        int distancia_minima = -1;
        int index_distancia_minima = -1;
        for(int j = 0; j < M; j++){
            if(banco_de_dados[j].length() < clipes[i].length()) continue;

            int distancia = calcular_distancia_hamming(clipes[i], banco_de_dados[j]);
            if(distancia_minima > distancia || distancia_minima == -1){
                distancia_minima = distancia;
                index_distancia_minima = j;
                if(distancia_minima == 0) break;
            }
        }
        cout << index_distancia_minima << endl;


    }
}