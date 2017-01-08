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

const int M = 31;
bitset<M> a[M];
bool free_x[M], x[M];
int step[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};

void Gauss (int equ,int var) {
	int i,j,k;
	int col, max_r;
	int free_x_num;
	int free_index;
	bool temp;

	for (int i=0; i<var; i++) {
		free_x[i] = true;
		x[i] = false;
	}

	for (k=0,col=0; k<equ && col<var; k++, col++) {
		for (max_r=k, i=k; i<equ; i++) if (a[i].test(col)) {
			max_r=i; break;
		}
		if (max_r!=k) swap(a[max_r], a[k]);
		if (!a[k].test(col)) {
			k--; continue;
		}
		for (int i=k+1; i<equ; i++) if (a[i].test(col)) {
			a[i] = a[i]^a[k];
		}
	}
	for (i=k-1; i>=0; i--) {
		free_x_num=0;
		for (j=0; j<var; j++) if (a[i].test(j) && free_x[j]) {
			free_x_num ++;
			free_index = j;
		}
		if (free_x_num>1) continue;
		temp = a[i].test(var);
		for (j=0; j<var; j++) if (a[i].test(j) && j!=free_index) {
			temp ^= x[j];
		}
		x[free_index] = temp;
		free_x[free_index] = false;
	}
}

int main () {
	int CASE; scanf ("%d", &CASE);
	for (int cas=1; cas<=CASE; cas++) {
		for (int i=0; i<30; i++) a[i].reset();
		for (int i=0, x; i<5; i++) {
			for (int j=0; j<6; j++) {
				scanf ("%d", &x);
				int id = i*6+j;
				if (x) a[id].set(30);
				a[id].set(id);
				for (int z=0; z<4; z++) {
					int x = i+step[z][0], y = j+step[z][1];
					if (x<0 || y<0 || x==5 || y==6) continue;
					a[id].set(x*6+y);
				}
			}
		}
		Gauss (30, 30);
		printf ("PUZZLE #%d\n", cas);
		for (int i=0; i<30; i++) {
			int y = i%6;
			printf ("%d%c", x[i], " \n"[y==5]);
		}
	}
	return 0;
}
