/*
   这里求 ai 的区间[Li , Ri] ,使得在这个区间里 ai 是最小的.
   当出现 2 1 2 1 1 2 2这种情况时，我们令靠前的 2 统治的区间尽可能大.
*/
#include<bits/stdc++.h>
using namespace std;
const int M = 1e5 + 7 ;
int L[M] , R[M] ;
int n ;
int a[M] ;

void L_wall () {
	stack<int> wall ;
	L[1] = 1 ;
	wall.push (1) ;
	for (int i = 2 ; i <= n ; i ++) {
		if (a[wall.top()] < a[i]) L[i] = wall.top()+1 ; 
		else {
			while (!wall.empty() && a[wall.top()] >= a[i]) wall.pop () ; 
			if (!wall.empty ()) L[i] = 1 ;
			else L[i] = wall.top () + 1 ;
		}
		wall.push (i) ;
	}
}

void R_wall () {
	stack<int> wall ;
	R[n] = n ; 
	wall.push (n) ;
	for (int i = n-1 ; i >= 1 ; i --) {
		if (a[wall.top()] <= a[i]) R[i] = wall.top()-1 ; 
		else {
			while (!wall.empty() && a[wall.top()] > a[i]) wall.pop () ;
			if (!wall.empty ()) R[i] = n ;
			else R[i] = wall.top()-1 ;
		}
		wall.push (i) ;
	}
}

int main () {
	scanf ("%d" , &n) ;
	for (int i = 1 ; i <= n ; i ++) 
		scanf ("%d" , &a[i]) ;
	return 0 ;
}
