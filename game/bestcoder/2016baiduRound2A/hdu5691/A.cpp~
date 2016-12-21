#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <math.h>
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
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
int sign(double x){return x<-eps?-1:x>eps;}

int n ;
ll dp[1<<16][17] ;
int b[17] ;
int a[17] ;
int state ;
bool vis[1<<16][17] ;

inline int get_x (int s,int ret=0) {
    for (s ; s ; s>>=1) if (s&1) ret ++ ;
    return ret ;
}

ll dfs (int s , int lst) {
    if (s == (1<<n)-1) return 0 ;
    if (vis[s][lst]) return dp[s][lst] ;
    int x = get_x (s) ;
    if (~b[x]) {
        dp[s][lst] = 1ll*a[b[x]]*a[lst] + dfs(s|(1<<b[x]) , b[x]) ;
    } else {
        ll maxn = -INF ;
        for (int i=0 ; i<n ; i++) {
            if ( ((s>>i) & 1) || ((state>>i)&1) ) continue ;
            maxn = max(maxn , 1ll*a[lst]*a[i] + dfs(s|(1<<i) , i)) ;
        }
        dp[s][lst] = maxn ;
    }
    vis[s][lst] = 1 ;
    return dp[s][lst] ;
}

int main () {
    int CASE ;
    scanf ("%d" , &CASE) ;
    a[16] = 0 ;
    for (int cas=1 ; cas<=CASE ; cas ++) {
        memset (b , -1 , sizeof(b)) ;
        memset (vis , 0 , sizeof(vis)) ;
        state = 0 ;
        scanf ("%d",&n) ;
        for (int i=0 ,x ; i<n ; i++) {
            scanf ("%d%d",a+i,&x) ;
            if (~x) {
                b[x] = i ;
                state |= 1<<i ;
            }
        }
        printf ("Case #%d:\n" , cas) ;
        printf (LLD "\n" , dfs (0 , 16)) ;
    }
    return 0 ;
}
