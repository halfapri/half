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
#define M (500000+10)
	int go[M][26] , fail[M] , end[M] ;
	int o , root ;

	void init () {
		o = 0 ;
		root = newNode () ;
	}

	int newNode () {
		for (int i=0 ; i<26 ; i++)
			go[o][i] = -1 ;
		end[o] = false ;
		return o ++ ;
	}

	void Insert (char *s) {
		int now = root ;
		for (; *s ; s ++) {
			if (go[now][*s-'a']==-1)  
				go[now][*s-'a'] = newNode () ;
			now = go[now][*s-'a'] ;
		}
		end[now] ++ ;
	}

	void get_fail () {
		queue<int> q ;
		for (int i=0 ; i<26 ; i++) {
			if (go[root][i]==-1)
				go[root][i] = root ;
			else {
				fail[go[root][i]] = root ;
				q.push (go[root][i]) ;
			}
		}
		while (!q.empty ()) {
			int now=q.front() ; q.pop() ;
			for (int i=0 ; i<26 ; i++) {
				if (go[now][i] == -1) 
					go[now][i] = go[fail[now]][i] ;
				else { 
					fail[go[now][i]] = go[fail[now]][i] ;
					q.push (go[now][i]) ;
				}
			}
		}
	}

	int search (char *s) {
		int cnt = 0 ;
		int now = root ;
		for (; *s ; s ++) {
			now = go[now][*s-'a'] ;
			int tmp = now ;
			while (tmp != root) {
				cnt += end[tmp] ;
				end[tmp] = 0 ;
				tmp = fail[tmp] ;
			}
		}
		return cnt ;
	}
} ac ;
char s[1000000+10] ;
int n ;

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		ac.init () ;
		scanf ("%d" , &n) ;
		for (int i = 0 ; i < n ; i ++) {
			scanf ("%s" , s) ;
			ac.Insert (s) ;
		}
		ac.get_fail () ;
		scanf ("%s" , s) ;
		printf ("%d\n" , ac.search (s)) ;
	}
	return 0 ;
}
