#include <iostream>
#include <queue>

using namespace std;

struct Grupo {
    int musicos, partituras;
    
    // Sobrescrever o operador < para a fila saber quem colocar no topo
    bool operator<(const Grupo& outro) const {
        return (double)musicos / partituras < (double)outro.musicos / outro.partituras;
    }
};

int main(){
    int t;
    if (!(cin >> t)) return 0;
    
    while(t--){
        int p, n;
        cin >> p >> n;
        
        priority_queue<Grupo> pq;
        
        for(int i = 0; i < n; i++){
            int nro_musico;
            cin >> nro_musico;
            pq.push({nro_musico, 1});
        }
        
        p -= n;
        
        while(p > 0){
            Grupo mais_lotado = pq.top();
            pq.pop();                    
            
            mais_lotado.partituras++;     
            
            pq.push(mais_lotado);         
            p--;
        }
        
        Grupo resposta = pq.top();
        
        cout << (resposta.musicos + resposta.partituras - 1) / resposta.partituras << endl;
    }
    return 0;
}