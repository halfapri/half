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

const int M = 200000;
int ch[M][2], rt; 
unsigned ran[M];
struct Node {
	int ac,tim,lastac,no;
	int sz;
	unsigned fix;
	Node () {}
	Node (int _ac,int _tim) : ac(_ac), tim(_tim) {}
	Node (int _ac,int _tim,int _lastac,int _no) :
		ac(_ac),tim(_tim),lastac(_lastac),no(_no) {}
	void init (int _ac,int _tim,int _lastac,int _no) {
		ac=_ac,tim=_tim,lastac=_lastac,no=_no,sz=1,fix=rand();
	}
} T[M];

struct Treap {
	int MY;
	void init () {MY=1;T[0].no=-1;T[0].fix=0;}
	inline int alloc (int ac,int tim,int lastac,int no) {
		T[MY].init(ac,tim,lastac,no); ch[MY][0]=ch[MY][1]=0;
		return MY++;
	}
	inline void up (int o) {
		T[o].sz = T[ch[o][0]].sz+T[ch[o][1]].sz+1;
	}
	void build (int &o,int l,int r) {
		if (l>r) return;
		int mid = l+r>>1;
		o = alloc(0,0,0,mid-1);
		T[o].fix = ran[o];
		build (ch[o][0], l, mid-1);
		build (ch[o][1], mid+1, r);
		up (o);
	}
	inline void rot (int &o,int d) {
		int u = ch[o][d]; ch[o][d]=ch[u][!d], ch[u][!d]=o;
		up (o), up (u), o=u;//这里顺序不能换
	}
//////////////////////////////////////////////////////////////////
	inline bool better1 (Node x,Node y) {
		if (x.ac==y.ac) {
			if (x.tim==y.tim) {
				if (x.lastac==y.lastac) return x.no<y.no;
				return x.lastac<y.lastac;
			}return x.tim<y.tim;
		} return x.ac>y.ac;
	}
	void ins (int &o,Node x) { 
		if (!o) {o=alloc(x.ac,x.tim,x.lastac,x.no);return;}
		bool d = better1 (T[o],x);
		ins (ch[o][d], x);
		T[ch[o][d]].fix>T[o].fix ? rot(o, d): up (o);
	}
	void del (int &o,Node x) {
		if (!o) return;
		if (T[o].ac==x.ac&&T[o].tim==x.tim&&
				T[o].lastac==x.lastac&&T[o].no==x.no) {
			if (ch[o][0]==ch[o][1]) {o=0; return;}
			bool d = !ch[o][1] ? 0 : !ch[o][0] ? 1 : 
				T[ch[o][1]].fix > T[ch[o][0]].fix;
			rot (o, d); del (ch[o][!d], x);
		} else del (ch[o][better1(T[o],x)], x);
		up (o);
	}
//////////////////////////////////////////////////////////////////
	inline bool better2 (Node x,Node y) {
		if (x.ac==y.ac) return x.tim<y.tim;
		return x.ac>y.ac;
	}
	int askR (int o,Node x) {
		if (!o) return 0;
		if (better2(T[o],x)) 
			return T[ch[o][0]].sz+1 + askR(ch[o][1], x);
		return askR(ch[o][0], x);
	}
	int askT (int o,int k) {
		if (!o) return -1;
		if (k>T[ch[o][0]].sz) {
			k -= T[ch[o][0]].sz+1;
			if (k == 0) return T[o].no;
			return askT (ch[o][1], k);
		} return askT (ch[o][0], k);
	}
} my;

struct Team {
	int ac,tim,lastac,lastsub,penal[11];
	inline void init () {
		ac=tim=lastac=0, lastsub=-5; 
		memset(penal,0,sizeof(penal));
	}
	inline bool valid (int now,char id) {
		if (penal[id]==-1) return false;
		if (now-lastsub<5) return false;
		return true;
	}
} team[M];

int n, m;

int main () {
	//freopen ("read.txt", "r", stdin);
	srand (time(0));
	for (int i=0; i<M; i++) ran[i]=rand();
	sort (ran, ran+M, [](unsigned x,unsigned y) {
			return x>y;
			});
	while (~ scanf("%d%d", &n,&m)) {
		for (int i=0; i<n; i++) team[i].init();
		my.init();
		my.build (rt,1,n);
		char op[10];
		int now,no,res,k;
		char id;
		int fk=0;
		while (~scanf("%s", op)) {
			if (op[0]=='C') {scanf("%s",op);break;}
			fk ++;
			if (op[0]=='S') {
				scanf ("%d:%d:%c:%d", &now,&no,&id,&res);
				id -= 'A';
				Team &x = team[no];
				if (x.valid(now,id)) {
					if (res) {
						printf ("[%d][%c]\n", no, id+'A');
						Team y = x;
						x.ac ++;
						x.tim += now + x.penal[id];
						x.penal[id] = -1;
						x.lastac = fk;
						x.lastsub = now;
						my.del (rt, Node(y.ac,y.tim,y.lastac,no));
						my.ins (rt, Node(x.ac,x.tim,x.lastac,no));
					} else x.lastsub=now,x.penal[id]+=20;
				}
			} else if (op[0]=='R') {
				scanf ("%d", &no);
				Team &x = team[no];
				printf ("%d\n", my.askR(rt, Node(x.ac,x.tim))+1);
			} else {
				scanf ("%d", &k);
				int tmp = k;
				no = my.askT (rt, tmp);
				if (no == -1) puts ("-1");
				else {
					Team &x = team[no];
					tmp = my.askR (rt, Node(x.ac,x.tim))+1;
					tmp == k ? printf ("%d\n", no) : puts ("-1");
				}
			}
		} puts ("");
	}
	return 0;
}
