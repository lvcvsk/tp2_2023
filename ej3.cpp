#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
const double inf = 1e18;

vector<tuple<double,int,int>> E;
vector<tuple<int,int>> oficinas;

int n,r,u,v,w;

double utp; double fibra;

struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padres(){
        return padre;
    }

    vector<int> padre;
    vector<int> rank;
};

double distancia(tuple<int,int> p1, tuple<int,int> p2){
    int deltaX = abs( get<0>(p1) - get<0>(p2));
    int deltaY = abs(get<1>(p1) - get<1>(p2));
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}

vector<int> kruskal_corto(){
    sort(E.begin(),E.end());
    //double res = 0;
    int aristas = 0;
    DSU dsu(n);
    for(int i = 0; i < n - w; i++){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            dsu.unite(u,v);
            aristas++;
            //res += c;
        }
    }
    //if(aristas == n-1) cout<<res<<endl;
    //else cout<<"IMPOSSIBLE\n";
    return dsu.padres();
}

vector<vector<int>> conseguir_conexas (vector<int> v){
    vector<vector<int>> comp(n, vector<int>());

    for (int i = 0; i < v.size(); i++){
        comp[v[i]].push_back(i);
    }

    vector<vector<int>> res;

    for(vector<int> u : comp){
        if (u.size() != 0){
            res.push_back(u);
        }
    }
    return res;
}

int main(){
    int c;
    cin >> c;
    int q = 1;
    while (q <= c){
        q++;
        cin >> n >> r >> w >> u >> v;
        for (int i = n; i < n; i++){
            int x,y;
            cin >> x >> y;
            oficinas.push_back(make_tuple(x,y));
        }
        for(int i = 0; i < n; i++){
            for(int j = 1; j < n - 1; j++){
                double dist = distancia(oficinas[i],oficinas[j]);
                tuple<double,int,int> temp = make_tuple(dist,i,j);
                E.push_back(temp);
            }
        }
        utp = 0.0; fibra = 0.0;

        vector<int> padrastros = kruskal_corto();
        vector<vector<int>> comp_conexas = conseguir_conexas(padrastros);

        for(int i = 0; i < comp_conexas.size(); i++){
            for (int j = 0; i < comp_conexas[i].size(); j++){
                cout << comp_conexas[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Caso #" << q << ": " << utp << " " << fibra << endl;
    }
}