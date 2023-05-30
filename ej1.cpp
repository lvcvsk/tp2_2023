#include<iostream>
#include<vector>
#include<utility>
#include<set>
#include <iomanip>
using namespace std;


//Grafo, vector de vecindades
vector< set<int> > G;

//nos niveles de cada nodo en el árbol dfs
vector<int> niveles;

//aquel nodo de menor nivel al que se puede llegar a traves de los vecinos (sin contar al padre) o sus hijos
vector<int> menor_ancestro;

//en el árbol dfs, la cantidad de nodos contando al padre y sus hijos
vector<int> tamanio_subarbol;

vector<bool> visitado;
vector< pair<int,int> > aristas_puente;      //se utiliza solo para debuggear 

long casos_favorables;

//Implemento el numero combinatorio
long int comb(int n, int k){
    long int matriz[k][n];
    for(int i=0; i<n ;i++)
        matriz[0][i]= i+1;
    
    for(int i=1; i<k ;i++)
        matriz[i][i]=1;
    
    for(int i=1; i<k; i++){
        for(int j=i+1; j<n ;j++)
            matriz[i][j]= matriz[i-1][j-1]+matriz[i][j-1];
    }
    
    return matriz[k-1][n-1];
}

//utilizo dfs para construirme un arbol
void dfs(int v, int nivel){
    visitado[v]= true;
    tamanio_subarbol[v]+=1 ;
    niveles[v]= nivel;
    for(int w :  G[v]){
        if(!visitado[w]){
            dfs(w, nivel+1);

            //si a traves de este hijo puedo encontrar un camino a un nodo de nivel inferior a v, actualizo
            if(niveles[menor_ancestro[w]]<niveles[menor_ancestro[v]])
                menor_ancestro[v]= menor_ancestro[w];
            
            if(niveles[menor_ancestro[w]]>niveles[v]){
                aristas_puente.push_back(make_pair(v,w));

                //si vw es arista puente calculo las comb favorables con los nodos debajo de mi arbol
                //luego los "borro" de mi arbol modificando tamanio_subarbol
                if(tamanio_subarbol[w]>=2)
                    casos_favorables+= comb(tamanio_subarbol[w],2);
                tamanio_subarbol[w]= 0;
            }

            //el tamaño del subarbol que incluye a b incluye la suma de todos los subárboles
            tamanio_subarbol[v]+=tamanio_subarbol[w];
        }
        else{
            //si y visite ese nodo y ese vertice me lleva a un nodo de un nivel menor, actualizo
            if( niveles[w]+1!=niveles[v] && niveles[w]<niveles[menor_ancestro[v]])
                menor_ancestro[v]= w ;
        }
    }
    if(niveles[v]==0){
        //cuando llego a la raiz calculo los casos favorables con la cantidad de nodos que no "eliminé"
        if(tamanio_subarbol[v]>=2)
            casos_favorables+= comb(tamanio_subarbol[v],2);
    }
}


int main(){
    int N; int M;
    
    //recibo los valores de entrada
    cin>>N; cin>>M;
   
    //inicializo G
    G= vector< set<int>> (N,set<int>());

    for(int i=0; i<M ;i++){
        int a; int b;
        cin>>a; cin>>b;
        G[a-1].insert(b-1);
        G[b-1].insert(a-1);
    }

    //inicializo el verctor
    for(int i=0; i<G.size() ;i++){
        menor_ancestro.push_back(i);
    }

    //Utilizo dfs para descrubrir las aristas puente

    niveles= vector<int>(N,0);
    tamanio_subarbol= vector<int>(N,0);
    visitado= vector<bool>(N,false);
    
    casos_favorables= 0;

    //aplico dfs a nodo cualquiera, ya que el grafo es conexo
    dfs(0,0);

    //calculo las probabilidades
    double prob_perder= 1-((double)casos_favorables/comb(N, 2));

    cout << setprecision(5) << prob_perder << endl;

    return 0;
}
	