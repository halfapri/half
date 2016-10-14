#include <stdio.h>
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
const int MOD=91250681,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

int tim[55];

int main () {
	freopen ("read.txt", "w", stdout);
	srand (time(0));
	int team_num = rand()%17 + 1, problem_num = rand()%10 + 1;
	int ask_num = 70;
	for (int i=0; i<ask_num; i++) tim[i] = rand()%2333; 
	sort (tim, tim+ask_num);
	printf ("%d %d\n", team_num, problem_num);
	for (int i=0; i<ask_num; i++) {
		int op = rand()%3;
		if (op==0) {
			printf ("S %d:%d:%c:%d\n", tim[i],rand()%team_num,
					'A'+rand()%problem_num,rand()%2);
		} else if (op==1) {
			printf ("T %d\n", rand()%team_num+1);
		} else {
			printf ("R %d\n", rand()%team_num);
		}
	}
	puts ("Contest Ends");
	return 0;
}
