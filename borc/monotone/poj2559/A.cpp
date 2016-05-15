#include<stdio.h>
#include<stack>
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
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
int sign(double x){return x<-eps?-1:x>eps;}

const int M = 100000+10 ;
int h[M] , n;
int L[M] , R[M] ;

void solve () {
	stack<int> q ;
	for (int i=0 ; i<n ; i++) {
		while (!q.empty() && h[q.top()]>=h[i]) q.pop() ;
		L[i] = q.empty()?0:q.top()+1 ;
		q.push (i) ;
	}
	while (!q.empty()) q.pop() ;
	for (int i=n-1 ; i>=0 ; i--) {
		while (!q.empty() && h[q.top()]>=h[i]) q.pop() ;
		R[i] = q.empty()?n-1:q.top()-1 ;
		q.push(i) ;
	}
	ll maxn = -1 ;
	for (int i=0 ; i<n ; i++) {
		maxn = max (maxn , 1ll*(R[i]-L[i]+1)*h[i]) ;
	}
	printf (LLD "\n" , maxn) ;
}

int main () {
	while (~scanf("%d",&n) && n) {
		for (int i=0 ; i<n ; i++) scanf ("%d" , h+i) ;
		solve () ;
	}
	return 0 ;
}
