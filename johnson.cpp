#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <set>

using namespace std;
vector<int> filial;
int n_locais, n_filiais, ligs;

struct Aresta {
  int head;
  int custo;
};

const int INF = INT_MAX;

vector<vector<Aresta> > loadgraph(){

  vector<vector< Aresta> > grafo;
  cin >> n_locais >> n_filiais >> ligs;
  int u, v, w, n;
  grafo.resize(n_locais+1);
  for (int i=0; i < n_filiais; i++){
    cin >> n;
    filial.push_back(n);
  }

  for (int i = 0; i < ligs; i++){
    cin >> u >> v >> w;
    Aresta e = {v, w};
    grafo[u].push_back(e);  
  }

  return grafo;
}

vector<int> bellmanford(vector<vector<Aresta> > &grafo, int s) {
  vector<int> primeiro (n_locais+1, 0);
  vector<int> segundo (n_locais+1, 0);

  for (int i = 1; i < n_locais+1 ; i++) {
    
    for (int n = 0; n < n_locais+1; n++) {
      if (segundo[n] < primeiro[n]) {
        primeiro[n] = segundo[n];
      }
      for(unsigned int e = 0; e < grafo[n].size(); e++){
        if (segundo[n] != INF) {
          if (segundo[n] + grafo[n][e].custo < primeiro[grafo[n][e].head]) {
            primeiro[grafo[n][e].head] = segundo[n] + grafo[n][e].custo;
          }
        }
      }
    }
    segundo = primeiro;
  }

  return segundo;
}


vector<int> dijkstra(const vector<vector<Aresta> > &grafo, int s) {
  vector<int> dist(grafo.size(), INF);
  set< pair<int,int> > pilha;

  pair<int,int> par(0,s);
  pilha.insert(par);

  while (!pilha.empty()) {
    pair<int,int> p = *pilha.begin();
    pilha.erase(pilha.begin());

    int d = p.first;
    int n = p.second;

    dist[n] = d;
    for (unsigned int e = 0; e < grafo[n].size() ; e++) {
      if (dist[n]+grafo[n][e].custo < dist[grafo[n][e].head]) {
        if (dist[grafo[n][e].head] != INF) {
          pair<int,int> par2(dist[grafo[n][e].head], grafo[n][e].head);
          pilha.erase(pilha.find(par2));
        }
        pair<int,int> par3(dist[n]+grafo[n][e].custo, grafo[n][e].head);
        pilha.insert(par3);
        dist[grafo[n][e].head] = dist[n]+grafo[n][e].custo;
      }
    }
  }
  return dist;
}


int johnson(vector<vector<Aresta> > &grafo) {
  vector<int> aux (n_locais+1);
  vector<int> temp (n_locais+1);

  for (int i = 0; i < n_locais+1; i++) {
    Aresta aresta = {i, 0};
    grafo[0].push_back(aresta);
  }
  
  vector<int> ssp;
  ssp = bellmanford(grafo, 0);

  
  for (int i = 1; i < n_locais+1; i++) {
    for (unsigned int e = 0; e < grafo[i].size(); e++){
      grafo[i][e].custo = grafo[i][e].custo + ssp[i] - ssp[grafo[i][e].head];
    }
  }

  
  int shortest = INF;
  int vertice= -1;

  for (int u = 0; u < n_filiais; u++) {
    temp = dijkstra(grafo, filial[u]); 
    for (int v = 1; v < n_locais+1; v++) {
      if (aux[v] != INF && temp[v] != INF) {
        temp[v] += ssp[v] - ssp[filial[u]];
        aux[v] += temp[v];
      }
      else aux[v]=INF;
    }
  }

  for (int i = 1 ; i < n_locais+1; i++){
    if (aux[i] < shortest){
      shortest = aux[i];
      vertice = i;
    } 
  }
  if (vertice == -1){
    cout << "N\n";
    return 0;
  }
  else{
    cout << vertice << " "<<  shortest << "\n";
    for (int u = 0; u < n_filiais; u++) {
    temp = dijkstra(grafo, filial[u]); 
    temp[vertice] += ssp[vertice] - ssp[filial[u]];
    cout << temp[vertice] << " ";
    }
  }
  cout << endl;
  return 0;
}


int main () {

  vector< vector<Aresta> > grafo = loadgraph();
  return johnson(grafo);
}
