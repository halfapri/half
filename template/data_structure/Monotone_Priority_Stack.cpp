#include<bits/stdc++.h>
using namespace std;
const int M = 1e5 + 7 ;
int L[M] , R[M] ;
int n ;
int h[M] ;

void run () {
	stack<int> q ;
	for (int i=0 ; i<n ; i++) {
		while (!q.empty() && h[q.top()]>=h[i]) q.pop() ;
		L[i] = q.empty()?0:q.top()+1 ;
		q.push(i) ;
	}
	while (!q.empty()) q.pop() ;
	for (int i=n-1 ; i>=0 ; i--) {
		while(!q.empty() && h[q.top()]>=h[i]) q.pop() ;
		R[i] = q.empty()?n-1:q.top()-1 ;
		q.push(i) ;
	}
}
