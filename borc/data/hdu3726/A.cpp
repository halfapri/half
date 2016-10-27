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
template <class T> inline int SZ(T x){return (int)x.size();}

const int M=400000, MN=20000+10, nill=0;
int ls[M], rs[M];
struct Node {
	int sz;
	unsigned fix;
	int v,id;
	inline void init(int _v,int _id) {
		sz=1, fix=rand();
		v=_v, id=_id;
	}
}T[M];

int MY;
inline int alloc (int _v,int _id) {
	T[MY].init(_v,_id); ls[MY]=rs[MY]=nill; return MY++;
}

struct Treap {
	int rt;
	inline void init() {rt=nill;}
	inline void up(int o) {T[o].sz=T[ls[o]].sz+T[rs[o]].sz+1;}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a=o,b=nill;return;}
		if (k<=0) {a=nill,b=o;return;}
		if (k>T[ls[o]].sz)cut(rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
		else cut(ls[o],a,ls[b=o],k);
		up(o);
	}
	void merge (int &o,int a,int b) {
		if (a==nill) o=b;
		else if (b==nill) o=a;
		else if (T[a].fix>T[b].fix) {
			merge(rs[o=a],rs[a],b); up(o);
		} else {
			merge(ls[o=b],a,ls[b]); up(o);
		}
	}
	inline bool better (Node &x,int &v,int &id) {
		if (v==x.v) return id<=x.id;
		return v>x.v;
	}
	int askR (int o,int v,int id) {
		if (o==nill) return 0;
		int ret=0;
		if (better(T[o],v,id)) ret=askR(ls[o],v,id);
		else ret=1+T[ls[o]].sz+askR(rs[o],v,id);
		return ret;
	}
	void ins (int v,int id) {
		int a,b,c, k=askR(rt,v,id);
		cut (rt, a, b, k);
		merge (rt, a, alloc(v,id));
		merge (rt, rt, b);
	}
	void ins (int o) { 
		T[o].sz=1, ls[o]=rs[o]=nill;
		int a,b,c, k=askR(rt,T[o].v,T[o].id);
		cut (rt, a, b, k);
		merge (rt, a, o);
		merge (rt, rt, b);
	}
	void update (int _v,int _id,int v) {
		int a,b,c, k=askR(rt,_v,_id);
		cut (rt, a, b, k);
		cut (b, b, c, 1);
		T[b].v=v;
		merge (rt, a, c);
		ins (b);
	}
	int ask (int k) {
		if (k>size() || k<=0) return 0;
		int a,b,c;
		cut (rt, a, b, k-1);
		cut (b, b, c, 1);
		int ans=T[b].v;
		merge (rt, a, b);
		merge (rt, rt, c);
		return ans;
	}
	inline int size() {return T[rt].sz;}
}my[M];
//////////////////////////////////////////////////////////////////

struct Arr {
	int val,nxt;
}arr[M];
int H[M], ARR;

struct Edge {
	int u,v,nxt;
}e[M*6];
int head[M], E;
bool vis[M*6];

struct Query {
	int op,x,v;
}query[M];
int n, m, Q;
int fa[M], FA;

void DFS (int o, Treap &x,int type) {
	if (o==nill) return;
	DFS (ls[o], x, type);
	DFS (rs[o], x, type);
	fa[T[o].id]=type;
	x.ins (o);
}

void Union (int x,int y) {
	if (x==y) return;
	if (SZ(my[x])<SZ(my[y])) swap(x,y);
	DFS (my[y].rt, my[x], x);
}

void dfs (int u) {
	my[FA].ins (arr[H[u]].val,u);
	fa[u] = FA;
	for (int i=head[u]; ~i; i=e[i].nxt) {
		if (vis[i] || fa[e[i].v]!=-1) continue;
		dfs (e[i].v);
	}
}

double solve () {
	MY=1, FA=0;
	memset (fa, -1, sizeof(int)*(n+1));
	for (int i=1; i<=n; i++) if(fa[i]==-1) {
		my[FA].init(); dfs(i); FA++;
	}
	int cnt=0;
	ll ans=0;
	for (int i=Q-1; i>=0; i--) {
		if (query[i].op==0) {
			int id = (query[i].x-1)*2;
			Union (fa[e[id].u], fa[e[id].v]);
			//printf ("D %d\n", query[i].x);
		} else if (query[i].op==1) {
			cnt ++;
			int tmp = my[fa[query[i].x]].ask(query[i].v);
			ans += tmp;
			//printf ("Q %d %d:%d\n",query[i].x,query[i].v,tmp);
		} else {
			int x=query[i].x;
			my[fa[x]].update(arr[H[x]].val,x,arr[arr[H[x]].nxt].val);
			H[x] = arr[H[x]].nxt;
			//printf ("C %d %d\n", query[i].x,query[i].v);
		}
	}
	return ans/(1.0*cnt);
}

int main () {
	//freopen ("read.txt", "r", stdin);
	srand(time(0));
	int cas=1;
	while (~scanf("%d%d", &n,&m) && n+m) {
		memset (H, -1, sizeof(int)*(n+1));
		memset (head, -1, sizeof(int)*(n+1));
		memset (vis, 0, sizeof(bool)*(2*(m+1)));
		ARR=E=0;
		for (int i=1; i<=n; i++) {
			scanf ("%d", &arr[ARR].val);
			arr[ARR].nxt=H[i];
			H[i] = ARR++;
		}
		for (int i=1,u,v; i<=m; i++) {
			scanf ("%d%d", &u,&v);
			e[E] = {u,v,head[u]};
			head[u] = E++;
			e[E] = {v,u,head[v]};
			head[v] = E++;
		}
		Q=0;
		char s[10];
		while (~scanf("%s", s)) {
			if (s[0]=='E') break;
			if (s[0]=='D') {
				scanf("%d", &query[Q].x);
				query[Q].op=0;
				vis[(query[Q].x-1)*2]=1;
				vis[(query[Q].x-1)*2+1]=1;
			} else if (s[0]=='Q') {
				scanf("%d%d", &query[Q].x,&query[Q].v);
				query[Q].op=1;
			} else {
				scanf("%d%d", &query[Q].x,&query[Q].v);
				arr[ARR] = {query[Q].v,H[query[Q].x]};
				H[query[Q].x] = ARR++;
				query[Q].op=2;
			}
			Q++;
		}
		printf ("Case %d: %.6f\n", cas++, solve());
	}
	return 0;
}
