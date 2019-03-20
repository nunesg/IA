#include <bits/stdc++.h>

using namespace std;

#define N 100

typedef pair<int, int> ii;

struct edge{
	int destino, peso;
	edge(){}
	edge(int a, int b) : destino(a), peso(b) {}
};

int n, seen[N];//numero de vertices, vetor de visitados
map<string, int> dic;//mapeia os nomes das cidades para inteiros
vector<edge> adj[N];//listas de adjacencias do grafo
string inv[N];//recupera o nome de uma cidade pelo indice 
vector<int> answer;

void find_answer_bfs(int origin, int u, vector<int> &pai){//printa a resposta pra bfs e dijkstra
	if(u == origin){
		cout << inv[origin];
		return;
	}
	find_answer_bfs(origin, pai[u], pai);
	cout << " " << inv[u];
}

void bfs(int origin, int target){//busca em superficie
	
	vector<int> pai(n);
	memset(seen, 0, sizeof seen);
	queue<int> q;
	
	seen[origin] = 1;
	q.push(origin);
	while(q.size()){
		int u = q.front(); q.pop();
		if(u == target) break;
		for(edge e : adj[u]){
			if(seen[e.destino]) continue;
			
			seen[e.destino] = seen[u]+1;
			q.push(e.destino);
			pai[e.destino] = u;
		}
	}
	
	if(pai[target] == 0) {
		printf("Resposta nao encontrada\n");
		return;
	}
	
	find_answer_bfs(origin, target, pai);
	cout << "\ndistancia = " << seen[target]-1 << "\n\n";
	
}

void Dijkstra(int origin, int target){
	
	vector<int> pai(n);
	memset(seen, -1, sizeof seen);
	priority_queue< ii > pq;
	
	seen[origin] = 0;
	pq.push(ii(0, origin));
	
	while(pq.size()){
		ii foo = pq.top(); pq.pop();
		int u = foo.second, d = -foo.first;
		
		if(u == target) break;
		if(d>seen[u]) continue;
		
		for(edge e : adj[u]){
			if(seen[e.destino] != -1 && d+e.peso >= seen[e.destino]) continue;
			
			seen[e.destino] = d+e.peso;
			pq.push(ii(-seen[e.destino], e.destino));
			pai[e.destino] = u;
		}
	}
	
	if(pai[target] == 0) {
		printf("Resposta nao encontrada\n");
		return;
	}
	
	find_answer_bfs(origin, target, pai);
	cout << "\ndistancia = " << seen[target] << "\n\n";
	
}

bool dfs(int u, int target){//busca em profundidade
	answer.push_back(u);
	if(u == target){
		
		for(int x : answer){
			cout << inv[x] << " ";
		}
		cout << "\ndistancia = " << (int)answer.size()-1 << "\n";
		return true;
	}
	
	seen[u] = 1;
	
	for(edge e : adj[u]){
		if(seen[e.destino]) continue;
		
		if(dfs(e.destino, target)) return true;
		
	}
	answer.pop_back();
	return false;
}

bool dfs_limitada(int u, int target, int depth){//busca em profundidade limitada
	if(depth < 0) return false;
	answer.push_back(u);
	if(u == target){
		
		for(int x : answer){
			cout << inv[x] << " ";
		}
		cout << "\ndistancia = " << (int)answer.size()-1 << "\n";
		return true;
	}
	
	seen[u] = 1;
	
	for(edge e : adj[u]){
		if(seen[e.destino]) continue;
		
		if(dfs_limitada(e.destino, target, depth-1)) return true;
		
	}
	answer.pop_back();
	return false;
}


void solve(int origin, int target){
	
	printf("Busca em Largura(Superficie):\n");
	bfs(origin, target);
	
	memset(seen, 0, sizeof seen);
	printf("Busca em Profundidade:\n");
	if(!dfs(origin, target)) printf("Resposta nao encontrada\n");
	
	memset(seen, 0, sizeof seen);
	answer.clear();
	
	printf("\nBusca de custo uniforme(Dijkstra):\n");
	Dijkstra(origin, target);
	
	memset(seen, 0, sizeof seen);
	answer.clear();
	printf("\nBusca em Profundidade com limite 3:\n");
	if(!dfs_limitada(origin, target, 3)) printf("Resposta nao encontrada\n");
	
}


int main(){
	
	n=2;
	string a, b;
	cin >> a >> b;
	
	dic[a] = 0; dic[b] = 1;
	inv[0] = a;	inv[1] = b;
	
	int w;
	while(cin >> a){
		cin >> b >> w;

		if(!dic.count(a)) {
			inv[n] = a;
			dic[a] = n++;
		}
		if(!dic.count(b)) {
			inv[n] = b;
			dic[b] = n++;
		}
		
		adj[dic[a]].push_back(edge(dic[b], w));
		adj[dic[b]].push_back(edge(dic[a], w));
	}
	
	solve(0, 1);
}
