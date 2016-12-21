#include <stdio.h>
#include <string.h>
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
int sign(double x){return x<-eps?-1:x>eps;}

const int M = 100000+10 ;
int in[M] , n , m ;
vector<int> pt ;
vector<int> g[M] ;
void topo () {
	priority_queue<int> q ;
	for (int i=1 ; i<=n ; i++) {
		if (in[i]==0) q.push (i) ;
	}
	while (!q.empty()) {
		int cur = q.top() ; q.pop() ;
		pt.push_back (cur) ;
		for (int v : g[cur]) {
			if (--in[v]==0) {
				q.push(v) ;
			}
		}
	}
}

int main () {
	int CASE ;
	scanf ("%d" ,&CASE) ;
	while (CASE --) {
		scanf ("%d%d" , &n,&m) ; 
		memset (in , 0 , sizeof(in)) ;
		for (int i=0 ; i<=n ; i++) g[i].clear () ;
		for (int i=0,u,v; i<m ; i++) {
			scanf ("%d%d",&u,&v) ;
			g[u].push_back (v) ;
			in[v] ++ ;
		}
		pt.clear () ;
		topo () ;
		int minn = inf ;
		ll tot = 0 ;
		for (int i=0 ; i<n ; i++) {
			minn = min (minn , pt[i]) ;
			tot += minn ;
		}
		printf (LLD "\n" , tot) ;
	}
	return 0 ;
}
