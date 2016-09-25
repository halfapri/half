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
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

//实践证明，岛娘的lg2()灰常好用。我在网上查看了关于优化ST询问的算法的方法，因为ST虽说是O(1)回答的，但常数有点大，怎么办呢？因为sa能做的题目数据量一般就1e6这样，所以我们完全可以开一个lg[]数组，lg[x]=lg2(x)，这样询问时直接在lg[]进行，这样就能把常数大大减小了。
const int M = 100000+10 ;
char s[M] ;
int sa[M],rk[M],height[M],st[18][M];

void da (const char *s,int n,int m=256) {
	static int t1[M],t2[M],c[M];
	int *x=t1,*y=t2,i,j,k,p=1;
	memset (c,0,sizeof(c[0])*m) ;
	for (i=0; i<n; i++) c[x[i]=s[i]] ++ ;
	for (i=1; i<m; i++) c[i] += c[i-1] ;
	for (i=n-1; i>=0; i--) sa[--c[x[i]]] = x[i] ;
	for (k=1; p<n; k<<=1, m=p) {
		for (p=0, i=n-k; i<n; i++) y[p++] = i ;
		for (i=0; i<n; i++) if (sa[i]>=k) y[p++] = sa[i]-k ;
		memset (c,0,sizeof(c[0])*m) ;
		for (i=0; i<n; i++) c[x[i]] ++ ;
		for (i=1; i<m; i++) c[i] += c[i-1] ;
		for (i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i] ;
		for (swap(x,y), x[sa[0]]=0, p=1, i=1; i<n; i++)
			x[sa[i]] = y[sa[i]] == y[sa[i-1]] &&
				y[sa[i]+k] == y[sa[i-1]+k] ? p-1 : p++ ;
	}
	memcpy (rk,x,sizeof(x[0])*n) ;
	for (i=0, k=0; i<n-1; height[rk[i++]] = k?k-1:k++) 
		for (j=sa[rk[i]-1]; s[j+k] == s[i+k]; k++);
	memcpy (st[0], height, sizeof(height[0])*n);
	for (k=1; 1<<k <= n; k++)
		for (i=0; i+(1<<k)-1<n; i++)
			st[k][i] = min(st[k-1][i], st[k-1][i+(1<<k-1)]);
}

int getlcp (int i, int j) {
	i = rk[i], j = rk[j];
	if (i>j) swap(i, j);
	i ++;
	int f = lg2 (j-i+1);
	return min (st[f][i], st[f][j-(1<<f)+1]);
}

int main () {
	scanf ("%s" , s) ;
	da (s , strlen(s)+1) ;
	return 0 ;
}
