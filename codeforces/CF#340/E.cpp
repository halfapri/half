#include<bits/stdc++.h>
using namespace std;
const int M = 1e6+10 ;
int n , m , k ;
int cnt[M] ;
int pre[M] , ure[M] ;
int a[M] ;

int main () {
	cin >> n >> m >> k ;
	int tmp = 0 ;
	int ans = 0 ;
	for (int i = 1 ; i <= n ; i ++) {
		scanf ("%d" , &a[i]) ;
	}
	cnt[0] = 1 ;
	for (int i = 1 ; i <= n ; i ++) {
		tmp = tmp^a[i] ;
		ans = tmp^k ;
		//printf ("tmp = %d\n" , tmp) ;
		//printf ("cnt[%d] = %d\n" , ans , cnt[ans]) ; 
		pre[i] = pre[i-1] + cnt[ans] ;
		cnt[tmp] ++ ;
	}
	memset (cnt , 0 , sizeof(cnt)) ;
	tmp = 0 ;
	cnt[0] = 1 ;
	for (int i = n ; i >= 1 ; i --) {
		tmp = tmp^a[i] ;
		ans = tmp^k ;
		ure[i] = ure[i+1] + cnt[ans] ;
		cnt[tmp] ++ ;
	}
	puts ("") ;
	puts ("pre:") ;
	for (int i = 1 ; i <= n ; i ++) printf ("%d " , pre[i]) ; puts ("") ;
	puts ("ure") ;
	for (int i = 1 ; i <= n ; i ++) printf ("%d " , ure[i]) ; puts ("") ;
	while (m --) {
		int L , R ;
		scanf ("%d%d" , &L , &R) ;
		int tmp1 = pre[n]-pre[R]-ure[R+1] ;
		int tmp2 = ure[1]-ure[L]-pre[L+1] ;

		cout << pre[R]-pre[L-1] << endl ;
	}
	return 0 ;
}
