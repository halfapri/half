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
int s[M] , t[M<<1] ;
int lens , lent ;
int pal[M<<1] ;
int minleft[M<<2] ;
int LEFT[M] , n;

int build (int o , int l , int r) {
	if (l==r) 
		return minleft[o] = LEFT[l] ;
	int mid=l+r>>1 ;
	return minleft[o] = min (build(lson) , build(rson)) ;
}

int query (int L , int R , int o , int l , int r) {
	if (l==r) {
		if (minleft[o]<=L) 
			return l ;
		return -1 ;
	}
	int mid=l+r>>1 ;
	int ans = -1 ;
	if (mid+1<=R && minleft[o<<1|1]) 
		ans = query(L,R,rson) ;
	if (~ans) 
		return ans ;
	if (mid>=L && minleft[o<<1]<=L)
		ans = query(L,R,lson) ;
	return ans ;
}

void solve () {
	for (int i=1 ; i<lent ; i+=2 ) {
		LEFT[(i+1)/2] = (i-pal[i]+1+1)/2 ;
	}
	n = lens+1 ;
	//for (int i=1 ; i<=n ; i++) {
	//	printf ("%d " , LEFT[i]) ;
	//} puts ("") ;
	build (1,1,n) ;
	int maxn = 0 ;
	for (int i=1 ; i<=n ; i++) {
		if (LEFT[i]==i) continue ;
		int tmp = query (i,2*i-LEFT[i],1,1,n) ;
		//printf ("%d:%d\n" , i,tmp) ;
		maxn = max (maxn , 3*(tmp-i)) ;
	}
	printf ("%d\n" , maxn) ;
}

void manacher () {
	lent = 0 ;
	t[lent++] = -2 , t[lent++] = -1 ;
	for (int i=0 ; i<lens ; i++) {
		t[lent++] = s[i] ;
		t[lent++] = -1 ;
	}

	int mx=0 , id=0 ;
	for (int i=1 ; i<lent ; i++) {
		if (mx>i) pal[i] = pal[2*id-i]<mx-i?pal[2*id-i]:mx-i ;
		else 
			pal[i] = 1 ;
		while (t[i+pal[i]]==t[i-pal[i]]) pal[i] ++ ;
		if (i+pal[i]>mx) {
			mx=i+pal[i] ;
			id=i ;
		}
	}

	solve () ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	for (int cas=1 ; cas<=T ; cas ++) {
		scanf ("%d" , &lens) ;
		for (int i=0 ; i<lens ; i++) {
			scanf ("%d" , &s[i]) ;
		}
		printf ("Case #%d: " , cas) ;
		manacher () ;
	}
	return 0 ;
}
