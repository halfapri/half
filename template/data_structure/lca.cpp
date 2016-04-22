#include<bits/stdc++.h>
using namespace std;
const int M = 1e5 + 10 ;
int tin[M] , tout[M] , tim ;
int anc[M][20] ;

vector<int> g[M] ;

void lca (int o , int u) {
	tin[u] = ++ tim ;
	for (int v : g[u]) {
		if (v == o) continue ;
		anc[v][0] = u ;
		for (int i = 1 ; i < 20 ; i ++)  {
			anc[v][i] = anc[ anc[v][i-1] ][ i-1 ] ;
		}
		lca (u , v ) ;
	}
	tout[u] = ++ tim ;
}

bool isanc (int u , int v) { return tin[u] <= tin[v] && tout[u] >= tout[v] ; }

int get_lca (int u , int v) {
	int i = 19 ;
	while (!isanc(u , v)) {
		if (i == 0 || !isanc(anc[u][i] , v)) u = anc[u][i] ;
		else i -- ;
	}
	return u ;
}
