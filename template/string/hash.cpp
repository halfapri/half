#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll ;
const int bas[2] = {17 , 233} ;
const int mod[2] = {(int)1e9+7 , (int)1e9+21} ;
const int M = 3e5 + 7 ;
set<pair<int , int> > HASH ; 
ll pw[2][M] ;
int n , m ;
char s[M] ; 

int get_HASH (char *s , int x) {
	int ret = 0 ;
	int lens = strlen (s) ;
	for (int i = 0 ; i < lens ; i ++) {
		ret = (1ll*ret + 1ll*pw[x][i] * (s[i]-'a' + 1)) % mod[x] ;
	}
	return ret ;
}

int main () {
	pw[0][0] = pw[1][0] = 1 ;
	for (int i = 1 ; i < M ; i ++) {
		pw[0][i] = 1ll * pw[0][i-1] * bas[0] % mod[0] ;
		pw[1][i] = 1ll * pw[1][i-1] * bas[1] % mod[1] ;
	}

	return 0 ;
}
