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

struct Trie {
	const int M = 100000+10 ;
	int go[M][10] , fail[M] ;
	bool end[M] ;
	int o , root ;

	int newNode () {
		for (int i=0 ; i<10 ; i++)
			go[o][i] = -1 ;
		end[o] = false ;
		return o ++ ;
	}

	void Init () {
		o = 0 ;
		root = newNode() ;
	}

	void Insert (char *s) {
		int now = root ;
		for (; *s ; s ++) {
			if (go[now][*s-'0']==-1) 
				go[now][*s-'0'] = newNode () ;
			now = go[now][*s-'0'] ;
		}
		end[now] = true ;
	}

	void Build () {
		queue<int> q ;
		for (int i=0 ; i<10 ; i++) {
			if (go[root][i]==-1) 
				go[root][i] = root ;
			else {
				fail[go[root][i]] = root ;
				q.push(go[root][i]) ;
			}
		}
		while (!q.empty()) {
			int now = q.front() ; q.pop () ;
			end[now] |= end[fail[now]] ;
			for (int i=0 ; i<10 ; i++) {
				if (go[now][i]==-1) 
					go[now][i] = go[fail[now]][i] ;
				else {
					fail[go[now][i]] = go[fail[now]][i] ;
					q.push (go[now][i]) ;
				}
			}
		}
	}
} ;
