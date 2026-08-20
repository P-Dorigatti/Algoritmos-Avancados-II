#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

// Representa os 4 estados lógicos possíveis para um habitante considerando a variável "tempo" para humanas
enum State { D = 0, M = 1, HD = 2, HN = 3 };

// Verifica se o estado implica em dizer a verdade
bool is_truthful(int s) {
    return s == D || s == HD;
}

// Verifica se um estado corresponde à "role" (espécie) afirmada
bool match_role(int s, const string& role) {
    if (role == "divina") return s == D;
    if (role == "maligna") return s == M;
    if (role == "humana") return s == HD || s == HN;
    if (role == "mentirosa") return !is_truthful(s);
    return false;
}

// Retorna o nome base da espécie para exibição
string get_role_name(int s) {
    if (s == D) return "divina";
    if (s == M) return "maligna";
    return "humana";
}

// Estrutura para armazenar uma configuração de mundo que passou em todas as regras
struct World {
    vector<int> states;
    int time; // 1 para Dia, 2 para Noite
};

void solve() {
    int n;
    int conv_num = 1;
    while (cin >> n && n != 0) {
        string dummy;
        getline(cin, dummy); // Consume newline

        map<string, int> name_to_id;
        vector<string> id_to_name;
        vector<string> statements(n);

        // --- PASSO 1: Coletar todos os nomes para definir o número de pessoas ---
        for (int i = 0; i < n; i++) {
            getline(cin, statements[i]);
            size_t pos = statements[i].find(':');
            string speaker = statements[i].substr(0, pos);
            if (name_to_id.find(speaker) == name_to_id.end()) {
                name_to_id[speaker] = id_to_name.size();
                id_to_name.push_back(speaker);
            }
            string statement = statements[i].substr(pos + 2);
            if (!statement.empty() && statement.back() == '.') statement.pop_back();
            
            stringstream ss(statement);
            string token0;
            ss >> token0;
            // Se não for "Eu" e nem "É", então é o nome da pessoa alvo (Target)
            if (token0 != "Eu" && token0 != "É" && token0 != "Ã‰") { // Ã‰ é 'É' em UTF-8
                if (name_to_id.find(token0) == name_to_id.end()) {
                    name_to_id[token0] = id_to_name.size();
                    id_to_name.push_back(token0);
                }
            }
        }

        int num_people = id_to_name.size();
        
        // Estrutura (EU): o que a pessoa falando de si mesma permite [D, M, HD, HN]
        vector<vector<bool>> self_possibilities(num_people, vector<bool>(4, true));
        
        // Estrutura (TEMPO): restrições de tempo cruzadas com a espécie (1=Dia, 2=Noite, 3=Ambos, 0=Inválido)
        vector<vector<int>> time_possibilities(num_people, vector<int>(4, 3));
        for(int p = 0; p < num_people; p++) {
            time_possibilities[p][HD] = 1; // Humana/Dia obriga ser Dia
            time_possibilities[p][HN] = 2; // Humana/Noite obriga ser Noite
        }

        // Estrutura (RELAÇÕES): Matriz 4D que indica se Speaker no estado S1 pode dizer aquilo do Target no estado S2
        vector<vector<vector<vector<bool>>>> relation(num_people,
            vector<vector<vector<bool>>>(num_people,
            vector<vector<bool>>(4, vector<bool>(4, true))));

        // --- PASSO 2: Fazer o parsing da lógica para preencher as matrizes ---
        for (int i = 0; i < n; i++) {
            string line = statements[i];
            size_t pos = line.find(':');
            int speaker = name_to_id[line.substr(0, pos)];
            string statement = line.substr(pos + 2);
            if (!statement.empty() && statement.back() == '.') statement.pop_back();

            stringstream ss(statement);
            vector<string> tokens;
            string token;
            while (ss >> token) tokens.push_back(token);

            if (tokens[0] == "Eu") {
                bool is_neg = (tokens[1] == "não");
                string role;
                if (!is_neg) {
                    if (tokens.size() > 2 && tokens[1] == "estou" && tokens[2] == "mentindo") role = "mentirosa";
                    else role = tokens[2];
                } else {
                    if (tokens.size() > 3 && tokens[2] == "estou" && tokens[3] == "mentindo") role = "mentirosa";
                    else role = tokens[3];
                }
                
                for (int s1 = 0; s1 < 4; s1++) {
                    bool truth = match_role(s1, role);
                    if (is_neg) truth = !truth;
                    // Se a veracidade do estado atual entra em contradição com a frase, corta a possibilidade
                    if (is_truthful(s1) != truth) {
                        self_possibilities[speaker][s1] = false;
                    }
                }
            } else if (tokens[0] == "É" || tokens[0] == "Ã‰") { 
                int implied_time = (tokens[1] == "dia") ? 1 : 2;
                for (int s1 = 0; s1 < 4; s1++) {
                    int actual_time = is_truthful(s1) ? implied_time : (3 - implied_time);
                    time_possibilities[speaker][s1] &= actual_time; // Aplica máscara bitwise
                }
            } else {
                int target = name_to_id[tokens[0]];
                bool is_neg = (tokens[1] == "não");
                string role = is_neg ? tokens[3] : tokens[2];

                for (int s1 = 0; s1 < 4; s1++) {
                    for (int s2 = 0; s2 < 4; s2++) {
                        bool truth = match_role(s2, role);
                        if (is_neg) truth = !truth;
                        // Se a veracidade do interlocutor conflita com o fato analisado sobre o alvo
                        if (is_truthful(s1) != truth) {
                            relation[speaker][target][s1][s2] = false;
                        }
                    }
                }
            }
        }

        // --- PASSO 3: Trazer as restrições de Tempo e Autorreferência de volta para `self` ---
        for (int p = 0; p < num_people; p++) {
            for (int s = 0; s < 4; s++) {
                if (time_possibilities[p][s] == 0 || !relation[p][p][s][s]) {
                    self_possibilities[p][s] = false;
                }
            }
        }

        // --- PASSO 4: Percorrer a estrutura para checar intersecção de todas as condições simultaneamente (Backtracking) ---
        vector<World> valid_worlds;
        vector<int> current_state(num_people, 0);

        auto backtrack = [&](auto& self_fn, int p_idx, int global_time) -> void {
            if (global_time == 0) return; // Se a intersecção de tempo der incompatível, morre
            if (p_idx == num_people) { // Chegou ao fim = combinação perfeita!
                if (global_time & 1) valid_worlds.push_back({current_state, 1}); // 1 = Dia
                if (global_time & 2) valid_worlds.push_back({current_state, 2}); // 2 = Noite
                return;
            }

            for (int s = 0; s < 4; s++) {
                // Checa compatibilidade da pessoa atual
                if (!self_possibilities[p_idx][s]) continue;
                
                int next_time = global_time & time_possibilities[p_idx][s];
                if (next_time == 0) continue;

                // Checa com os vizinhos já alocados (Bidirecional: O que eu falei deles e o que eles falaram de mim)
                bool ok = true;
                for (int prev_idx = 0; prev_idx < p_idx; prev_idx++) {
                    int prev_s = current_state[prev_idx];
                    if (!relation[p_idx][prev_idx][s][prev_s] || !relation[prev_idx][p_idx][prev_s][s]) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    current_state[p_idx] = s;
                    self_fn(self_fn, p_idx + 1, next_time);
                }
            }
        };

        // Inicia com global_time = 3 (Pode ser dia ou noite antes de ler as sentenças)
        backtrack(backtrack, 0, 3);

        // --- PASSO 5: Extração e Exibição de Fatos Deduzíveis ---
        cout << "Conversa #" << conv_num++ << endl;
        if (valid_worlds.empty()) {
            cout << "Nenhum fato pode ser deduzido." << endl;
            cout << endl;
            continue;
        }

        vector<string> deduced_roles(num_people, "");
        for (int p = 0; p < num_people; p++) {
            string common_role = get_role_name(valid_worlds[0].states[p]);
            bool always_same = true;
            for (size_t w = 1; w < valid_worlds.size(); w++) {
                if (get_role_name(valid_worlds[w].states[p]) != common_role) {
                    always_same = false;
                    break;
                }
            }
            if (always_same) deduced_roles[p] = common_role;
        }

        int common_time = valid_worlds[0].time;
        bool always_same_time = true;
        for (size_t w = 1; w < valid_worlds.size(); w++) {
            if (valid_worlds[w].time != common_time) {
                always_same_time = false;
                break;
            }
        }

        vector<string> facts;
        for (int p = 0; p < num_people; p++) {
            if (deduced_roles[p] != "") {
                facts.push_back(id_to_name[p] + " é " + deduced_roles[p] + ".");
            }
        }
        
        // Ordena nomes alfabeticamente
        sort(facts.begin(), facts.end());
        
        // Adiciona a dedução do tempo no final, conforme a regra
        if (always_same_time) {
            if (common_time == 1) facts.push_back("É dia.");
            else facts.push_back("É noite.");
        }

        if (facts.empty()) {
            cout << "Nenhum fato pode ser deduzido." << endl;
        } else {
            for (const string& fact : facts) {
                cout << fact << endl;
            }
        }
        cout << endl;
    }
}

int main() {
    // Otimização de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}