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
const ll INF = (ll)1e18 ;

const int M = 10000+10 ;
struct trie {
	trie *go[2] ;
	bool ed ;
	trie () {
		memset (go , 0 , sizeof(go)) ;
		ed = 0 ;
	}
} ;

trie pool[M*100] , *root , *alloc ;
char s[111] ;
int lens ;
int n ;
int cnt = 0 ;

inline int add (int x) {
	return x>=lens?x-lens:x ;
}

void maxway (char *s) {
	lens = strlen (s) ;
	int i = 0 , j = 1 , k = 0 ;
	while (i<lens && j<lens && k<lens) {
		int tmp = s[add(i+k)]-s[add(j+k)] ;
		if (tmp == 0) k ++ ;
		else {
			if (tmp<0) j+=k+1 ;
			else i+=k+1 ;
			if (i==j) j ++ ;
			k = 0 ;
		}
	}
	int len = min(i,j)+1 ;
	rotate (s,s+len,s+lens) ;
}

void Insert (char *s) {
	trie *path = root ;
	for (; *s ; s ++) {
		int tmp = *s-'0' ;
		if (path->go[tmp]==NULL)
			path->go[tmp] = new(alloc++) trie ;
		path = path->go[tmp] ;
	}
	if (!(path->ed)) {
		path->ed = 1 ;
		cnt ++ ;
	}
}

int main () {
	while (~ scanf ("%d" , &n)) {
		cnt = 0 ;
		alloc = pool ;
		root = new(alloc ++) trie ;
		for (int i = 0 ; i < n ; i ++) {
			scanf ("%s" , s) ;
			maxway (s) ;
			Insert (s) ;
		}
		printf ("%d\n" , cnt) ;
	}
	return 0 ;
}
