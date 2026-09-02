#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <cstdio>

using namespace std;

enum Events {
    DMG,
    POISON,
    HEAL,
    BLESS
};

map<string, Events> event_map = {
    {"DMG", Events::DMG},
    {"POISON", Events::POISON},
    {"HEAL", Events::HEAL},
    {"BLESS", Events::BLESS},
};

template <typename T>
T read(){
    T value;
    cin >> value;
    return value;
}

double apply_event(double pv, Events event, double value){
    switch(event){
        case(Events::DMG):
            return pv - value;
        case(Events::POISON):
            return pv * (1.0 - value);
        case(Events::HEAL):{
            double heal = pv + value;
            if (heal >= 1000.0) return 1000.0;
            else return heal;
        };
        case(Events::BLESS):{
            double bless = pv * (1.0 + value);
            if (bless >= 1000.0) return 1000.0;
            else return bless;
        };
        default:
            cout << "Unexpected Error: invalid event to revert" << endl;
            return -1;
    }
}

double treverse_dungeon(double pv, const list<pair<Events, double>>& history){
    for(auto it = history.begin(); it != history.end(); it++){
        pv = apply_event(pv, it->first, it->second);
        if(pv <= 1e-9) return pv; // Morreu
    }
    return pv;
}

Events read_event(){
    string event_name = read<string>();
    return event_map[event_name];    
}

int main(){
    int t = read<int>();

    for(int i = 0; i < t; i++){
        int num_events = read<int>();
        list<pair<Events, double>> history;
        for(int j = 0; j < num_events; j++){
            Events event = read_event();
            double value = read<double>();
            history.push_back({event, value});
        }

        long long min_pv = 1;
        long long max_pv = 1000000;
        long long melhor_pv = 1000000;

        while (min_pv <= max_pv) {
            long long mid = (min_pv + max_pv) / 2;
            double pv_teste = mid / 1000.0; 
            double final_pv = treverse_dungeon(pv_teste, history);

            if (final_pv > 1e-9) {
                melhor_pv = mid;
                max_pv = mid - 1;
            } else {
                min_pv = mid + 1;
            }
        }

        printf("%.3f\n", melhor_pv / 1000.0);
    }
    return 0;
}