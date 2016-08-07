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
#include <complex>
#include <functional>
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

const int M = 100000+10 ;
char s[M] ;
int sa[M],rk[M],height[M];

void da (const char *s,int n,int m=256) {
	int t1[M],t2[M],c[M];
	int *x=t1,*y=t2,i,j,k,p=1;
	memset (c,0,4*m) ;
	for (i=0; i<n; i++) c[x[i]=s[i]] ++ ;
	for (i=1; i<m; i++) c[i] += c[i-1] ;
	for (i=n-1; i>=0; i--) sa[--c[x[i]]] = x[i] ;
	for (k=1; p<n; k<<=1, m=p) {
		for (p=0, i=n-k; i<n; i++) y[p++] = i ;
		for (i=0; i<n; i++) if (sa[i]>=k) y[p++] = sa[i]-k ;
		memset (c,0,4*m) ;
		for (i=0; i<n; i++) c[x[i]] ++ ;
		for (i=1; i<m; i++) c[i] += c[i-1] ;
		for (i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i] ;
		for (swap(x,y), x[sa[0]]=0, p=1, i=1; i<n; i++)
			x[sa[i]] = y[sa[i]] == y[sa[i]-1] &&
				y[sa[i]+k] == y[sa[i-1]+k] ? p-1 : p++ ;
	}
	memcpy (rk,x,4*n) ;
	for (i=0,k=0; i<n-1; i++) {
		j = sa[rk[i]-1] ;
		while (s[i+k] == s[j+k]) k++ ;
		height[rk[i]] = k ;
		if (k) k -- ;
	}
}

int main () {
	scanf ("%s" , s) ;
	da (s , strlen(s)+1) ;
	return 0 ;
}
