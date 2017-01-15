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
const int mod = 4;
const int aa[9][10] = {
	{1,1,0,1,0,0,0,0,0, 0},
	{1,1,1,0,1,0,0,0,0, 0},
	{0,1,1,0,0,1,0,0,0, 0},
	{1,0,0,1,1,0,1,0,0, 0},
	{1,0,1,0,1,0,1,0,1, 0},
	{0,0,1,0,1,1,0,0,1, 0},
	{0,0,0,1,0,0,1,1,0, 0},
	{0,0,0,0,1,0,1,1,1, 0},
	{0,0,0,0,0,1,0,1,1, 0}
};

inline int getlcm (int a,int b) {
	return a/__gcd(a,b)*b;
}

inline void add (int &a,int b) {
	a += b; if (a>=mod) a-=mod; if(a<0) a+=mod;
}

void Gauss (mat &a) {
	int equ=SZ(a), var=SZ(a[0])-1;
	int i,j,k,col,max_r;
	int ta, tb, LCM;

	//beg
	//for (int i=0; i<equ; i++) {
	//	for (int j=0; j<var+1; j++) {
	//		printf ("%d ", a[i][j]);
	//	} puts("");
	//} puts("");
	//end
	
	for (k=col=0; k<equ && col<var; k++, col++) {
		for (max_r=k, i=k; i<equ; i++) if (a[i][col]>a[max_r][col] && a[i][col]!=2) {
			max_r=i;
		}
		if (max_r!=k) swap(a[max_r],a[k]);
		if (a[k][col]==0) {
			k--; continue;
		}
		for (i=k+1; i<equ; i++) if (a[i][col]) {
			LCM = getlcm(abs(a[i][col]), abs(a[k][col]));
			ta = LCM/abs(a[i][col]);
			tb = LCM/abs(a[k][col]);
			if (a[i][col]<0 || a[k][col]<0) tb = -tb;
			for (j=col; j<var+1; j++) {
				a[i][j] = ((a[i][j]*ta-a[k][j]*tb)%mod+mod)%mod;
			}
		}
	}

	//beg
	//for (int i=0; i<equ; i++) {
	//	for (int j=0; j<var+1; j++) {
	//		printf ("%d ", a[i][j]);
	//	} puts("");
	//} puts("");
	//end
	
	vec x(var);
	vec ans;
	int tmp;
	for (i=k-1; i>=0; i--) {
		tmp = a[i][var];
		for (j=i+1; j<var; j++) if (a[i][j]) {
			add (tmp, -(a[i][j]*x[j])%mod);
		}
		//beg
		//printf ("a[%d][%d]=%d,tmp=%d\n",i,i,a[i][i],tmp);
		//end
		while (x[i]*a[i][i]%mod!=tmp) x[i]++;
		//beg
		//printf ("x[%d]=%d\n", i,x[i]);
		//end
		for (j=0; j<x[i]; j++) ans.push_back (i+1);
	}
	//beg
	//for (int i=0; i<var; i++) printf ("%d,",x[i]); puts("");
	//end
	for (i=SZ(ans)-1; i>=0; i--) printf ("%d%c", ans[i], " \n"[i==0]);
}

int main () {
	int x;
	while (~scanf("%d", &x)) {
		mat a(9,vec(10));
		for (int i=0; i<9; i++)
			for (int j=0; j<10; j++)
				a[i][j] = aa[i][j];
		a[0][9] = (mod-x)%mod;
		for (int i=1; i<9; i++) {
			scanf ("%d", &x);
			a[i][9] = (mod-x)%mod;
		}
		Gauss (a);
	}
	return 0;
}
