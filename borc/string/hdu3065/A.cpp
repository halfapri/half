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

const int M = 1010*50 ;
int n ;
char s[2000000+10] ;
int cnt[1010] ;
char t[1010][55] ;
struct Trie {
	int go[M][26] , fail[M] ;
	int end[M] ;
	int o , root ;

	void init () {
		o = 0 ;
		root = newNode () ;
	}

	int newNode () {
		for (int i=0 ; i<26 ; i++)
			go[o][i] = -1 ;
		end[o] = 0 ;
		return o ++ ;
	}

	void Insert (char *s , int id) {
		int now = root ;
		for (; *s ; s ++) {
			if (go[now][*s-'A']==-1)
				go[now][*s-'A'] = newNode() ;
			now=go[now][*s-'A'] ;
		}
		end[now] = id ;
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
		while (!q.empty()) {
			int now=q.front() ; q.pop () ;
			for (int i=0 ; i<26 ; i++) {
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
		int now=root ;
		for (; *s ; s++) {
			if (*s<'A' || *s>'Z') {
				now=root ;
				continue ;
			}
			now=go[now][*s-'A'] ;
			int tmp=now ;
			while (tmp!=root) {
				if (end[tmp])
					cnt[end[tmp]] ++ ;
				tmp=fail[tmp] ;
			}
		}
	}
} ac;

int main () {
	while (~ scanf ("%d" , &n)) {
		memset (cnt , 0 , sizeof(cnt)) ;
		ac.init () ;

		for (int i=0 ; i<n ; i ++) {
			scanf ("%s" , t[i]) ;
			ac.Insert (t[i] , i+1) ;
		}
		ac.get_fail () ;

		scanf ("%s" , s) ;
		ac.search (s) ;
		for (int i=0 ; i<n ; i++) {
			if (cnt[i+1]==0) continue ;
			printf ("%s: %d\n" , t[i] , cnt[i+1]) ;
		}
	}
	return 0 ;
}
