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

struct VC:vector<int> {
	void done () {
		sort (begin(),end());
		erase(unique(begin(),end()),end());
	}
	int get (int x) {
		return lower_bound(begin(),end(),x)-begin()+1;
	}
}ss;
int n;
int s[M], st[19][M];

int work (int sz) {
	da (s, sz+1, ss.size()+1);
	for (int i=1; i<=sz; i++) {
		if (sa[i]>1) {
			for (int j=sa[i]; j<sz; j++) 
				printf ("%d\n", ss[s[j]-1]);
			return sa[i];
		}
	}
}

int getlcp (int i,int j) {
	int f = lg2(j-i+1);
	return min (st[f][i], st[f][j-(1<<f)+1]);
}

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d", &n);
	ss.resize(n);
	for (int i=0; i<n; i++) {
		scanf ("%d", s+i);
		ss[i] = s[i];
	}
	ss.done();
	reverse (s, s+n);
	for (int i=0; i<n; i++) s[i] = ss.get(s[i]);
	s[n] = 0;
	///////////////////////////////////////////////////////////////
	n = work (n);
	s[n] = 0;
	da (s, n+1, ss.size()+1);
	memcpy (st[0], h, sizeof(h[0])*(n+1));
	for (int k=1; 1<<k<=n+1; k++) 
		for (int i=0; i+(1<<k)-1<n+1; i++)
			st[k][i] = min (st[k-1][i], st[k-1][i+(1<<k-1)]);
	int ans=0;
	for (int i=1, flag=-1; i<=n; i++) {
		if (sa[i]==0) continue;
		if (flag == -1) { flag = 1;
			ans = i;
		} else {
			int lcp = getlcp (ans+1, i);
			if (sa[ans]+lcp<n) break;
			if (rk[sa[i]+lcp]<rk[0]) ans = i;
			else break;
		}
	}
	for (int i=sa[ans]; i<n; i++) printf ("%d\n", ss[s[i]-1]);
	for (int i=0; i<sa[ans]; i++) printf ("%d\n", ss[s[i]-1]);
	return 0;
}
