#include <bits/stdc++.h>
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
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
int sign(double x){return x<-eps?-1:x>eps;}

const int M = (int)1e5+10 ;
int n , m ;
int T[M] ;
struct EDGES {
	int u , nxt ;
	EDGES(int _u=0,int _nxt=0):u(_u),nxt(_nxt){}
}edge[M] ;
int head[M<<1] , E;
vector<int> pt ;

void solve () {
	set<pair<int,int> > steins ;
	set<int> cur ;
	int ret = 0 ;
	for (int i=0 ; i<m ; i++) { 
		steins.insert (MP(head[i]==-1?inf:edge[head[i]].u,i)) ;
		cur.insert (i) ;
	}
	for (int i=0 ; i<n ; i++) {
		if (cur.count(T[i])) {
			steins.erase(MP(head[T[i]]==-1?inf:edge[head[T[i]]].u,T[i])) ;
			if (head[T[i]]!=-1) head[T[i]] = edge[head[T[i]]].nxt ;
			steins.insert (MP(head[T[i]]==-1?inf:edge[head[T[i]]].u,T[i])) ;
		} else {
			ret ++ ;
			if (head[T[i]]!=-1) head[T[i]] = edge[head[T[i]]].nxt ;
			steins.insert (MP(head[T[i]]==-1?inf:edge[head[T[i]]].u,T[i])) ;
			cur.insert (T[i]) ;
			auto it = steins.end(); --it ;
			cur.erase(it->se) ;
			steins.erase(it) ;
		}
	}
	printf ("%d\n" , ret) ;
}

int main () {
	while (~ scanf ("%d%d",&n,&m)) {
		memset (head , -1 , sizeof(head)) ;
		pt.clear () ;
		for (int i=0 ; i<n ; i++) {
			scanf ("%d" , T+i) ;
			pt.push_back (T[i]) ;
		}
		for (int i=1 ; i<=m ; i++) {
			pt.push_back (i) ;
		}
		sort (pt.begin(),pt.end()) ;
		pt.erase(unique(pt.begin(),pt.end()),pt.end()) ;
		E=0 ;
		auto addedge = [](int u,int v) {
			edge[E] = EDGES(v,head[u]) ;
			head[u] = E ++ ;
		} ;
		for (int i=n-1 ; i>=0 ; i--) { 
			T[i] = lower_bound(pt.begin(),pt.end(),T[i])-pt.begin();
			addedge(T[i],i) ;
		}
		solve () ;
	}
	return 0 ;
}
