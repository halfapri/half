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

const int M = (int)5e4+10 ;
int n ;
bool vis[M] ;
int f[M] , s[M] ;
bool cmp (const pair<int,int>&a , const pair<int,int>&b) {
	if (a.fi==b.fi) return a.se<b.se ;
	return a.fi>b.fi ;
}

int main () {
	int CASE ;
	scanf ("%d" , &CASE) ;
	for (int cas=1 ; cas<=CASE ; cas++) {
		printf ("Case #%d:\n" , cas) ;
		vector<int> vc ;
		vector<pair<int,int> > pt ;
		scanf ("%d" , &n) ;
		memset (vis , false , sizeof(bool)*(n+10)) ;
		for (int i=0 ; i<n ; i++) scanf ("%d%d" , f+i,s+i) ;
		for (int i=1 ; i<=501 ; i++) {
			int maxn = -1 , id = -1 ;
			for (int j=0 ; j<n ; j++) { if(vis[j]) continue ;
				if (f[j]+(i-1)*s[j]>maxn) {
					maxn = f[j]+(i-1)*s[j] ;
					id = j ;
				}
			}
			if (id==-1) continue ;
			vis[id]=1 ;
			vc.push_back (id) ;
		}
		for (int i=0 ; i<n ; i++) { if(vis[i]) continue ;
			pt.push_back (MP(f[i]+501*s[i],i)) ;
		}
		sort (pt.begin(),pt.end(),cmp) ;
		for (pair<int,int> i:pt) vc.push_back(i.se) ; 
		for (int i=0 ; i<vc.size() ; i++) printf ("%d%c",vc[i]+1," \n"[i==vc.size()-1]) ;
	}
	return 0 ;
}
