#include<iostream>
#include<vector>
#include<utility>
#include<set>
#include<map>
#include <boost/math/special_functions/binomial.hpp>
#include <iomanip>
using namespace std;


//vector< pair<int,vector<int> > > G;
map<int, set<int> > G;

vector<int> niveles(G.size(), 0);
vector<int> menor_ancestro;

vector<int> tamanio_subarbol(G.size(),0);

vector<bool> visitado(G.size(), false);
vector< pair<int,int> > aristas_puente;

vector<int> tamanio_comp_conexas;

//utilizo dfs para construirme un arbol
void dfs(int v, int nivel){
    visitado[v]= true;
    tamanio_subarbol[v]+=1 ;
    niveles[v]= nivel;
    for(int w :  G[v]){
        if(!visitado[w]){
            dfs(w, nivel+1);
            if(niveles[menor_ancestro[w]]<niveles[menor_ancestro[v]])
                menor_ancestro[v]= menor_ancestro[w];
            tamanio_subarbol[v]+=tamanio_subarbol[w];
        }
        else{
            if( niveles[w]+1!=niveles[v] && niveles[w]<niveles[menor_ancestro[v]])
                menor_ancestro[v]= w ;
        }

        if(menor_ancestro[w]>niveles[v])
            aristas_puente.push_back(make_pair(v,w));
    }
}

//Funcion basada en dfs para descubrir componentes conexas y anotar en v la cantidad de nodos
void comp_conexa(int v){
    visitado[v]= true;
    tamanio_subarbol[v]+=1;
    for(int w : G[v]){
        if(!visitado[w]){
            comp_conexa(w);
            tamanio_subarbol[v]+=tamanio_subarbol[w];
        }
    }
}

int main(){
    int N; int M;
    //recibo los valores de entrada
    cin>>N; cin>>M;
   
    for(int i=0; i<N ; i++){
        set<int> vecinos;
        G[i]=vecinos;
    }

    for(int i=0; i<M ;i++){
        int a; int b;
        cin>>a; cin>>b;
        G[a-1].insert(b-1);
        G[b-1].insert(a-1);
    }


    for(int i=0; i<G.size() ;i++){
        menor_ancestro.push_back(i);
    }

    //Utilizo dfs para descrubrir las aristas puente
    niveles= vector(G.size(), 0);
    tamanio_subarbol = vector(G.size(),0);
    visitado = vector(G.size(), false);
    for(int nodo=0; nodo<G.size() ; nodo++){
        dfs(nodo,0);
    }

    //Elimino las aristas puente
    for(pair<int,int> arista: aristas_puente){
        G[arista.first].erase(arista.second);
        G[arista.second].erase(arista.first);
    }

    //Uso dfs para descubrir las componentes conexas
    visitado= visitado = vector(G.size(), false);
    tamanio_subarbol = vector(G.size(),0);

    for(int nodo; nodo<G.size() ;nodo++){
        if(!visitado[nodo]){
            comp_conexa(nodo);
            tamanio_comp_conexas.push_back(tamanio_subarbol[nodo]);
        }
    }

    //calculo las probabilidades
    int combinaciones=0;
    for(int i=0; i<tamanio_comp_conexas.size() ;i++){
        for(int j=0; j<tamanio_comp_conexas.size() ;j++){
            if(i!=j)
                combinaciones+= tamanio_comp_conexas[i]*tamanio_comp_conexas[j];
        }
    }

    combinaciones/=2;
    double res= combinaciones/boost::math::binomial_coefficient<double>(N, 2);

    cout << setprecision(5) << res << endl;

    return 0;
}