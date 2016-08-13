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

typedef pair<int,int> pii;
const int M=100000+10;
int n, k;
pii b[M];

void solve (int p) {
	int l=0, sz=1;
	ll minn = INF;
	pii ans, f;
	for (int i=1; i<n; i++) {
		sz ++;
		int dif = b[i].fi-b[l].fi;
		if (dif > p) {
			while (sz>1 && (dif=b[i].fi-b[l].fi) >p) {
				if (dif-p < minn) {
					minn = dif-p;
					ans = MP(b[l].se,b[i].se);
					f = MP(l, i);
				}
				l++, sz--;
			}
		}
		if (sz>1) {
			dif = b[i].fi-b[l].fi;
			if (p-dif < minn) {
				minn = p-dif;
				ans = MP(b[l].se,b[i].se);
				f = MP(l, i);
			}
		}
	}
	if (ans.fi>ans.se) swap(ans.fi,ans.se);
	printf ("%d %d %d\n", b[f.se].fi-b[f.fi].fi,
			ans.fi+1, ans.se);
}

int main () {
//	freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d%d", &n, &k) && n+k) {
		memset (b, 0, sizeof(b[0])*(n+1));
		for (int i=1; i<=n; i++) { int x;
			scanf ("%d", &b[i].fi);
			b[i].fi += b[i-1].fi;
			b[i].se = i;
		}
		n ++ ;
		sort (b, b+n);
		while (k --) { int t;
			scanf ("%d", &t);
			solve (t);
		}
	}
	return 0;
}
