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

const int M = 100000+10;
int rs[M*22], ls[M*22], rt[M*22];

struct PERSIST {
	int T[M*22], n;
	inline int init () { n = 0; return newnode(); }
	inline int newnode () { T[n] = 0; return n++; }
	void build (int o,int l,int r) {
		if (l == r) return;
		int mid = l+r>>1;
		ls[o] = newnode(), rs[o] = newnode();
		build (ls[o], l, mid); 
		build (rs[o], mid+1, r);
	}
	void ins (int o,int l,int r,int k) {
		int cur = n-1;
		T[cur] = T[o] + 1;
		if (l == r) return;
		int mid = l+r>>1;
		if (k <= mid) {
			ls[cur] = newnode(), rs[cur] = rs[o];
			ins (ls[o],l,mid,k);
		} else {
			ls[cur] = ls[o], rs[cur] = newnode();
			ins (rs[o],mid+1,r,k);
		}
	}
	int ask (int l,int r,int pl,int pr,int &k) {
		if (k > T[pr]-T[pl]) { 
			k -= T[pr]-T[pl]; return -1;
		}
		if (l == r) return l;
		int mid = l+r>>1;
		int ret = ask(l,mid,ls[pl],ls[pr],k);
		if (~ret) return ret;
		return ask (mid+1,r,rs[pl],rs[pr],k);
	}
} sgt;

struct VC:vector<int> {
	void done () {
		sort (begin(),end());
		erase (unique(begin(),end()),end());
	}
	int get (int x) {
		return lower_bound (begin(),end(),x) - begin();
	}
} ss;

int n, m;
int a[M];

int main () {
	freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d%d", &n, &m)) {
		ss.resize (n);
		for (int i=1; i<=n; i++) {
			scanf ("%d", &a[i]);
			ss[i-1] = a[i];
		}
		ss.done ();
		sgt.build (rt[0]=sgt.init(),0,ss.size()-1);
		for (int i=1; i<=n; i++) {
			rt[i] = sgt.newnode();
			sgt.ins (rt[i-1],0,ss.size()-1,ss.get(a[i]));
		}
		while (m --) {int i,j,k;
			scanf ("%d%d%d", &i, &j, &k); 
			int x = sgt.ask(0,ss.size()-1,rt[i-1],rt[j],k);
			printf ("%d\n", ss[x]);
		}
	}
	return 0;
}
