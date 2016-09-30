#include<bits/stdc++.h>
using namespace std;
const int M = 100000+10;
int tin[M],tout[M],tim,deep[M],anc[18][M];
vector<int> g[M];

void dfs (int o,int u) {
	tin[u] = ++tim;
	for (int v:g[o]) if (v!=o) {
		deep[v] = deep[u]+1;
		anc[0][v] = u;
		for (int k=1; k<18; k++) anc[k][v] = anc[k-1][anc[k-1][v]];
		dfs (u, v);
	}
	tout[u] = tim;
}

int getlca (int u,int v) {
	if (deep[u]<deep[v]) swap(u,v);
	for (int i=17; i>=0; i--)
		if (deep[anc[i][u]]>=deep[v]) u=anc[i][u];
	if (u==v) return u;
	for (int i=17; i>=0; i--)
		if (anc[i][u]!=anc[i][v]) u=anc[i][u], v=anc[i][v];
	return anc[0][u];
}
