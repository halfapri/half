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

int n , m ;
int s[30002] ;
char t[30002] ;

struct Trie {
	int go[512*70][256] , fail[512*70] ;
	int end[512*70] ;
	int o , root ;

	void init () {
		o = 0 ;
		root = newNode () ;
	}

	int newNode () {
		for (int i=0 ; i<256 ; i++) 
			go[o][i] = -1 ;
		end[o] = -1 ;
		return o ++ ;
	}

	void Insert (int *s , int id , int lens) {
		int now = root ;
		for (int i=0 ; i<lens ; i ++) {
			if (go[now][s[i]]==-1)
				go[now][s[i]] = newNode () ;
			now=go[now][s[i]] ;
		}
		end[now] = id ;
	}

	void get_fail () {
		queue<int> q ;
		for (int i=0 ; i<256 ; i++) { 
			if (go[root][i]==-1)
				go[root][i] = root ;
			else {
				fail[go[root][i]] = root ; 
				q.push (go[root][i]) ;
			}
		}
		while (!q.empty()) {
			int now=q.front() ; q.pop () ;
			for (int i=0 ; i<256 ; i++) {
				if (go[now][i]==-1) 
					go[now][i] = go[fail[now]][i] ;
				else {
					fail[go[now][i]] = go[fail[now]][i] ;
					q.push (go[now][i]) ;
				}
			}
		}
	}

	void search (int *s ,int lens ) {
		bool vis[520] ;
		memset (vis , 0 , sizeof(vis)) ; 
		int now=root ;
		for (int i=0 ; i<lens ; i++) {
			now=go[now][s[i]] ;
			int tmp=now ;
			while (tmp!=root) {
				if (~end[tmp])
					vis[end[tmp]] = 1 ;
				tmp=fail[tmp] ;
			}
		}
		int cnt = 0;
		for (int i=0 ;i<n ; i++)
			if (vis[i]) cnt ++ ;
		printf ("%d\n" , cnt) ;
	}
} ac ;

int table (char ch) {
	if (ch>='A' && ch<='Z') return ch-'A' ;
	if (ch>='a' && ch<='z') return ch-'a'+26 ;
	if (ch>='0' && ch<='9') return ch-'0'+52 ;
	if (ch=='+') return 62 ;
	return 63 ;
}

int decode (char *t) {
	int cnt = 0 , lens = 0 ;
	int pre = 0 ;
	int a[10] ;
	for (; *t ; t ++) {
		if (*t=='=') continue ;
		int tmp = table(*t) ;
		for (int i=0 ; i<6 ; i++){
			a[i] = tmp&1 ;
			tmp >>= 1 ;
		} 
		for (int i=5 ; i>=0 ; i--) {
			cnt ++ ;
			pre = pre<<1 | a[i] ;
			if (cnt%8==0) {
				s[lens++] = pre ;
				pre = 0 ;
			}
		}
	}
	return lens ;
}

int main () {
	while (~ scanf ("%d" , &n)) {
		ac.init () ;
		for (int i=0 ; i<n ; i++) {
			scanf ("%s" , t) ; 
			int lens = decode (t) ;
			ac.Insert (s , i , lens) ;
		}
		ac.get_fail () ;

		scanf ("%d" , &m) ;
		for (int i=0 ; i<m ; i++) {
			scanf ("%s" , t) ;
			int lens = decode (t) ;
			ac.search (s , lens) ;
		} puts ("") ;
	}
	return 0 ;
}
