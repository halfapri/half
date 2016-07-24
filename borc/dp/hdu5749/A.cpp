#include <stdio.h>
#include <bitset>
#include <string.h>
#include <stack>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <math.h>
#include <queue>
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
#define ALL(v) (v).begin(),(v).end()
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
int sign(double x){return x<-eps?-1:x>eps;}

typedef unsigned ui ;
const int M = 1000+5 ;
int a[M][M] ,U[M][M] , D[M][M] , R[M][M] , L[M][M] , n , m ;

void debug (int a[M][M]) {
	for (int i=0 ; i<n ; i++) {
		for (int j=0 ; j<m ; j++) {
			printf ("%d " , a[i][j]) ;
		} puts ("") ;
	} puts ("") ;
}

ui calc (ui l , ui x , ui r) {
	ui d1 = x-l+1 , d2 = r-x+1 ;
	return (1+d1)*d1/2*d2 + (d2-1)*d2/2*d1 ;
}

ui solve () {
	stack<int> q ;
	for (int i=0 ; i<n ; i++) {
		for (int j=0 ; j<m ; j++) {
			while (!q.empty()&&a[i][j]<a[i][q.top()]) q.pop() ;
			L[i][j] = q.empty()?0:q.top()+1 ;
			q.push (j) ;
		} 
		while (!q.empty()) q.pop() ;
		for (int j=m-1 ; j>=0 ; j--) {
			while (!q.empty()&&a[i][j]<a[i][q.top()]) q.pop() ;
			R[i][j] = q.empty()?m-1:q.top()-1 ;
			q.push (j) ;
		}
		while (!q.empty()) q.pop() ;
	}
	//debug(L) ; debug(R) ;
	for (int i=0 ; i<m ; i++) {
		for (int j=0 ; j<n ; j++) {
			while (!q.empty()&&a[j][i]>a[q.top()][i]) q.pop() ;
			U[j][i] = q.empty()?0:q.top()+1 ;
			q.push (j) ;
		}
		while (!q.empty()) q.pop() ;
		for (int j=n-1 ; j>=0 ; j--) {
			while (!q.empty()&&a[j][i]>a[q.top()][i]) q.pop() ;
			D[j][i] = q.empty()?n-1:q.top()-1 ;
			q.push(j) ;
		}
		while (!q.empty()) q.pop() ;
	}
	//debug(U) ; debug(D) ;
	ui ret = 0 ;
	for (int i=0 ; i<n ; i++) 
		for (int j=0 ; j<m ; j++) 
			ret += (ui)a[i][j]*calc(L[i][j],j,R[i][j])*
				calc(U[i][j],i,D[i][j]) ;
	return ret ;
}

int main () {
	int CASE ;
	scanf ("%d" , &CASE) ;
	while (CASE --) {
		scanf ("%d%d" , &n , &m) ;
		for (int i=0 ; i<n ; i++)
			for (int j=0 ; j<m ; j++)
				scanf ("%d" , &a[i][j]) ;
		printf ("%u\n" , solve()) ;
	}
	return 0 ;
}
