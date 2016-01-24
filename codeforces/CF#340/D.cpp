#include<bits/stdc++.h>
using namespace std;
typedef long long ll ;
ll x[3] , y[3] ;

bool judgex (int a , int b , int c) {
	if (x[a]==x[b]) ;
	else return false ;
	int maxn = max(y[a],y[b]) , minn = min(y[a],y[b]) ;
	if (y[c] >= maxn || y[c] <= minn) return true ;
	return false ;
}

bool judgey (int a , int b , int c) {
	if (y[a]==y[b]) ;
	else return false ;
	int maxn = max(x[a],x[b]) , minn = min(x[a],x[b]) ;
	if (x[c] >= maxn || x[c] <= minn) return true ;
	return false ;
}

int main () {
	for (int i = 0 ; i < 3 ; i ++) {
		cin >> x[i] >> y[i] ;
	}
	if (x[0]==x[1]&&x[1]==x[2]) {
		puts ("1") ;
	}
	else if (y[0]==y[1]&&y[1]==y[2]) {
		puts ("1") ;
	}
	else if (judgex(0,1,2) || judgex(0,2,1) || judgex(1,2,0)) {
		puts ("2") ;
	}
	else if (judgey(0,1,2) || judgey(0,2,1) || judgey(1,2,0)) {
		puts ("2") ;
	}
	else puts ("3") ;
	return 0 ;
}
