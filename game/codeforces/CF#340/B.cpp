#include<bits/stdc++.h>
using namespace std;
int n ;
typedef unsigned long long ull ;
int a[111] ;
vector<int> vc ;

int main () {
	scanf ("%d" , &n) ;
	int cnt = 0 ;
	int i ;
	for (i = 0 ; i < n ; i ++) scanf ("%d" , &a[i]) ;
	i = 0 ;
	if (a[i] != 1) while (a[i] == 0 && i < n) i ++;
	if (i == n) return puts ("0") , 0 ;
	i ++ ;
	for (; i < n ; i ++) {
		if (a[i] == 0) cnt ++ ;
		else {
			vc.push_back (cnt) ;
			cnt = 0 ;
		}
	}
	//for (int x : vc) cout << x << " " ; puts ("") ;
	if (vc.size() == 0) puts ("1") ;
	else {
		ull tot = 1 ;
		for (int x:vc) tot = tot*(x+1) ;
		cout << tot << endl ;
	}
	return 0 ;
}
