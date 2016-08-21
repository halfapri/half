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

const int M = 100000+110;
int sa[M], h[M], rk[M], st[18][M], n;
vector<int> len;
char s[M];
int is[M];

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
		memset (c, 0, sizeof(int)*m);
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
	memcpy (st[0], h, sizeof(h[0])*n);
	for (k=1; 1<<k<=n; k++)
		for (i=0; i+(1<<k)-1<n; i++)
			st[k][i] = min (st[k-1][i], st[k-1][i+(1<<k-1)]);
}

int getlcp (int i,int j) {
	int f = lg2(j-i+1);
	return min (st[f][i], st[f][j-(1<<f)+1]);
}

int getss (int x) {
	return lower_bound(ALL(len),x)-len.begin();
}

bool judge (int x) {
	int ss[111];
	memset (ss, 0, sizeof(ss[0])*(n+1));
	int l=1, sz=1, cnt=1;
	ss[getss(sa[1])] ++;
	for (int i=2; i<=len[n]; i++) {
		sz ++;
		int f = getss(sa[i]);
		if (ss[f] ++==0) cnt ++;
		while (sz>1 && getlcp(l+1,i)<x) {
			f = getss(sa[l]);
			if (-- ss[f]==0) cnt --;
			l++, sz--;
		}
		//printf ("l=%d,sz=%d,cnt=%d,x=%d\n",l,sz,cnt,x);
		if (sz>1 && cnt>n/2) return true;
	}
	return false ;
}

void solve () {
	int l=1, r=len[n], ret=-1;
	while (l<=r) {
		int mid = l+r>>1;
		if (judge (mid)) ret = mid, l=mid+1;
		else r = mid-1;
	}
	//printf ("ret=%d\n", ret);
	if (ret == -1) { puts ("?"); return;}
//////////////////////////////////////////////////////////////////
	int ss[111];
	memset (ss, 0, sizeof(ss[0])*(n+1));
	vector<int> ans;
	l = 1;
	int sz=1, cnt=1;
	bool flag=0;
	ss[getss(sa[1])] ++;
	for (int i=2; i<=len[n]; i++) {
		sz ++;
		int f = getss (sa[i]);
		if (ss[f]++==0) cnt ++;
		while (sz>1 && getlcp(l+1,i)<ret) {
			f = getss (sa[l]);
			if (--ss[f]==0) cnt --;
			l++, sz--;
		}
		if (sz>1 && cnt>n/2 && !flag) ans.push_back (sa[i]),flag=1;
		if (!sz || cnt<=n/2) flag = 0;
	}
	//for (int i:ans) printf ("%d ", i); puts ("");
	for (int i=0; i<ans.size(); i++) {
		char ch = s[ans[i]+ret];
		s[ans[i]+ret] = '\0';
		printf ("%s\n", s+ans[i]);
		s[ans[i]+ret] = ch;
	}
}

int main () {
	//freopen ("read.txt", "r", stdin);
	int cas=1;
	while (~ scanf ("%d", &n) && n) {
		if (cas++ != 1) puts ("");
		len.resize (n+1);
		len[0] = -1;
		for (int i=0; i<n; i++) {
			scanf ("%s", s+len[i]+1);
			len[i+1] = strlen (s);
			s[len[i+1]] = 3;
		}
		s[len[n]] = '\0';
		for (int i=0,j=1; i<=len[n]; i++) {
			is[i] = s[i];
			if (i == len[j] && j!=n) is[i] = (j++)+128;
		}
		da (is, len[n]+1, 256);
		//puts (s);
		solve ();
	}
	return 0;
}
