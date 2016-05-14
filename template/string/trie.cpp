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
/////////////////////////////////////////////////////////////////////////////////////
struct TRIE {
	int go[M][26] ;
   	bool ed[M] ;
	int root , o ;

	void init () {
		o = 0 ;
		root = newnode () ;
	}
	int newnode () {
		for (int i=0 ; i<26 ; i++) go[o][i] = -1 ;
		ed[o] = 0 ;
		return o ++ ;
	}
	void Insert (char *s,int rt=0) {
		for (; *s ; s++) {
			int ch = *s-'a' ;
			if (go[rt][ch]==-1) {
				go[rt][ch] = newnode () ;
			}
			rt = go[rt][ch] ;
		}
		ed[rt] = 1 ;
	}
	bool search (char *s,int rt=0) {
		for (; *s ; s++) {
			int ch = *s-'a' ;
			if (go[rt][ch]==-1) return false ;
			rt = go[rt][ch] ;
		}
		return ed[rt] ;
	}
} trie ;
