#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef long long ll ;
vector<pair<ll ,int> > vc ;
int n ;
int sx[2] , sy[2] ;
int x[2010] , y[2010] ;

ll dis1 (int px , int py) {
	return 1ll*(sx[0]-px)*(sx[0]-px)+1ll*(sy[0]-py)*(sy[0]-py) ;
}

ll dis2 (int px , int py) {
	return 1ll*(sx[1]-px)*(sx[1]-px)+1ll*(sy[1]-py)*(sy[1]-py) ;
}

void solve () {
	sort(vc.begin(),vc.end()) ;
	ll tmp = -1 ;
	ll cur = vc[n-1].F ;
	for (int i = n-1 ; i > 0 ; i --) {
		int id = vc[i].S ;
		tmp = max (tmp , dis2(x[id],y[id])) ;
		if (cur > tmp+vc[i-1].F) {
			cur = tmp+vc[i-1].F ;
		}
	}
	int id = vc[0].S ;
	tmp = max (tmp , dis2(x[id],y[id])) ;
	if (cur > tmp) cur = tmp ;
	cout << cur << endl ;
}

int main () {
	cin >> n >> sx[0] >> sy[0] >> sx[1] >> sy[1] ;
	for (int i = 0 ; i < n ; i ++) {
		scanf ("%d%d" , &x[i] , &y[i]) ;
	}
	for (int i = 0 ; i < n ; i ++) {
		ll tmp = dis1 (x[i],y[i]) ;
		vc.push_back (make_pair(tmp,i)) ;
	}
	solve () ;
	return 0 ;
}
