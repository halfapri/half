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
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;

const int M = (int)1e5+10 ;
struct SAM {
	int go[M][26] ,len[M] , par[M] , root , oL , last ;

	int newnode (int l) {
		for (int i=0 ; i<26 ; i++) go[oL][i] = -1 ;
		len[oL] = l ;
		return oL ++ ;
	}

	void init() {
		oL = last = 0 ;
		par[oL] = -1 ;
		root = newnode (0) ;
	}

	void Insert (char v) {
		v -= 'a' ;
		int p = last ;
		int np = newnode (len[p]+1) ;
		while (p!=-1 && go[p][v]==-1) 
			go[p][v] = np , p = par[p] ;
		if (p==-1)
			par[p] = root ;
		else {
			q = go[p][v] ;
			if (len[q] == len[p]+1)
				par[np] = q ;
			else {
				int nq = newnode(len[p]+1) ;
				memcpy (go[nq] , go[q] , sizeof(go[q])) ;
				par[nq] = p ;
				par[q] = nq ;
				par[np] = nq ;
				while (p!=-1 && go[p][v]==q) 
					go[p][v]=nq , p=par[p] ;
			}
		}
	}
} ;
