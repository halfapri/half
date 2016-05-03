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
int sign(double x){return x<-eps?-1:x>eps;}

const int M = 100000+10 ;
int idx[M] , N , k , sz;
ll a[M] ;

bool needed (int f1 , int f2 , int f3) {
	return (f3-f1)*(a[f2]-a[f1])-(f2-f1)*(a[f3]-a[f1])<0 ;
}

bool judge (int f1 , int f2 , int f3) {
	return (a[f1]-a[f2])*(f1-f3) < (a[f1]-a[f3])*(f1-f2) ;
}

inline void qkread (ll &ans) {
	char c; bool flag = false;
	while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
	if (c == '-') flag = true; else ans = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') ans = ans * 10 + c - '0';
	ans *=(flag ? -1 : 1);
}

int main () {
	while (~ scanf ("%d%d",&N,&k)) {
		sz = 0 ;
		for (int i=0 ; i<N ; i++) {
			qkread (a[i]) ;
			if (i) a[i] += a[i-1] ;
			while (true) {
				if (sz>2 && !needed(idx[sz-2],idx[sz-1],i)) sz -- ;
				else break ;
			}
			idx[sz++] = i ;
		}
		double ans = -INF ;
		for (int i=k,j=0 ; i<N ; i++) {
			while (j+1<sz && idx[j+1]+k<=i && judge(i,idx[j],idx[j+1])) j ++ ;
			double tmp = 1.0*(a[i]-a[idx[j]])/ (1.0*(i-idx[j])) ;
			if (sign(ans-tmp) < 0)
				ans = tmp ;
		}
		printf ("%.2f\n" , ans) ;
	}
	return 0 ;
}
