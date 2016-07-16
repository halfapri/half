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
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
int sign(double x){return x<-eps?-1:x>eps;}

int as ;
int arr[111] ;
int a[111] ;
int n ;
int sb[66] ;
struct DP {
	int x , nxt , val;
} dp[100][1<<17] ;

bool judge (int x) {
	for (int i=2 ; i<=x/i ; i++) 
		if (x%i==0) return false ;
	return true ;
}

int get (int x,int ret=0) {
	if (x==1) return 0 ;
	for (int i=0 ; i<as ; i++)
		if (x%arr[i]==0) ret|=1<<i ;
	return ret ;
}

void init () {
	for (int i=2 ; i<=60 ; i++) {
		if (judge(i)) arr[as++] = i ;
	}
	for (int i=0 ; i<n ; i++) { 
		for (int j=0 ; j<(1<<17) ; j++) { 
			dp[i][j].nxt = -1 ;
			dp[i][j].val = inf ;
		}
	}
	for (int i=1 ; i<=60 ; i++) {
		sb[i] = get(i) ;
		if(abs(i-a[0])<dp[0][sb[i]].val) {
			dp[0][sb[i]].val = abs(i-a[0]) ;
			dp[0][sb[i]].x = i ;
		}
	}
}

void dfs (int deep,int now) {
	if (now==-1) return ;
	dfs (deep-1 , dp[deep][now].nxt) ;
	printf ("%d " , dp[deep][now].x) ;
}

int main () {
	scanf ("%d" , &n) ;
	for (int i=0 ; i<n ; i++) scanf ("%d" , a+i) ;
	init () ;
	for (int i=1 ; i<n ; i++) {
		for (int j=0 ; j<(1<<17) ; j++) {
			if (dp[i-1][j].val==inf) continue ;
			for (int z=1 ; z<=60 ; z++) {
				if (j&sb[z]) continue ;
				if (dp[i][j|sb[z]].val > dp[i-1][j].val+abs(a[i]-z)) {
					dp[i][j|sb[z]].val = dp[i-1][j].val+abs(a[i]-z) ;
					dp[i][j|sb[z]].nxt = j ;
					dp[i][j|sb[z]].x = z ;
				}
			}
		}
	}
	int ans = inf , beg ;
	for (int i=0 ; i<(1<<17) ; i++) {
		if (dp[n-1][i].val<ans) {
			ans = dp[n-1][i].val ;
			beg = i ;
		}
	}
	dfs (n-1,beg) ;
	return 0 ;
}
