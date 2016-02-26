#include<bits/stdc++.h>
using namespace std;
const int M = 1e5 + 10 ;
struct Trie {
	Trie *go[26] ;
	bool ed ;
	Trie () {
		memset (go , 0 , sizeof(go)) ;
		ed = 0 ;
	}
} ;

Trie pool[M] , *alloc , *root ;

char s[M] ;

void Insert (char *s) {
	Trie *path = root ;
	for ( ; *s ; s ++) {
		int tmp = *s - 'a' ;
		if (path->go[tmp] == NULL) path->go[tmp] = new(alloc ++) Trie ;
		path = path->go[tmp] ;
	}
	path->ed = 1 ;
}

int main () {
	alloc = pool ;
	root = new(alloc ++) Trie ;
	int m ;
	scanf ("%d" , &m) ;
	for (int i = 0 ; i < m ; i ++) {
		scanf ("%s" , s) ;
		Insert (s) ;
	}
	return 0 ;
}
