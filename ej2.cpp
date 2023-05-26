#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
int n, m, N;

vector<vector<int>> D;
vector<vector<int>> D_T;
vector<int> nodosCfc;

//vector<vector<int>> adj_scc;
//vector<int> raices;



void dfs_inicial(int v, vector<bool> &visitado, stack<int> &s){
    visitado[v] = true;

    for (int u : D[v]){
        if(!visitado[u]){
            dfs_inicial(u, visitado, s);
        }
    }
    s.push(v);
}

void dfs_t(int v, vector<bool> &visitado, vector<int> &componente, int &min){
    visitado[v] = true;
    componente.push_back(v);

    if (v < min){min = v;}

    for (int u : D_T[v]){
        if(!visitado[u]){
            dfs_t(u, visitado, componente, min);
        }
    }
}

/*
void dfs_ts(int v, vector<bool> &visitado, stack<int> &s){
    visitado[v] = true;

    for (int u : D[v]){
        if(!visitado[u]){
            dfs_ts(u, visitado, s);
        }
    }
    s.push(v);
}*/

vector<int> topologicalSort(vector<bool> &visitado, vector<int> &nodos){
    stack<int> s;
    vector<int> resultado;
    for (int u  : nodos){
        if (!visitado[u]){
            dfs_inicial(u, visitado, s);
            resultado.push_back(s.top());
        }
    }
    return resultado;
}

void kosaraju(){
    vector<bool> visitado(N, false);
    stack<int> s;

    //raices.resize(N, 0);

    for(int i = 1; i < N; i++){
        if(!visitado[i]){
            dfs_inicial(i, visitado, s);
        }
    }

    visitado.assign(N, false);
    vector<int> componente;

    while(!s.empty()){
        int x = s.top(); s.pop();
        if(!visitado[x]){
            int minimo = x;
            dfs_t(x, visitado, componente, minimo);

            int raiz = minimo;
            //for (int u : componente) raices[u] = raiz;
            nodosCfc.push_back(raiz);
            componente.clear();
        }
    }
    /*
    for (int u = 1; u < N; u++){
        for (int v : D[u]){
            int raiz_u = raices[u];
            int raiz_v = raices[v];

            if (raiz_u != raiz_v){
                if (find(adj_scc[raiz_u].begin(), adj_scc[raiz_u].end(), raiz_v) == adj_scc[raiz_u].end()) {
                    adj_scc[raiz_u].push_back(raiz_v);
                    }
            }
        }
    } */
}

void print(vector<vector<int>> &D){
    for (int i = 1; i < N; i++) {
        cout << "Adjacency list of vertex " << i << ": ";
        for (int j : D[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}


int main(){
    cin >> n >> m;
    N = n+1;
    D.resize(N); D_T.resize(N); 
    //adj_scc.resize(N);
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        D[u].push_back(v);
        D_T[v].push_back(u);
    }

    kosaraju();

    vector<bool> visitado(nodosCfc.size(), false);

    
    vector<int> res = topologicalSort(visitado, nodosCfc);


    //sort(res.begin(), res.end());

    cout << res.size() << endl;
    for (int i = res.size() - 1; i >= 0; i--) cout << res[i] << " ";
    cout << endl;

    return 0;
}

/*int encontrarMinimo(vector<int> &v){
    int min = v[0];
    int n = v.size();
    if (n == 1) return min;
    for (int i = 1; i < n; i++){
        if (min > v[i]){min = v[i];}
    }
    return min;
}*/
