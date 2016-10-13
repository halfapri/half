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

const int M = 100000+10, nill=0;
unsigned fix[M];
typedef pair<int,int> pii;
int fa[M], ls[M], rs[M], rt, it[M];
struct Node
{
    int sz;
    unsigned fix;
    bool mk;
    void init () {
        sz=1, mk=0;
    }
    void mark (int o) {
        mk ^= 1, swap (ls[o], rs[o]);
    }
}T[M];

struct Treap
{
    int MY;
    void init () {T[0].sz=T[0].fix=T[0].mk=0;MY=1;}
    inline int alloc () {
        T[MY].init(); T[MY].fix=fix[MY]; ls[MY]=rs[MY]=nill; return MY++;
    }
    inline void up (int o) {
        T[o].sz = T[ls[o]].sz+T[rs[o]].sz+1;
        fa[ls[o]] = fa[rs[o]] = o;
    }
    inline void down (int o) {
        if (T[o].mk) {
            T[ls[o]].mark (ls[o]);
            T[rs[o]].mark (rs[o]);
            T[o].mk = 0;
        }
    }
    void cut (int o,int &a,int &b,int k) {
        if (T[o].sz <= k) {a=o,b=nill;return;}
        if (k<=0) {a=nill,b=o;return;}
        down (o);
        if (k>T[ls[o]].sz) cut (rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
        else cut (ls[o],a,ls[b=o],k);
        up (o);
    }
    void Merge (int &o,int a,int b) {
        if (a==nill) o=b;
        else if (b==nill) o=a;
        else if (T[a].fix>T[b].fix) {
            down (a); Merge (rs[o=a],rs[a],b); up (o);
        } else {
            down (b); Merge (ls[o=b],a,ls[b]); up (o);
        }
    }
    void build (int &o,int l,int r) {
        if (l>r) return;
        int mid = l+r>>1;
        build (ls[o=alloc()],l,mid-1);
        build (rs[o],mid+1,r);
        it[mid-1] = o;
        up (o);
    }
    int ask (int o) {
        if (o==rt) {down(o); return 0;}
        int ret = ask (fa[o]);
        down (o);
        if (o == rs[fa[o]]) ret += 1 + T[ls[fa[o]]].sz;
        return ret;
    }
    void rev (int r) {
        int a, b, c;
        cut (rt, a, b, r);
        T[a].mark(a);
        Merge (rt, a, b);
        cut (rt, a, rt, 1);
    }
    void Print (int o) {
        if (o==nill) return;
        printf ("%d:%d %d\n", o,ls[o],rs[o]);
        Print (ls[o]);
        Print (rs[o]);
    }
}my;

int n;
pii a[M];

int main ()
{
	//freopen ("read.txt", "r", stdin);
    srand (time(0));
	for (int i=0; i<M; i++) fix[i] = rand();
	sort (fix, fix+M, [](int x,int y) {
			return x>y;
			});
    while (~scanf("%d", &n) && n) {
        for (int i=0; i<n; i++) scanf ("%d", &a[i].fi), a[i].se = i;
        sort (a, a+n);
        my.init();
        my.build (rt, 1, n);
        //my.Print (rt);
        for (int i=0; i<n; i++) {
            int o = it[a[i].se];
            //printf ("o=%d\n", o);
            int r = my.ask (o) + 1 + T[ls[o]].sz;
            printf ("%d%c", i+r, " \n"[i==n-1]);
            //printf ("\nl=%d,r=%d\n", i+1,r);
            my.rev (r);
        }
    }
	//showtime;
    return 0;
}
