#include <stdio.h>
#include <numeric>
#include <time.h>
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
#include <limits.h>
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
#define SZ(x) ((int)x.size())
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
#define sqr(x) ((x)*(x))
#define ALL(v) (v).begin(),(v).end()
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=91250681,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 1000+10;
int a[M], dp[M][1<<8], lst[M][8][126];
bool vis[8];
int maxn;
int n;

int main () {
	scanf ("%d", &n);
	maxn = 0;
	for (int i=1; i<=n; i++) {
		scanf("%d", a+i), a[i]--;
		if (!vis[a[i]]) vis[a[i]]=true, maxn ++;
	}
	int C = n/8+1;
	for (int i=1; i<=n; i++) {
		for (int j=0; j<8; j++) {
			if (j==a[i]) {
				lst[i][j][1] = i;
				for (int c=1; c<C; c++) {
					lst[i][j][c+1] = lst[i-1][j][c];
				}
			} else {
				for (int c=1; c<=C; c++) {
					lst[i][j][c] = lst[i-1][j][c];
				}
			}
		}
	}

	for (int c=2; c<=C; c++) {
		for (int i=0; i<=n; i++)
			for (int s=0; s<1<<8; s++)
				dp[i][s] = -1;
		dp[0][0] = 0;
		for (int i=1; i<=n; i++) {
			if (lst[i][a[i]][c-1]) {
				int x = lst[i][a[i]][c-1]-1;
				int S = ~(1<<a[i]) & ((1<<8)-1);
				for (int s=S; ; s=(s-1)&S) {
					if (dp[x][s]==-1) continue;
					dp[i][s|1<<a[i]] = max(dp[i][s|1<<a[i]],
						dp[x][s] + c-1);
					if (s==0) break;
				}
			}
			if (lst[i][a[i]][c]) {
				int x = lst[i][a[i]][c]-1;
				int S = ~(1<<a[i]) & ((1<<8)-1);
				for (int s=S; ; s=(s-1)&S) {
					if (dp[x][s]==-1) continue;
					dp[i][s|1<<a[i]] = max(dp[i][s|1<<a[i]],
						dp[x][s] + c);
					if (s==0) break;
				}
			}
			for (int s=0; s<1<<8; s++) if (dp[i-1][s]!=-1) {
				dp[i][s] = max(dp[i][s], dp[i-1][s]);
			}
		}
		maxn = max(maxn, dp[n][(1<<8)-1]);
	}

	printf ("%d\n", maxn);
	return 0;
}
