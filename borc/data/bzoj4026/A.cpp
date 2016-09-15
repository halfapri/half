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
const int MOD=(int)1e9+21,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int mod = 1000777, M = 100000+10;
struct EDGE {
	int v,nxt;
} e[mod*3];
int head[mod], es;
int prime[M], szp;
bool vis[mod];

//////////////////////////////////////////////////////////////////
int rt[M], ls[M*155], rs[M*155], T[M*155];
struct PERSISI {
	int sz;
	int init () {sz=0;return sz++;}
	inline int alloc (int o) {
		ls[sz]=ls[o], rs[sz]=rs[o], T[sz]=T[o];
		return sz++;
	}
	void build (int o,int l,int r) {
		T[o] = 1;
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=sz++,l,mid);
		build (rs[o]=sz++,mid+1,r);
	}
	void ins (int o,int l,int r,int u,int x,int val) {
		if (l == r) {T[u] = 1ll*T[u]*val%mod; return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x,val);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x,val);
		T[u] = 1ll*T[ls[u]]*T[rs[u]]%mod;
	}
	int ask (int o,int l,int r,int pr) {
		if (r<=pr) return T[o];
		int mid = l+r>>1, ret=1;
		ret = 1ll*ret*ask(ls[o],l,mid,pr)%mod;
		if (pr>mid) ret = 1ll*ret*ask(rs[o],mid+1,r,pr)%mod;
		return ret;
	}
} sgt;

//////////////////////////////////////////////////////////////////
int vmax[mod], pre[M], inv[mod], n, Q, a[M];

int main () {
	//freopen ("read.txt", "r", stdin);
	memset (head, -1, sizeof(head));
	for (int i=2; i<=1000000; i++) if (!vis[i]) {
		prime[szp++] = i;
		for (int j=i; j<=1000000; j+=i) {
			vis[j] = 1;
			e[es] = {i, head[j]}; head[j] = es ++;
		}
	}
	inv[0] = inv[1] = 1;
	for (int i=2; i<=mod; i++) 
		inv[i] = 1ll*(mod-mod/i)*inv[mod%i]%mod;
//////////////////////////////////////////////////////////////////
	scanf ("%d%d", &n, &Q);
	pre[0] = 1;
	for (int i=1; i<=n; i++) {
		scanf ("%d", a+i);
		pre[i] = 1ll*pre[i-1]*a[i]%mod;
	}
	sgt.build (rt[0]=sgt.init(),0,n);
	for (int i=1; i<=n; i++) {
		rt[i] = rt[i-1];
		for (int j=head[a[i]]; ~j; j=e[j].nxt) {int v=e[j].v;
			int lst = rt[i];
			rt[i] = sgt.alloc(lst);
			sgt.ins(lst,0,n,rt[i],vmax[v],1ll*(v-1)*inv[v]%mod);
			vmax[v] = i;
		}
	}
//////////////////////////////////////////////////////////////////
	int ans = 0;
	while (Q --) {int l, r;
		scanf ("%d%d", &l, &r);
		l ^= ans, r ^=ans;
		ans = 1ll*pre[r]*inv[pre[l-1]]%mod;
		ans = 1ll*ans*sgt.ask(rt[r],0,n,l-1)%mod;
		ans = 1ll*ans*inv[sgt.ask(rt[l-1],0,n,l-1)]%mod;
		printf ("%d\n", ans);
	}
	return 0;
}
