#include <bits/stdc++.h>
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
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;

char s[1010] ;
const int M = 1000+10 ;
struct Palindromic {
    int S[M] ;
    int go[M][26] ;
    int len[M] ;
    int fail[M] ;
    int last ;
    int oL ;
    int n ;

    inline int newnode (int sz) {
        for (int i=0 ; i<26 ; i++) 
            go[oL][i] = 0 ;
        len[oL] = sz ;
        return oL ++ ;
    }

    inline void init () {
        last=oL=n=0 ;
        newnode (0) ;
        newnode (-1) ;
        fail[1] = fail[0] = 1 ;
        S[0] = -1 ;
    }

    inline int get_fail (int o) {
        while (S[n-len[o]-1]!=S[n]) {
            o=fail[o] ;
        }
        return o ;
    }

    inline void Insert (char ch) {
        ch -= 'a' ;
        S[++n] = ch ;
        int cur = get_fail (last) ;
        if (!go[cur][ch]) {
            int now = newnode (len[cur]+2) ;
            fail[now] = go[ get_fail(fail[cur]) ][ch] ;
            go[cur][ch] = now ;
        }
        last = go[cur][ch] ;
    }
} pt;

int Q ;
int n ;
int answer[1010][1010] ;

void In(int &num) {
    char c = getchar();
    while('0' > c || c > '9') c = getchar();
    for(num = 0; '0' <= c && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
}

void Out(int x) {
    if(x>9) Out(x/10) ;
    putchar(x%10+'0') ;
}


int main () {
    int T ;
    scanf ("%d" , &T) ;
    while (T --) {
        scanf ("%s" , s+1) ;

        int n = strlen(s+1) ;
        for (int i=1 ; i<=n ; i++) {
            pt.init () ;
            for (int j=i ; j<=n ; j++) {
                pt.Insert (s[j]) ;
                answer[i][j] = pt.oL-2 ;
            }
        }
        In(Q) ;
        for (int i=0 ; i<Q ; i++) {
            int l , r ;
            In(l) ; In(r) ;
            Out (answer[l][r]) ; putchar ('\n') ;
        }
    } 
    return 0 ;
}
