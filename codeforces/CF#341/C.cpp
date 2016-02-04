#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
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
const ll INF = (ll)1e18 ;

const int M = 1e5+10 ;
pair<int,int> a[M] ;
int n , p;
double tot = 0 ;

double get_pro (int i) {
	int num = a[i].S/p - (a[i].F-1)/p ;
	return 1.0*num/(1.0*a[i].S-1.0*a[i].F+1) ;
}

void work (int x , int y) {
	double px = get_pro(x) ;
	double py = get_pro(y) ;
	//printf ("px=%f,py=%f\n" , px,py) ;
	tot += (1.0-(1.0-px)*(1.0-py))*2000.0 ;
}

int main () {
	scanf ("%d%d" , &n , &p) ;
	for (int i = 0 ; i < n ; i ++) {
		scanf ("%d%d" , &a[i].F , &a[i].S) ;
	}
	for (int i = 0 ; i < n ; i ++) {
		work (i , (i+1)%n) ;
	}
	printf ("%.7f\n" , tot ) ;
	return 0 ;
}
