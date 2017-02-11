#include <stdio.h>
#include <numeric>
#include <time.h>
#include <bitset>
#include <string.h>
#include <stack>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <math.h>
#include <queue>
#include <complex>
#include <functional>
#include <limits.h>
using namespace std ;
typedef long long ll ;
typedef long double ld ;
typedef unsigned long long ull ;
#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif
#define pi (acos(-1.0))
#define fi first
#define se second
#define SZ(x) ((int)x.size())
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
#define sqr(x) ((x)*(x))
#define ALL(v) (v).begin(),(v).end()
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
const double eps = 1e-9 ;
const int MOD=(int)1e9+7,BAS=233;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}
int AP (char *s) {
	unsigned hash=0;
	for(int i=0; s[i]; i++){
		if (i & 1) hash ^= (~((hash<<11)^s[i]^(hash>>5)));
		else hash ^= ((hash<<7)^s[i]^(hash>>3));
   } return hash & 0x7FFFFFFF;
}

const int M = 1000+10;
bool vis[M];
int spf[M];
int deep[M];
int low[M];
struct vec : vector<int> {
	void done() {
		sort(begin(),end());
		erase(unique(begin(),end()),end());
	}
} g[M];

void dfs (int u,int dep) {
	deep[u] = low[u] = dep;
	vis[u] = true;
	int ans=0;
	for (int i=0, v; i<SZ(g[u]); i++) {
		v = g[u][i];
		if (!vis[v]) {
			dfs (v, dep+1);
			if (low[v]>=dep) ans ++;
			else low[u] = min(low[u], low[v]);
		} else if (vis[v] && deep[v]<dep) {
			low[u] = min(low[u], deep[v]);
		}
	}
	if (dep==1) spf[u] = ans>1?ans:0;
	else spf[u] = ans+1;
}

void init (int &cnt) {
	for (int i=0; i<M; i++) g[i].clear();
	cnt = 0;
}

int main () {
	int u, v, cas=1;
	int cnt=0;
	while (~scanf ("%d",&u)) {
		if (u==0) {
			if (cnt==0) break;
			for (int i=1; i<M; i++) g[i].done();
			memset (vis, 0, sizeof(vis));
			memset (spf, 0, sizeof(spf));
			for (int i=1; i<M; i++) if (!vis[i]) {
				dfs (i, 1);
			}
			printf ("Network #%d\n", cas++);
			bool flag=0;
			for (int i=1; i<M; i++) if (spf[i]>1) {
				printf ("  SPF node %d leaves %d subnets\n",i,spf[i]);
				flag=true;
			}
			if (!flag) puts ("  No SPF nodes");
			puts ("");
			init (cnt);
			continue;
		}
		scanf ("%d", &v);
		cnt ++;
		if (u==v) continue;//去掉自环
		g[u].push_back(v);
		g[v].push_back(u);
	}
	return 0;
}
