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

typedef vector<int> vec;
typedef vector<vec> mat;

int idx (char *s) {
	if (strcmp(s, "MON")==0) return 0;
	if (strcmp(s, "TUE")==0) return 1;
	if (strcmp(s, "WED")==0) return 2;
	if (strcmp(s, "THU")==0) return 3;
	if (strcmp(s, "FRI")==0) return 4;
	if (strcmp(s, "SAT")==0) return 5;
	if (strcmp(s, "SUN")==0) return 6;
}

int get (char *s, char *t) {
	int tmp = (idx(t)-idx(s)+1)%7;
	if (tmp<0) tmp += 7;
	return tmp;
}

int n, m;
char s[2][10];

inline int lcm (int x,int y) {
	return x/__gcd(x,y)*y;
}

inline int inv (int x) {
	int ret=1;
	for (int i=5; i; i>>=1) {
		if (i&1) ret=ret*x%7;
		x=x*x%7;
	} return ret;
}

inline void add (int &a,int b) {
	a += b; if (a<0) a += 7; if (a>=7) a-=7;
}

int Gauss (mat &a, vec &x) {
	int equ = SZ(a), var = SZ(a[0])-1;
	vec free_x(var, 1);
	int free_x_num, free_index;
	int i, j, k, col, max_r;
	int LCM, ta, tb, temp;

	//beg
	//puts ("Gauss_start:");
	//for (int i=0; i<equ; i++) {
	//	for (int j=0; j<var+1; j++) {
	//		printf ("%d ", a[i][j]);
	//	} puts("");
	//}puts ("");
	//end

	for (k=col=0; k<equ && col<var; k++, col++) {
		for (max_r=k, i=k+1; i<equ; i++) if (a[i][col]>a[max_r][col]) {
			max_r=i;
		}
		if (max_r!=k) swap(a[max_r], a[k]);
		if (a[k][col]==0) {
			k--; continue;
		}
		for (i=k+1; i<equ; i++) if (a[i][col]) {
			LCM = lcm(abs(a[k][col]), abs(a[i][col]));
			ta = LCM/abs(a[i][col]);
			tb = LCM/abs(a[k][col]);
			if (a[i][col]<0 || a[k][col]<0) tb = -tb;
			for (j=col; j<var+1; j++) {
				a[i][j] = (a[i][j]*ta-a[k][j]*tb)%7;
				if (a[i][j]<0) a[i][j]+=7;
			}
		}
	}

	//beg
	//printf ("col=%d, k=%d\n", col, k);
	//puts ("Gauss_end:");
	//for (int i=0; i<equ; i++) {
	//	for (int j=0; j<var+1; j++) {
	//		printf ("%d ", a[i][j]);
	//	} puts("");
	//}puts ("");
	//end

	for (i=k; i<equ; i++) if (a[i][col]) {
		return -1;
	}

	if (k<var) return var-k;//有自由元,必定存在正整数解

	for (i=var-1; i>=0; i--) {
		temp = a[i][var];
		for (j=i+1; j<var; j++) if (a[i][j]) {
			add(temp, -a[i][j]*x[j]%7);
		}
		x[i] = temp*inv(a[i][i])%7;
		if (x[i]<3) x[i] += 7;
	}

	return 0;
}

int main () {
	while (~scanf("%d%d",&n,&m) && n+m) {
		mat a(m, vec(n+1));
		vec x(n);
		for (int i=0, k, x; i<m; i++) {
			scanf ("%d%s%s", &k, s[0], s[1]);
			a[i][n] = get(s[0],s[1]);
			for (int j=0; j<k; j++) {
				scanf ("%d", &x);
				add(a[i][--x], 1);
			}
		}
		int ans = Gauss (a, x);
		if (ans==-1) puts ("Inconsistent data.");
		else if (ans) puts ("Multiple solutions.");
		else {
			for (int i=0; i<n; i++) {
				printf ("%d%c", x[i], " \n"[i==n-1]);
			}
		}
	}
	return 0;
}