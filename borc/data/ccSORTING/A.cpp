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

const int M = (int)5e5+10;
int ls[M*24], rs[M*24], T[M*24], rt[M];

struct PERSIST {
	int sz;
	int init () {sz=0;return alloc(0);}
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
		if (l == r) {T[u]=1;return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x);
		T[u] = T[ls[u]] + T[rs[u]];
	}
	int bins (int o,int u,int l,int r,int &k) {
		if (k>T[u]-T[o]) {k-=T[u]-T[o];return -1;}
		if (l == r) return l;
		int mid = l+r>>1;
		int ret = bins (ls[o],ls[u],l,mid,k);
		if (~ret) return ret;
		return bins (rs[o],rs[u],mid+1,r,k);
	}
} sgt;

int n, id[M], a[M];;
ll dfs (int l,int r) {
	if (l>=r) return 0;
	int tmp;
	int ans = sgt.bins (rt[l-1],rt[r],1,n,tmp = (r-l+2)/2);
	return dfs (l,a[ans]-1) + dfs (a[ans]+1,r) + r-l+1;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d", &n);
	for (int i=1; i<=n; i++) {
		scanf ("%d", a+i);
		id[a[i]] = i;
	}
	sgt.build (rt[0]=sgt.init(),1,n);
	for (int i=1; i<=n; i++)
		sgt.ins (rt[i-1],1,n,rt[i]=sgt.alloc(rt[i-1]),id[i]);
	printf (LLD "\n", dfs (1, n));
	return 0;
}
