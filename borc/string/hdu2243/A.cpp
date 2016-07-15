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

typedef vector<ull> vec ;
typedef vector<vec> mat ;
const int M = 30 ;
int n , l ;
char s[10] ;

mat mul (const mat &a , const mat &b) {
	mat ret(a.size(),vec(b[0].size())) ;
	for (int i=0 ; i<a.size() ; i++) 
		for (int j=0 ; j<b[0].size() ; j++)
			for (int z=0 ; z<b.size() ; z++)
				ret[i][j] += a[i][z]*b[z][j] ;
	return ret ;
}

struct AC {
	int go[M][26],fail[M],ed[M],ns,rt ; 
	void init () {
		ns = 0 ;
		rt = newnode() ;
	}
	int newnode () {
		memset (go[ns],-1,sizeof(go[ns])) ;
		ed[ns] = 0 ;
		return ns ++ ;
	}
	void Insert (char *s,int now=0) {
		if (! *s) { ed[now] = 1 ; return ;}
		int ch = *s-'a' ;
		if (go[now][ch]==-1) go[now][ch] = newnode() ;
		Insert (s+1 , go[now][ch]) ;
	}
	void get_fail () {
		queue<int> q ;
		for (int i=0 ; i<26 ; i++)
			if (go[rt][i]==-1) go[rt][i] = rt ;
			else {
				fail[go[rt][i]] = rt ;
				q.push (go[rt][i]) ;
			}
		while (!q.empty()) {
			int now = q.front() ; q.pop() ;
			ed[now] |= ed[fail[now]] ;
			for (int i=0 ; i<26 ; i++) 
				if (go[now][i]==-1) go[now][i] = go[fail[now]][i] ;
				else {
					fail[go[now][i]] = go[fail[now]][i] ;
					q.push (go[now][i]) ;
				}
		}
	}
	void get_mat (mat &b) {
		for (int i=0 ; i<ns*2 ; i++)  
			for (int j=0 ; j<26 ; j++)  
				if (i&1 || ed[go[i>>1][j]]) { 
					int son = go[i>>1][j]*2+1 ;
					b[son][i] ++ ; 
				} else if (!(i&1) && ed[go[i>>1][j]]==0) {
					int son = go[i>>1][j]*2 ;
					b[son][i] ++ ;
				}
		for (int i=0 ; i<ns*2 ; i++) 
			for (int j=1 ; j<ns*2 ; j+=2)
				b[b.size()-1][i] += b[j][i] ;
		b[b.size()-1][b.size()-1] = 1 ;
		//for (int i=0 ; i<b.size() ; i++) {
		//	for (int j=0 ; j<b[0].size() ; j++) {
		//		printf ("%3d" , b[i][j]) ;
		//	} puts ("") ;
		//} puts ("") ;
	}
} ac ;

int main () {
	while (~ scanf ("%d%d" , &n , &l)) {
		ac.init () ;
		for (int i=0 ; i<n ; i++) {
			scanf ("%s" , s) ;
			ac.Insert (s) ;
		}
		ac.get_fail() ;
		mat b(ac.ns*2+1 , vec(ac.ns*2+1)) ;
		ac.get_mat (b) ;
		mat a(b.size() , vec(1)) ;
		a[0][0] = 1 ;
		mat ans(b.size() , vec(b.size())) ;
		for (int i=0 ; i<ans.size() ; i++) ans[i][i] = 1 ;
		for ( ; l ; l>>=1) {
			if (l&1) ans = mul (ans , b) ;
			b = mul (b , b) ;
		}
		ans = mul (ans , a) ;
		printf ("%I64u\n" , ans[ans.size()-1][0]) ;
	}
	return 0 ;
}
