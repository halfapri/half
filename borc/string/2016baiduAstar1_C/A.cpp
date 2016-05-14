#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<map>
using namespace std;
typedef long long ll ;

const int M = 100000+10 ;
struct TRIE {
	int go[M*30][26] ;
	int sz[M*30] ;
	int root , o;

	int newnode () {
		for (int i=0 ; i<26 ; i++) go[o][i] = -1 ;
		sz[o] = 0 ;
		return o ++ ;
	}

	void init () {
		o = 0 ;
		root = newnode () ;
	}

	void Insert (char *s) {
		int cur = root ;
		for (; *s ; s ++) {
			int ch = *s-'a' ;
			if (go[cur][ch]==-1) {
				go[cur][ch] = newnode () ;
				sz[cur] ++ ;
			}
			cur = go[cur][ch] ;
		}
	}

	bool Del (char *s , int rt=0) {
		if (!(*s)) return true ;
		int ch = *s-'a' ;
		if (go[rt][ch]==-1) return false ;
		if (Del (s+1 , go[rt][ch])) {
			if (sz[rt]==1) {
				go[rt][ch] = -1 ;
				sz[rt] = 0 ;
				return true ;
			} else {
				go[rt][ch] = -1 ;
				sz[rt] -- ;
				return false ;
			}
		}
		return false ;
	}

	bool Search (char *s , int rt=0) {
		if (!(*s)) return true ;
		int ch = *s-'a' ;
		if (go[rt][ch]==-1) return false ;
		return Search (s+1 , go[rt][ch]) ;
	}
} trie ;

int N ;

int main () {
	while (~ scanf("%d" , &N)) {
		trie.init () ;
		for (int i=0 ; i<N ; i++) {
			char t[10] , s[40] ;
			scanf ("%s%s" , t,s) ;
			if (t[0]=='i') trie.Insert (s) ;
			else if (t[0]=='s') {
				if (trie.Search (s)) puts ("Yes") ;
				else puts ("No") ;
			} 
			else trie.Del(s) ;
		}
	}
	return 0 ;
}
