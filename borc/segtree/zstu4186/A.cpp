#include<bits/stdc++.h>
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define F first
#define S second
using namespace std;
const int M = 8e4 + 10 ;
typedef pair<int,int> pii ;
vector<pii> sis[M] , node[M<<2] ;
typedef long long ll ;
ll pre[M] ;
int n , m , t ;
 
void Join (int o) {
    vector<pii> ans = node[o] ;
    sort (ans.begin() , ans.end()) ;
    node[o].clear () ;
    for (int i = 0 ; i < ans.size() ; ++ i) {
        for (int j = i+1 , at = i ; j < ans.size() ; ++j ) {
            if (ans[j].F == ans[at].F) i = j ;
            else break ;
        }
        node[o].push_back (ans[i]) ;
        for (int j = i+1 , at = i ; j < ans.size () ; ++j ) {
            if (ans[j].S <= ans[at].S) i = j ;
            else break ;
        }
    }
}
 
void build (int o , int l , int r) {
    node[o].clear () ;
    if (l == r) {
        sort (sis[l].begin() , sis[l].end()) ;
        int cur = 1 ;
        for (int i = 0 ; i < sis[l].size () ; i ++) {
            if (sis[l][i].F > cur) node[o].push_back ({cur,sis[l][i].F-1}) ;
            cur = max (cur , sis[l][i].S+1) ;
        }
        if (t >= cur) node[o].push_back ({cur,t}) ;
        return ;
    }
    int mid = l+r>>1 ;
    build (lson) ; build (rson) ;
    node[o] = node[o<<1] ;
    for (int i = 0 ; i < node[o<<1|1].size () ; i ++) node[o].push_back (node[o<<1|1][i]) ;
    Join (o) ;
}
 
bool judge (int pl , int pr , int o) {
    int x = lower_bound (node[o].begin() , node[o].end() , make_pair(pl,pr)) - node[o].begin() ;
    if (x-1 >= 0 && node[o][x-1].F <= pl && pr <= node[o][x-1].S) return true ;
    if (x != node[o].size () && node[o][x].F <= pl && pr <= node[o][x].S) return true ;
    return false ;
}
 
int Ask (int pl , int pr , int o , int l , int r) {
    if (l == r) {return judge (pl,pr,o) ? l : 0 ; }
    int mid = l+r>>1 ;
    if (judge (pl,pr,o<<1)) return Ask (pl,pr,lson) ;
    else if (judge (pl,pr,o<<1|1)) return Ask (pl,pr,rson) ;
    return 0 ;
}
 
int main () {
    while (~ scanf ("%d%d%d" , &n , &m , &t)) {
        memset (pre , 0 , sizeof(pre)) ;
        for (int i = 0 ; i <= n ; i ++) sis[i].clear () ;
        int L , R , id ;
        for (int i = 0 ; i < m ; i ++) {
            scanf ("%d%d%d" , &L , &R , &id) ;
            sis[id].push_back ({L,R}) ;
            pre[L] ++ ; pre[R+1] -- ;
        }
        build (1 , 1 , n) ;
        for (int i = 1 ; i <= t ; i ++) pre[i] += pre[i-1] ;
        for (int i = 1 ; i <= t ; i ++) pre[i] += pre[i-1] ;
        int Q , z = 0 ;
        scanf ("%d" , &Q) ; 
        while (Q --) {
            scanf ("%d%d" , &L , &R) ;
            L += z , R += z ;
            if (R > t) L = t - (R-L) , R = t ;
            z = Ask (L , R , 1,1,n) ;
            printf ("%lld %d\n" , pre[R] - pre[L-1] , z) ;
        }
    }
    return 0 ;
}
