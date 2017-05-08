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

const int M = 100000+10;
struct EDGE {
    int v,nxt;
} e[M<<1];
int head[M], E;

inline void addEdge (int u,int v) {
    e[E] = EDGE{v,head[u]};
    head[u] = E++;
}

int n, m;
int anc[18][M];
int deep[M];
int maxDeep;

void dfs (int o,int u) {
    deep[u] = deep[o] + 1;
    maxDeep = max(maxDeep, deep[u]);
    for (int i=head[u], v; ~i; i=e[i].nxt) {
        v = e[i].v;
        if (v == o) continue;
        anc[0][v] = u;
        for (int j=1; j<18; ++j) anc[j][v] = anc[ j-1 ][ anc[j-1][v] ];
        dfs (u, v);
    }
}

inline int go (int u,int dep) { 
    if (deep[u]<dep) return -1;
    for (int i=17; i>=0; --i) {
        if (deep[u] - (1<<i) >= dep) u = anc[i][u];
    }
    return u==0 ? 1 : u;
}

int a[M], A, b[M], B;
bool vis[M];
vector<int> st;

int main () {
    while (~scanf("%d%d", &n,&m)) {
        memset (head, -1, sizeof(head[0])*(n+1));
        E = 0;
        for (int i=0,u,v; i<n-1; ++i) {
            scanf ("%d%d", &u,&v);
            addEdge(u, v);
            addEdge(v, u);
        }
        maxDeep = 0;
        dfs (0, 1);
        while (m --) {
            scanf ("%d", &A);
            for (int i=0; i<A; ++i) scanf ("%d", a+i);
            scanf ("%d", &B);
            for (int i=0; i<B; ++i) scanf ("%d", b+i);
            int l = 1, r = maxDeep, ret = l;
            while (l<=r) {
                int mid = l+r>>1;
                for (int i=0, v; i<A; ++i) {
                    v = go(a[i], mid);
                    if (~v && !vis[v]) {
                        st.emplace_back(v); 
                        vis[v] = true;
                    }
                }
                bool flag = false;
                for (int i=0, v; i<B; ++i) {
                    v = go(b[i], mid);
                    if (~v && vis[v]) {
                        flag = true;
                        break;
                    }
                }
                while (!st.empty()) {
                    vis[st.back()] = false;
                    st.pop_back();
                }
                if (flag) l = mid+1, ret = mid;
                else r = mid-1;
            }
            printf ("%d\n", ret);
        }
    }
    return 0;
}
