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

const int M = 5000+5, mod = (int)1e9+7;
int rk[M], sa[M], h[M], st[14][M];

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
		for (i=0; i<n; i++) c[x[i]]++;
		for (i=1; i<m; i++) c[i] += c[i-1];
		for (i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i];
		for (swap(x,y), x[sa[0]]=0, p=i=1; i<n; i++)
			x[sa[i]] = y[sa[i]] == y[sa[i-1]] &&
				y[sa[i]+k] == y[sa[i-1]+k] ? p-1 : p++;
	}
	memcpy (rk, x, sizeof(x[0])*n);
	for (i=0, k=0; i<n-1; h[rk[i++]] = k?k--:k)
		for (j=sa[rk[i]-1]; s[i+k] == s[j+k]; k++);
	memcpy (st[0], h, sizeof(h[0])*n);
	for (k=1; 1<<k<=n; k++)
		for (i=0; i+(1<<k)-1<n; i++)
			st[k][i] = min (st[k-1][i], st[k-1][i+(1<<k-1)]);
}

int getlcp (int i,int j) {
	i = rk[i], j=rk[j];
	if (i>j) swap(i, j);
	i ++;
	int f = lg2 (j-i+1);
	return min (st[f][i], st[f][j-(1<<f)+1]);
}

int dp[M][M], pre[M][M], n;
char s[M];

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d%s", &n, s);
	da (s, n+1, 128);
//////////////////////////////////////////////////////////////////
	auto add = [](int &a,int b) {
		a += b; if (a<0) a+=mod; if(a>=mod) a-=mod;
	};
	auto bigger = [&](int i,int j,int len) {
		int lcp = getlcp (i, j);
		return lcp>=len ? 0 : s[i+lcp]>s[j+lcp];
	};
//////////////////////////////
	for (int i=1; i<=n; i++) 
		dp[0][i] = 1, pre[0][i-1] = 1;
	for (int i=1; i<n; i++) { if (s[i]!='0') {
			for (int j=1; i-j>=0 && i+j<=n; j++) {
				if (bigger (i,i-j,j)) 
					add (dp[i][j], pre[i-j][i-1]);
				else
					add (dp[i][j], pre[i-j+1][i-1]);
				add (pre[i][i+j-1], dp[i][j]);
			}
			for (int j=i+1; i+j<=n; j++) {
				add (dp[i][j], pre[0][i-1]);
				add (pre[i][i+j-1], dp[i][j]);
			}
		}
		for (int j=i-1; j>=0; j--) add(pre[j][i], pre[j+1][i]);
	}
	printf ("%d\n", pre[0][n-1]);
	return 0;
}
