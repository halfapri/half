#include<bits/stdc++.h>
using namespace std;
const int M = 1e6+10 ;
int n , m , k ;
vector<int>g[M] ;
int pre[M] , ure[M] ;
int a[M] ;

int main () {
	cin >> n >> m >> k ;
	for (int i = 1 ; i <= n ; i ++) {
		int x ;
		scanf ("%d" , &a[i]) ;
		g[a[i]].push_back (i) ;
	}

	for (int i = 2 ; i <= n ; i ++) {
		int tmp = k^a[i] ;
		int x = lower_bound (g[tmp].begin(),g[tmp].end(),i) - g[tmp].begin() ;
		pre[i] = pre[i-1] ;
		printf ("i=%d , x=%d\n" , i , x) ;
		if (g[tmp].size() == 0) continue ;
		if (x == 0) continue ;
		pre[i] += x ;
		printf ("pre[%d]=%d\n" , i , pre[i]) ;
	}
	puts ("Pre:") ;
	for (int i = 1 ; i <= n ; i ++) printf ("%d " , pre[i]) ; puts ("") ;
	for (int i = n-1 ; i >= 1 ; i --) {
		int tmp = k^a[i] ;
		int x = lower_bound(g[tmp].begin(),g[tmp].end(),i) - g[tmp].begin() ;
		ure[i] = ure[i+1] ;
		if (x == g[tmp].size()) continue ;
		ure[i] += g[tmp].size()-x ;
	}
	puts ("Ure:") ;
	for (int i = 1 ; i <= n ; i ++) printf ("%d " , ure[i]) ; puts ("") ;
	while (m --) {
		int l , r ;
		scanf ("%d%d" , &l , &r) ;
		int hou_in = ure[r+1] ;
		int hou_out = pre[n]-pre[r]-hou_in ; 
		int qian_in = pre[l-1] ;
		int qian_out = ure[1]-ure[l]-qian_in ;
		printf ("hou_out=%d,qian_out=%d\n" , hou_out , qian_out) ;
		
		int tmp = abs(hou_out-qian_out) ;
		int ans = ure[l]-ure[r+1] + pre[r]-pre[l-1];
		cout << "tmp = " << tmp << " ans = " << ans << endl ;

		int f = (ans-tmp)/2 ;
		cout << f << endl ;
	}
	return 0 ;
}
