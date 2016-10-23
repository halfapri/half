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

const int M = 100000+10, nill=0, mod=(int)1e9+7;
char s[M];
unsigned fix[M];
int fact[M];
int ls[M], rs[M], rt;

struct Node {
	int sz;
	unsigned fix;
	int sum[10];
	char ch;
	bool mk;
	inline void init (char _ch) {
		sz=1, fix=rand();
		memset(sum,0,sizeof(sum)), sum[ch=_ch-'a']++, mk=0;
	}
	inline int inv(int x) {
		if (x==0) return 1;
		int ret=1;
		for (int i=mod-2; i; i>>=1) {
			if (i&1) ret = 1ll*ret*x%mod;
			x = 1ll*x*x%mod;
		}
		return ret;
	}
	inline int getans () {
		int cnt=0, tot=0, ans=1;
		for (int i=0; i<10; i++) {
			if (sum[i]&1) cnt ++;
			ans = 1ll*ans*inv(fact[sum[i]/2])%mod;
			tot += sum[i];
		}
		if (tot & 1) {
			if (cnt==1) ans = 1ll*ans*fact[tot/2]%mod;
			else ans=0;
		} else {
			if (cnt) ans=0;
			else ans = 1ll*ans*fact[tot/2]%mod;
		}
		return ans;
	}
	inline void up(Node &ls,Node &rs) {
		memset (sum, 0, sizeof(sum));
		sum[ch]++;
		sz = ls.sz+rs.sz+1;
		for (int i=0; i<10; i++) sum[i]+=ls.sum[i]+rs.sum[i];
	}
	inline void mark (int o) {
		mk^=1, swap(ls[o],rs[o]);
	}
}T[M];

struct Treap {
	int MY;
	void init () {MY=1;}
	inline int alloc(char _ch) {
		T[MY].init(_ch); ls[MY]=rs[MY]=nill; return MY++;
	}
	inline void down(int o) {
		if (T[o].mk) {
			if (ls[o]!=nill) T[ls[o]].mark(ls[o]);
			if (rs[o]!=nill) T[rs[o]].mark(rs[o]);
			T[o].mk=0;
		}
	}
	inline void up(int o) {T[o].up(T[ls[o]],T[rs[o]]);}
	void build (int &o,int l,int r) {
		if (l>r) return;
		int mid = l+r>>1;
		build (ls[o=alloc(s[mid])],l,mid-1);
		build (rs[o],mid+1,r);
		T[o].fix = fix[mid];
		up(o);
	}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a=o,b=nill;return;}
		if (k<=0) {a=nill,b=o;return;}
		down(o);
		if (k>T[ls[o]].sz) cut(rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
		else cut(ls[o],a,ls[b=o],k);
		up(o);
	}
	void merge (int &o,int a,int b) {
		if (a==nill) o=b;
		else if (b==nill) o=a;
		else if (T[a].fix>T[b].fix) {
			down(o=a); merge(rs[o],rs[a],b); up(o);
		} else {
			down(o=b); merge(ls[o],a,ls[b]); up(o);
		}
	}
	int ask (int l,int r) {
		int a,b,c;
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		int ans = T[b].getans();
		merge (rt, a, b);
		merge (rt, rt, c);
		return ans;
	}
	void flip (int l,int r) {
		int a,b,c;
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		T[b].mark(b);
		merge (rt, a, b);
		merge (rt, rt, c);
	}
	void Print (int rt) {
		if (rt==nill) return;
		Print (ls[rt]);
		printf ("%c", T[rt].ch+'a');
		Print (rs[rt]);
	}
}my;

int n, m;

int main () {
	srand(time(0));
	for (int i=0; i<M; i++) fix[i] = rand();
	sort (fix, fix+M, [](unsigned a,unsigned b) {
			return a>b;
			});
	fact[0]=1;
	for (int i=1; i<M; i++) fact[i] = 1ll*fact[i-1]*i%mod;
	scanf ("%d%d", &n,&m);
	scanf ("%s", s);
	my.init();
	my.build (rt, 0, n-1);
	while (m --) {int op,l,r;
		scanf ("%d%d%d", &op,&l,&r);
		if (op==1) {
			my.flip(l,r);
		} else {
			printf ("%d\n", my.ask(l,r));
		}
	}
	return 0;
}

