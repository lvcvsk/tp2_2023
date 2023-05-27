#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <cmath>

using namespace std;

int n,r,w,u,v;
vector<tuple<double,int,int>> E;
vector<tuple<int,int>> coordenadas;
vector<tuple<double,double> > resultados;

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

    vector<int> padre;
    vector<int> rank;
};

tuple<double,double> kruskal(){
    double costo_utp= 0;
    double costo_fibra= 0;
    sort(E.begin(),E.end());
    int aristas = 0;
    DSU dsu(n);

    for(auto e : E){
        double dist = get<0>(e);
        int x = get<1>(e);
        int y = get<2>(e);
        if(w== n-aristas)
            break;
        //si (u,v) es arista segura
        if(dsu.find(x) != dsu.find(y)){
            // agregar
            dsu.unite(x,y);
            aristas++;
            if(dist<=r){
                costo_utp += dist * u;
            }
            else
                costo_fibra+=dist*v;
        }
    }
    return {costo_utp,costo_fibra};
}

//Distancia entre dos puntos
double distancia(tuple<int,int> p1, tuple<int,int> p2){
    int deltaX = get<0>(p1) - get<0>(p2);
    int deltaY = get<1>(p1) - get<1>(p2);
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}

int main() {
    int c; //casos de test
    cin>> c;
    for(int i=0; i<c ;i++){ 
        cin>>n;     //cantidad de nodos
        cin>>r; 
        cin>>w;     //cantidad de modems
        cin>>u;    //costo por metro de UTP 
        cin>>v;    //costo por metro de fibra óptica
        coordenadas.clear();
        E.clear();

        //creo mi vector de aristas y sus costos

        //implemento kruskal, guardar los valores para imprimirlos al final
        for(int i=0; i<n ;i++){
            int a,b; float dist;
            cin>>a>>b;
            coordenadas.push_back({a,b});
            for(int j=0; j<coordenadas.size()-1;j++){
                dist= distancia(coordenadas[coordenadas.size()-1], coordenadas[j]);
                E.push_back({dist,j,i});
            }
        }
        resultados.push_back(kruskal());
    }

    for(int i=0; i<resultados.size() ; i++){
        cout<<"Caso #"<<i+1<<": "<< fixed << setprecision(3)<< get<0>(resultados[i])<<" "<<get<1>(resultados[i])<<endl;
    }
    
    return 0;
}