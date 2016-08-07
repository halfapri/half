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

const int M = 20000+10;
int sa[M],rk[M],height[M];
int a[M],n,k ;

void da (const int *s,int n,int m) {
	int t1[M],t2[M],c[1000000+10];
	int *x=t1, *y=t2, i,j,k,p=1;
	memset (c, 0, 4*m) ;
	for (i=0; i<n; i++) c[x[i]=s[i]] ++;
	for (i=1; i<m; i++) c[i] += c[i-1];
	for (i=n-1; i>=0; i--) sa[--c[x[i]]] = i;
	for (k=1; p<n; k<<=1, m=p) {
		for (p=0, i=n-k; i<n; i++) y[p++] = i;
		for (i=0; i<n; i++) if(sa[i]>=k) y[p++] = sa[i]-k;
		memset (c, 0, 4*m);
		for (i=0; i<n; i++) c[x[i]]++;
		for (i=1; i<m; i++) c[i] += c[i-1];
		for (i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i];
		for (swap(x,y), x[sa[0]]=0, p=1, i=1; i<n; i++)
			x[sa[i]] = y[sa[i]] == y[sa[i-1]] &&
				y[sa[i]+k] == y[sa[i-1]+k] ? p-1 : p++;
	}
	memcpy (rk, x, 4*m);
	for (i=0, k=0; i<n-1; i++) {
		j = sa[rk[i]-1];
		while (s[i+k] == s[j+k]) k++;
		height[rk[i]] = k ;
		if (k) k -- ;
	}
}

bool judge (int len) {
	int cnt=1;
	for (int i=2; i<=n; i++) {
		if (cnt>=k) return true;
		if (height[i]>=len) cnt ++;
		else cnt = 1;
	}
	return cnt>=k;
}

int solve () {
	int l=k, r=n, ret=k;
	while (l<=r) {
		int mid = l+r>>1;
		if (judge(mid)) ret = mid, l = mid+1;
		else r = mid-1;
	}
	return ret ;
}

int main () {
	while (~ scanf("%d%d", &n, &k)) {
		for (int i=0; i<n; i++)  {
			scanf ("%d", a+i);
			a[i] ++;
		}
		a[n] = 0;
		da (a, n+1, 1000002);
		//for (int i=0; i<=n; i++) printf ("(%d)=%d\n",i,height[i]);
		printf ("%d\n" , solve());
	}
	return 0;
}

