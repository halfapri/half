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

const int M=200000+10, nill=0;
unsigned fix[M];
int ls[M], rs[M], rt;
char s[M];
struct Node {
	int sz;
	unsigned fix;
	char ch;
	int sum[26];//26个英文字母的和
	char mk;//延迟标记
	inline void init (char chh) {
		memset (sum,0,sizeof(sum));
		ch=chh;
		sum[ch-'a']++;
		mk=2;
	}
	inline void up (const Node &ls, const Node &rs) {
		for (int i=0; i<26; i++) sum[i]=ls.sum[i]+rs.sum[i];
		sum[ch-'a'] ++;
		sz=ls.sz+rs.sz+1;
	}
}T[M];

int MY;

struct Treap {
	inline int alloc (char ch) {
		T[MY].init(ch); T[MY].sz=1; T[MY].fix=fix[MY]; ls[MY]=rs[MY]=nill; 
		return MY++;
	}
	inline void down (Node &p,Node &ls,Node &rs) {
		if (p.mk==2) return;
		int i=p.mk==0?0:25, v=p.mk==0?1:-1, tmp=0;
		memset (ls.sum, 0, sizeof(ls.sum));
		memset (rs.sum, 0, sizeof(rs.sum));
		for (;i>=0 && i<26; i+=v) {
			tmp += p.sum[i];
			if (tmp<=ls.sz) ls.sum[i]=p.sum[i];
			else {
				tmp -= p.sum[i];
				ls.sum[i] = ls.sz-tmp;
				p.ch = i+'a';
				rs.sum[i] = p.sum[i]-ls.sum[i]-1;
				break;
			}
		}
		for (i+=v; i>=0 && i<26; i+=v) rs.sum[i]=p.sum[i];
		//beg
		//printf ("o:%c\n", p.ch);
		//puts ("ls:");
		//for (int i=0; i<26; i++) if (ls.sum[i]) {
		//	for (int j=0; j<ls.sum[i]; j++) printf ("%c", i+'a');
		//}puts("");
		//puts ("rs:");
		//for (int i=0; i<26; i++) if (rs.sum[i]) {
		//	for (int j=0; j<rs.sum[i]; j++) printf ("%c", i+'a');
		//}puts("");
		//end
		//
		ls.mk=rs.mk=p.mk;
		p.mk=2;
	}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a=o,b=nill;return;}
		if (k<=0) {a=nill,b=o;return;}
		down (T[o],T[ls[o]],T[rs[o]]);
		if (k>T[ls[o]].sz) cut (rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
		else cut (ls[o],a,ls[b=o],k);
		T[o].up(T[ls[o]],T[rs[o]]);
	}
	void Merge (int &o,int a,int b) {
		if (a==nill) o=b;
		else if (b==nill) o=a;
		else if (T[a].fix>T[b].fix) {
			down(T[a],T[ls[a]],T[rs[a]]); 
			Merge(rs[o=a],rs[a],b); 
			T[o].up(T[ls[o]], T[rs[o]]);
		} else {
			down(T[b],T[ls[b]],T[rs[b]]); 
			Merge(ls[o=b],a,ls[b]); 
			T[o].up(T[ls[o]], T[rs[o]]);
		}
	}
	void build (int &o,int l,int r) {
		if (l>r) return;
		int mid = l+r>>1;
		build (ls[o=alloc(s[mid])],l,mid-1); build (rs[o],mid+1,r);
		T[o].up (T[ls[o]],T[rs[o]]);
	}
	void update (int l,int r,int mk) {
		int a, b, c;
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		T[b].mk = mk;
		//beg
		//printf ("T[a].sz=%d\n", T[a].sz);
		//printf ("T[c].sz=%d\n", T[c].sz);
		//puts ("update:");
		//for (int i=0; i<26; i++) {
		//	for (int j=0; j<T[b].sum[i]; j++) printf ("%c", i+'a');
		//} puts("");
		//end
		Merge (rt, a, b);
		Merge (rt, rt, c);
	}
	void Print (int o) {
		if (o==nill) return;
		down (T[o],T[ls[o]],T[rs[o]]);
		Print (ls[o]);
		printf ("%c", T[o].ch);
		Print (rs[o]);
	}
} my;

int n, Q;

int main () {
	MY=1;
	srand(time(0));
	for (int i=0; i<M; i++) fix[i] = rand();
	scanf ("%d%d", &n,&Q);
	scanf ("%s", s);
	my.build (rt, 0, n-1);
	int l, r, mk;
	while (Q --) {
		scanf ("%d%d%d", &l,&r,&mk);
		my.update (l, r, !mk);
		//beg
		//my.Print(rt); puts("");
		//my.Print(rt); puts("");
		//end
	}
	my.Print(rt);
	puts ("");
	return 0;
}
