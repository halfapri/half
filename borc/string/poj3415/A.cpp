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

const int M = 200000+10;
int sa[M], h[M], rk[M], n, m, K;
char s[M];

void da (char *s,int n,int m) {
	static int t1[M], t2[M], c[M];
	int *x=t1, *y=t2, i,j,k,p=1;
	memset (c, 0, sizeof(c[0])*m);
	for (i=0; i<n; i++) c[x[i]=s[i]] ++;
	for (i=1; i<m; i++) c[i] += c[i-1];
	for (i=n-1; i>=0; i--) sa[--c[x[i]]] = i;
	for (k=1; p<n; k<<=1, m=p) {
		for (p=0, i=n-k; i<n; i++) y[p++] = i;
		for (i=0; i<n; i++) if (sa[i]>=k) y[p++] = sa[i]-k;
		memset (c, 0, sizeof(c[0])*m);
		for (i=0; i<n; i++) c[x[i]] ++;
		for (i=1; i<m; i++) c[i] += c[i-1];
		for (i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i];
		for (swap(x,y), x[sa[0]]=0, p=i=1; i<n; i++)
			x[sa[i]] = y[sa[i]] == y[sa[i-1]] &&
				y[sa[i]+k] == y[sa[i-1]+k] ? p-1 : p++;
	}
	memcpy (rk, x, sizeof(x[0])*n);
	for (i=0, k=0; i<n-1; h[rk[i++]] = k?k--:k) 
		for (j=sa[rk[i]-1]; s[i+k] == s[j+k]; k++);
}

int pre[M];
ll dp[M];

ll solve (bool flag,ll ret=0) {
	for (int i=2; i<=n; i++) 
		if (flag) pre[i] = (sa[i]<m) + pre[i-1];
		else pre[i] = (sa[i]>m) + pre[i-1];
	stack<int> q;
	for (int i=2; i<=n; i++) {
		if (h[i]<K)  dp[i] = 0;
		else {
			while (!q.empty() && h[i]<=h[q.top()]) q.pop();
			dp[i] = dp[q.top()]+1ll*(pre[i]-pre[q.top()-1])*(h[i]-K+1); 
			if (h[q.top()]>=K) {
				if (flag) dp[i] -= sa[q.top()]<m?h[q.top()]-K+1:0;
				if (!flag) dp[i] -= sa[q.top()]>m?h[q.top()]-K+1:0;
			}
			if (flag && (sa[i]>m)) ret += dp[i];
			if (!flag && (sa[i]<m)) ret += dp[i];
		}
		q.push (i);
	}
	return ret;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d", &K) && K) {
		scanf ("%s", s);
		m = strlen (s);
		s[m] = '#';
		scanf ("%s", s+m+1);
		n = strlen (s);
		da (s, n+1, 128);
		printf (LLD"\n", solve(0) + solve(1));
	}
	return 0;
}

