#include<bits/stdc++.h>
using namespace std;
const int M = 1e5+10 ;
int lson[M<<2] , rson[M<<2] , c[M<<2] ; 
int rt[M] ;
int tot ;
int a[M] , b[M] ;
int n , m ;
int sz ;

int build (int l , int r) {
	int o = tot ++ ;
	c[o] = 0 ;
	if (l == r) return o ;
	int mid = l+r>>1 ;
	lson[o] = build(l,mid) ;
	rson[o] = build(mid+1,r) ;
}

int update (int o , int pos , int val) {
	int newo = tot ++ , tmp = newo ;
	c[newo] = c[o] + val ;
	int l = 1 , r = sz ;
	while (l < r) {
		int mid = l+r>>1 ;
		if (pos <= mid) {
			lson[newo] = tot ++ ; rson[newo] = rson[o] ;
			newo = tot ; o = lson[o] ;
			r = mid ;
		}
		else {
			rson[newo] = tot ++ ; lson[newo] = lson[o] ;
			newo = tot ; o = rson[o] ;
			l = mid+1 ;
		}
		c[newo] = c[o] + val ;
	}
	return tmp ;
}

int query (int lo , int ro , int k) {
	int l = 1 , r = sz ;
	while (l < r) {
		int mid = l+r>>1 ;
		if (c[lson[lo]] - c[lson[ro]] >= k) {
			lo = lson[lo] ; ro = lson[ro] ;
			r = mid ;
		}
		else {
			k -= c[lson[lo]] - c[lson[ro]] ;
			lo = rson[lo] , ro = rson[ro] ;
			l = mid+1 ;
		}
	}
	return l ;
}

int main () {
	scanf ("%d%d" , &n , &m) ;
	for (int i = 0 ; i < n ; i ++) {
		scanf ("%d" , a+i) ;
		b[i] = a[i] ;
	}
	sort (b , b+n) ;
	sz = unique(b,b+n)-b;
	int tmp = build (1 , sz) ;
	for (int i = 0 ; i < n ; i ++) {
	   int pos  = lower_bound(b,b+sz,a[i])-b+1;
	   tmp = update (tmp , pos , 1) ;
	   rt[i] = tmp ;
	}	   

	while (m --) {
		int l , r , k ;
		printf ("%d\n" , a[query(l?rt[l-1]:0 , rt[r] , k)-1]) ;
	}
	return 0 ;
}
