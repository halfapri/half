#include <bits/stdc++.h>
int a[200] ;
const int LIMIT = 1000000+1 ;

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
		int n ;
		scanf ("%d" , &n) ;
		for (int i=0 ; i<n ;i++) scanf ("%d" , &a[i]) ;
		int E ;
		scanf ("%d" , &E) ;
		if (E>=LIMIT) {
			puts ("No") ;
			continue ;
		}
		std::bitset<LIMIT> bit;
		bit.reset();
		bit[0] = 1;
		std::priority_queue<int,std::vector<int>,std::greater<int>> que;
		for (int i = 0; i < n; ++ i) {
			que.push(a[i]);
		}
		while (que.size() >= 2) {
			int a = que.top(); que.pop();
			int b = que.top(); que.pop();
			bit = bit << a | bit << b;
			que.push(a + b);
		}
		puts(E < LIMIT && bit[E] ? "Yes" : "No");
	}
}
