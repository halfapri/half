#include <stdio.h>
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
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
#define sqr(x) ((x)*(x))
#define ALL(v) (v).begin(),(v).end()
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 1000000+10, upp=1000000;
int ls[M*25], rs[M*25], rt[M];

struct PERSIST {
	int T[M*25], sz;
	int init () {sz=0; return alloc(0);}
	inline int alloc (int o) {
		ls[sz] = ls[o], rs[sz] = rs[o], T[sz] = T[o];
		return sz++;
	}
	void build (int o,int l,int r) {
		T[o] = 0;
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=alloc(0),l,mid);
		build (rs[o]=alloc(0),mid+1,r);
	}
	void ins (int o,int l,int r,int u,int x) {
		if (l == r) {T[u]++; return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x);
		T[u] = T[ls[u]] + T[rs[u]];
	}
	int ask (int o,int u,int l,int r,int &k) {
		if (k > T[u]-T[o]) {k-=T[u]-T[o]; return -1;}
		if (l == r) return l;
		int mid = l+r>>1;
		int ret = ask (ls[o],ls[u],l,mid,k);
		if (~ret) return ret;
		return ask (rs[o],rs[u],mid+1,r,k);
	}
}sgt;

int prime[M], szp;
bool vis[M];
int rk[M], revrk[M], szrk;

int main () {
	//freopen ("read.txt", "r", stdin);
	szp = 0;
	for (int i=2; i<=upp; i++) {
		if (!vis[i]) prime[szp++] = i;
		for (int j=i+i; j<=upp; j+=i) vis[j] = 1;
	}
	szrk = 0;
	function<void(int,int,int,int)>dfs =
		[&](int v,int beg,int dep,int maxdep){
			if (dep==maxdep) {
				rk[v] = szrk; revrk[szrk++]=v; return;
			} 
			for (int i=beg; i<szp && v<=upp/prime[i]; i++)
				dfs (v*prime[i], i, dep+1, maxdep);
		};
	for (int i=1; i<=20; i++) dfs (1,0,0,i);
	sgt.build (rt[1]=sgt.init(),0,szrk-1);
	for (int i=2; i<=upp; i++) {
		//printf ("rk[%d]=%d,sgt.sz=%d\n",i,rk[i],sgt.sz);
		rt[i] = sgt.alloc (rt[i-1]);
		sgt.ins (rt[i-1],0,szrk-1,rt[i],rk[i]);
	}
	//////////////////////////////////////////////////////////////////
	int CASE;
	scanf ("%d", &CASE);
	for (int cas=1; cas<=CASE; cas++) {int A, B, K;
		scanf ("%d%d%d", &A, &B, &K);
		int ans = sgt.ask(rt[A-1],rt[B],0,szrk-1,K);
		printf ("Case %d:", cas);
		for (int i=revrk[ans], j=0; i!=1; j++)
			while (i%prime[j]==0) {
				printf (" %d", prime[j]);
				i/=prime[j];
			}
		puts ("");
	}
	return 0;
}
