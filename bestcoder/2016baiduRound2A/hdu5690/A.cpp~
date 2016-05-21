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

ll m ;
int x,k,c ;

int main () {
    int CASE ;
    scanf ("%d" , &CASE) ;
    for (int cas=1 ; cas<=CASE ; cas ++) {
        scanf ("%d" LLD "%d%d" , &x,&m,&k,&c) ;
        int len = -1 ;
        for (int i=1, tmp=0 ; i< 10000+10 && i<=m ; i++) {
            tmp = (tmp*10+x)%k ;
            if (tmp == c) {
                len = i ;
                break ;
            }
        }
        int ha = 0 ;
        if (~len) {
            for (int i=1,tmp=c ; i<10000+10 && i<=m ; i++) {
                tmp = (tmp*10+x)%k ;
                if (tmp == c) {
                    ha = i ;
                    break ;
                }
            }
        }
        //printf ("len=%d,ha=%d\n" , len,ha) ;
        printf ("Case #%d:\n" , cas) ;
        if (len==m) puts ("Yes") ;
        else if (m>len && ha != 0 && (m-len)%ha==0) puts ("Yes") ;
        else puts ("No") ;
    }
    return 0 ;
}
