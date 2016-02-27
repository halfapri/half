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

const int M = 100000+10 ;
int L[M] , R[M] ;
int a[M] , b[M<<1] ;
int n , m ;
int pal[M<<1] ;

void get_lr () {
	L[0] = 0 ;
	for (int i = 1 ; i < n ; i ++) {
		if (a[i]>=a[i-1])
			L[i] = L[i-1] ;
		else
			L[i] = i ;
	}
	R[n-1] = n-1 ;
	for (int i = n-2 ; i >= 0 ; i --) {
		if (a[i] >= a[i+1])
			R[i] = R[i+1] ;
		else
			R[i] = i ;
	}
}

void manacher () {
	m = 0 ;
	b[m++] = -2 ; b[m++] = -1 ;
	for (int i = 0 ; i < n ; i ++) {
		b[m++] = a[i] ;
		b[m++] = -1 ;
	}
	
	int mx = 0 , id = 0 ;
	for (int i=1 ; i<m ; i ++) {
		if (mx>i)
			pal[i] = pal[2*id-i]<mx-i?pal[2*id-i]:mx-i ;
		else
			pal[i] = 1 ;
		while (b[i+pal[i]]==b[i-pal[i]]) pal[i] ++ ;
		if (i+pal[i]>mx) {
			mx = i+pal[i] ;
			id = i ;
		}
	}
	//for (int i = 1 ; i < m ; i ++)printf("%d ",pal[i]);puts ("");
	//for (int i = 0 ; i < n; i ++) {
	//	printf ("(%d , %d)\n" , L[i],R[i]) ;
	//}

	int maxn = 1 ;
	for (int i = 2 ; i<m ; i ++) { 
		int tmp = (pal[i]*2-1)/2 ;
		if (tmp==1) continue ;
		if (i&1) {
			int xl = (i-1)/2-1 , xr = (i+1)/2-1 ;
			if (xl-L[xl]+1>=tmp/2 && R[xr]-xr+1>=tmp/2)
				maxn = max(maxn , tmp) ;
		}
		else {
			int x = i/2-1 ;
			if (x-L[x]>=tmp/2 && R[x]-x>=tmp/2)
				maxn = max(maxn , tmp) ;
		}
	}
	printf ("%d\n" , maxn) ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf ("%d" , &n) ;
		for (int i = 0 ; i < n ; i ++) {
			scanf ("%d" , &a[i]) ;
		}
		get_lr () ;
		manacher () ;
	}
	return 0 ;
}
