#include <iostream>
#include <list>
#include <vector>
#define NIL -1

using namespace std;
vector< list<int> > graph;
vector<int> parent;
vector<int> disc;
vector<int> low;
vector<bool> ap;
vector<bool> visited;
static int t = 1;



void dfs_aux(int current){
	visited[current] = true;
	disc[current]= t;
	t++;
	int children = 0;
	disc[current] = low[current] = t;

	list<int>::iterator it;
	for(it = graph[current].begin(); it != graph[current].end(); it++){
		int v = *it;

		if (!visited[v]){
			children++;
			parent[v] = current;
			dfs_aux(v);
			low[current] = min(low[current], low[v]);
			//primeiro caso
			if (parent[current] == NIL && children > 1)
				ap[current] = true;
			//segundo caso
			if (parent[current] != NIL && low[v] >= disc[current])
				ap[current] = true;
		}
		else if (v != parent[current])
			low[current]  = min(low[current], disc[v]);
	visited[current]=true;
	}

}

void dfs(int n){
	visited = vector<bool>(n+1, false);
	parent = vector<int>(n+1, NIL);
	disc = vector<int>(n+1);
	low= vector<int>(n+1);


	for(int i = 1 ; i <= n; i++ ){
		if (visited[i] == false)
			dfs_aux(i);
		
	}

}


int main() {

	int n_vertex, n_edges;
	int u , v, min=1000, max=-1, count=0;

	cin >> n_vertex >> n_edges;
	graph = vector< list<int> >(n_vertex+1);
	ap = vector<bool>(n_vertex+1, false);

	for(int i=1; i <= n_edges; i++ ){
		cin >> u >> v;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	dfs(n_vertex);
	for (int i = 1; i <= n_vertex; i++){
		if( ap[i] == true){
			count++;
			if(i >= max)
				max = i;
			if(i <= min)
				min = i;
			
		}
	}
	
	
	if(count == 0){
		min = -1;
		max = -1;
	}
	cout << count << "\n";
	cout << min << " "<< max << "\n";
	

	return 0;
}
