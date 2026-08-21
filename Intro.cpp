#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

template <typename T1, typename T2>
T1 add(T1 a, T2 b){
    return a + b;
}

template <typename T>
class Pessoa {
public:
    int idade;
    int nusp;
    T doc;
    Pessoa(int i, int n) : idade(i), nusp(n) {}
   
};

class NossoFunctor {
public:    
    int i = 0;
    void operator()() {
        i++;
    }
};

class GT {
public:
    bool operator()(int a, int b) {
        return a > b;
    }
};

class MaiorQueX {
public:
    int x;
    MaiorQueX(int _x) : x(_x){}
    bool operator()(int a) {
        return a > x;
    }
};

int main(){
    int i = 0;
    cout << "Hello" << "World" << i << endl;

    // containers
    vector<int> v;
    list<int> l;
    map<string, float> m;
    m["test"] = 10;
    m["batata"] = 20;

    cout << add(2, 3.5) << endl;
    cout << add(3.5, 2) << endl;

    Pessoa<string> p(30, 12345);
    p.doc = "RG";

    NossoFunctor n;
    n(); n(); n(); n();
    cout << n.i << endl;

    vector<int> v2 = {1, 2, 3, 4, 5, 6};
    sort(v2.begin(), v2.end(), GT());

    for (auto x : v2){
        cout << x << ", ";
    }
    cout << endl;

    cout << count_if(v2.begin(), v2.end(), MaiorQueX(4)) << endl;

    for (auto x : m){
        cout << x.first << " | " << x.second << ", ";
    }

}