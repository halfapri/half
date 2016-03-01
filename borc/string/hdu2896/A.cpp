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

const int M = 100000+10 ;
vector<int> vc ;
struct Trie {
	int go[M][128] , fail[M] ;
	int end[M] ;
	int root , o ;

	void init () {
		o = 0 ;
		root = newNode () ;
	}

	int newNode () {
		for (int i=0 ; i<128 ; i++) 
			go[o][i] = -1 ;
		end[o] = 0 ;
		return o ++ ;
	}

	void Insert (char *s , int id) {
		int now = root ;
		for (; *s ; s++) {
			if (go[now][*s]==-1)
				go[now][*s] = newNode () ;
			now = go[now][*s] ;
		}
		end[now] = id ;
	}

	void get_fail () {
		queue<int> q ;
		for (int i=0 ; i<128 ; i++) {
			if (go[root][i]==-1)
				go[root][i] = root ;
			else {
				fail[go[root][i]] =  root ;
				q.push (go[root][i]) ;
			}
		}

		while (!q.empty()) {
			int now=q.front() ; q.pop () ;
			for (int i=0 ; i<128 ; i++) {
				if (go[now][i]==-1)
					go[now][i] = go[fail[now]][i] ;
				else {
					fail[go[now][i]] = go[fail[now]][i] ;
					q.push (go[now][i]) ;
				}
			}
		}
	}

	void search (char *s) {
		int now = root ;
		for (; *s ; s ++) {
			now = go[now][*s] ;
			int tmp = now ;
			while (tmp != root) {
				if (end[tmp])
					vc.push_back (end[tmp]) ;
				tmp = fail[tmp] ;
			}
		}
	}
}ac ;

int n , m ;
char s[10000+10] ;

int main () {
	while (~ scanf ("%d" , &n)) {
		ac.init () ;
		for (int i=1 ; i<=n ; i++) {
			scanf ("%s" , s) ;
			ac.Insert (s , i) ;
		}
		ac.get_fail () ;

		scanf ("%d" , &m) ;
		int total = 0 ;
		for (int i=1 ; i<=m ; i++) {
			scanf ("%s" , s) ;
			vc.clear () ;
			ac.search (s) ;
			if (vc.size()) total ++ ;
			else continue ;
			sort(vc.begin(),vc.end()) ;
			printf ("web %d:" , i) ;
			for (int j:vc) 
				printf (" %d" , j) ;
			puts ("") ;
		}
		printf ("total: %d\n" , total) ;
	}
	return 0 ;
}
