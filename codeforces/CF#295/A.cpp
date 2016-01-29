#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)1e18 ;

bool vis[2][26] ;

int main () {
	int n ;
	string s ;
	cin >> n >> s ;
	for (int i = 0 ; i < n ; i ++) {
		if (s[i]>='A'&&s[i]<='Z') vis[1][s[i]-'A'] = 1 ;
		else vis[0][s[i]-'a'] = 1 ;
	}
	for (int i = 0 ; i < 26 ; i ++) {
		if (!(vis[0][i] || vis[1][i])) {
			return puts ("NO") , 0 ;
		}
	}
	return puts ("YES") , 0 ;
}
