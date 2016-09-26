#include <stdio.h>
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
const int MOD=91250681,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 100000;
ll ss[M];
int SS;
int get (ll x) {
	return lower_bound (ss, ss+SS, x) - ss;
}
//////////////////////////////////////////////////////////////////

int ta, tb, n, m, X, tot; 
struct Ext {
	int l; ll r; int d;
} ext[M];
int EXT;
//////////////////////////////////////////////////////////////////

int ls[M*22], rs[M*22], rt[M], T[M*22];
struct PERSIST {
#define mid (l+r>>1)
	int PST;
	int init () {PST=0;return PST++;}
	inline int alloc (int o) {
		ls[PST]=ls[o], rs[PST]=rs[o], T[PST]=T[o];
		return PST++;
	}
	void build (int o,int l,int r) {
		T[o] = 0;
		if (l == r) return;
		build (ls[o]=PST++, l, mid);
		build (rs[o]=PST++, mid+1, r);
	}
	void ins (int o,int l,int r,int u,int x,int val) {
		if (l == r) {T[u] += val;return;}
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x,val);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x,val);
		T[u] = T[ls[u]] + T[rs[u]];
	}
	int ask (int o,int l,int r,int pl,int pr) {
		if (pl<=l && r<=pr) return T[o];
		int ret = 0;
		if (pl<=mid) ret += ask (ls[o],l,mid,pl,pr);
		if (pr>mid) ret += ask (rs[o],mid+1,r,pl,pr);
		return ret;
	}
#undef mid
} pst;

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~scanf ("%d%d", &ta, &tb)) {
		scanf ("%d%d%d", &X, &n, &m);
		EXT = SS = tot = 0;
		ss[SS ++] = -inf;
		for (int i=0, l,f,d; i<n; i++) {ll r;
			scanf ("%d%d%d", &l, &f, &d);
			if (l+f>=X && l+f<=X+tb) {
				l += 2*f;
				if (l+f>X+tb) r = l;
				else {
					int k = (X+tb-l-f)/(2*f)+1;
					r = 1ll*k*2*f+l;
				}
				ext[EXT ++] = {l, r, d};
				ss[SS ++] = l, ss[SS ++] = r;
				tot += d;
			}
		}
		for (int i=0, l,f,d; i<m; i++) {ll r;
			scanf ("%d%d%d", &l, &f, &d);
			l += f;
			if (l+f>X+tb || l+f<X) r = l;
			else {
				int k = (X+tb-l-f)/(2*f)+1;
				r = 1ll*k*2*f+l;
			}
			ext[EXT ++] = {l, r, d};
			ss[SS ++] = l, ss[SS ++] = r;
			tot += d;
		}
		sort (ext, ext+EXT, [](Ext a,Ext b) {
				return a.r < b.r ;
				});
		sort (ss, ss+SS);
		SS = unique(ss, ss+SS) - ss;
//////////////////////////////////////////////////////////////////
		pst.build (rt[0]=pst.init(), 0, SS-1);
		for (int i=1, j=0; i<SS; i++) {
			rt[i] = rt[i-1];
			while (j<EXT && ext[j].r == ss[i]) {
				int lst = rt[i];
				rt[i] = pst.alloc (lst);
				pst.ins (lst,0,SS-1,rt[i],get(ext[j].l),ext[j].d);
				j ++;
			}
		}
		int maxn = 0;
		for (int i=1; i<SS; i++) {
			int ans = pst.ask (rt[i],0,SS-1,
					get(ss[i]-ta),i);
			maxn = max (maxn, ans);
		}
		printf ("%d\n", tot-maxn);
	}
	return 0;
}
