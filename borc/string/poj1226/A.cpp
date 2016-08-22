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

const int M = 100000;
int sa[M], rk[M], h[M];

void da (int *s,int n,int m) {
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
}

int is[M], n;
char s[111];
vector<int> len;

int getss (int x) {
	return lower_bound (ALL(len),x)-len.begin();
}

bool judge (int x) {
	int ss[111];
	memset (ss, 0, sizeof(ss[0])*(n+1));
	int l=1, sz=1, cnt=1;
	ss[getss(sa[1])] ++;
	for (int i=2; i<=len[n]; i++) {
		sz ++;
		if (ss[getss(sa[i])]++==0) cnt++;
		while (sz>1 && h[i]<x) {
			if (--ss[getss(sa[l])]==0) cnt--;
			l ++, sz--;
		}
		if (sz>1 && cnt>=n) return true;
	}
	return false;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	int CASE ;
	scanf ("%d", &CASE);
	while (CASE --) {
		scanf ("%d", &n);
		len.resize (n+1);
		len[0] = -1;
		for (int i=1,t=128,j=0; i<=n; i++) {
			scanf ("%s", s);
			for (int z=0; s[z]; z++) is[j++] = s[z];
			is[j++] = t++;
			for (int z=strlen(s)-1; z>=0; z--) is[j++] = s[z];
			len[i] = j;
			is[j++] = t++;
		}
		is[len[n]] = 0;
		da (is, len[n]+1, 256);
		//printf ("len[n]=%d\n", len[n]);
		//for (int i=0; i<len[n]; i++) printf ("%4d", i); puts("");
		//for (int i=0; i<len[n]; i++) printf("%4d", is[i]);puts("");
//////////////////////////////////////////////////////////////////
		int l=1, r=len[n], ret=0;
		while (l<=r) {
			int mid = l+r>>1;
			if (judge (mid)) ret=mid, l=mid+1;
			else r=mid-1;
		}
		printf ("%d\n", ret);
	}
	return 0;
}
