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
const int MOD=(int)1e9+7,BAS=233;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}
int AP (char *s) {
	unsigned hash=0;
	for(int i=0; s[i]; i++){
		if (i & 1) hash ^= (~((hash<<11)^s[i]^(hash>>5)));
		else hash ^= ((hash<<7)^s[i]^(hash>>3));
   } return hash & 0x7FFFFFFF;
}

const int M = 20;
typedef vector<int> vec;
typedef vector<vec> mat;
//我们对矩阵的每个位置列方程,得到n*n个方程,但是经过观察可以发现
//其实只要用第一行的n个未知数即可来表示所有的方程,并且我们可以只
//关心最后一行的n个位置对应的方程都为变成'y'的状态:
//这样实际上只要n个方程,第一行的n个未知元即可解决了.
bool var2[M][M][M];
//var2(i,j,k):表示(i,j)这个位置的状态用第一行的n个x(i)来表示的话,对应x(k)的系数,从而使得(i-1,j)这个格子为'y'
bool var[M][M];
//var(i,j):表示(i,j)这个位置的状态的常数项
char s[M][M];
int n;
int step[4][2] = {{0,1},{0,-1},{0,0},{-1,0}};

void debug (mat &a) {
	for (int i=0; i<SZ(a); i++) {
		for (int j=0; j<SZ(a[0]); j++) {
			printf ("%d%c", a[i][j], " \n"[j==SZ(a[0])-1]);
		}
	} puts ("");
}

int Gauss (mat &a) {
	int equ=SZ(a), var=SZ(a[0])-1;
	int k, col;
	int i, j, max_r;
	//beg
	//debug (a);
	//end
	for (k=col=0; k<equ && col<var; k++, col++) {
		for (max_r=k, i=k; i<equ; i++) if (a[i][col]) {
			max_r=i; break;
		}
		if (max_r!=k) swap(a[max_r], a[k]);
		if (a[k][col]==0) {
			k--; continue;
		}
		for (i=k+1; i<equ; i++) if (a[i][col]) {
			for (int j=col; j<var+1; j++) a[i][j] ^= a[k][j];
		}
		//beg
		//debug (a);
		//end
	}

	for (i=k; i<equ; i++) if (a[i][col]) {
		return -1;
	}
	return var-k;
}

void debug_Paint () {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			printf ("(%d,%d):", i, j);
			for (int z=0; z<n; z++) printf ("%d ", var2[i][j][z]);
			printf ("=%d\n", var[i][j]);
		}
	}
}

int Paint (vec &x) {
	//beg
	//debug_Paint ();
	//end
	int ret=0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			int tmp=0;
			for (int z=0; z<n; z++) tmp ^= var2[i][j][z]*x[z];
			tmp ^= var[i][j];
			ret += tmp&1;
		}
	}
	//beg
	//printf ("ret=%d\n", ret);
	//end
	return ret;
}

void solve () {
	mat a(n, vec(n+1));
	for (int i=0; i<n; i++) for (int j=0; j<n; j++) {
		a[i][j] = var2[n][i][j];
	}
	for (int i=0; i<n; i++) a[i][n] = var[n][i];
	int ans = Gauss (a);
	if (ans==-1) puts ("inf");
	else {
		vec x(n);
		int minn = inf;
		//beg
		//printf ("ans=%d\n", ans);
		//end
		for (int S=0; S<1<<ans; S++) {
			for (int i=0; i<ans; i++) x[n-i-1] = S>>i & 1;
			for (int i=n-ans-1; i>=0; i--) {
				x[i] = a[i][n];
				for (int j=i+1; j<n; j++) x[i] ^= a[i][j]*x[j];
			}
			//beg
			//for (int v: x) printf ("%d ", v); puts("");
			//end
			minn = min (Paint(x), minn);
		}
		printf ("%d\n", minn);
	}
}

int main () {
	int CASE; scanf ("%d", &CASE);
	while (CASE --) {
		scanf ("%d", &n);
		for (int i=0; i<n; i++) scanf ("%s", s+i);
		for (int i=0; i<n; i++) {
			var[0][i] = 0;
			var2[0][i][i] = 1;
		}
		for (int i=1; i<=n; i++) {
			for (int j=0; j<n; j++) {
				var[i][j] = s[i-1][j]!='y';
				memset (var2[i][j], 0, sizeof(bool)*n);
				for (int z=0; z<4; z++) {
					int x = i-1+step[z][0], y = j+step[z][1];
					if (x<0||y<0||x==n||y==n) continue;
					var[i][j] ^= var[x][y];
					for (int f=0; f<n; f++) {
						var2[i][j][f] ^= var2[x][y][f];
					}
				}
			}
		}
		solve();
	}
	return 0;
}
