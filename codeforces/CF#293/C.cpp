#include<bits/stdc++.h>
using namespace std;
int n , m , k ;
const int M = 1e5 + 10 ;
int id[M] ;
int mp[M] ;
typedef long long ll ;

int main () {
	cin >> n >> m >> k ;
	for (int i = 1 ; i <= n ; i ++) {
		int x ;
		scanf ("%d" , &x) ;
		id[x] = i ;
		mp[i] = x ;
	}
	ll cnt = 0 ;
	while (m --) {
		int x ;
		scanf ("%d" , &x) ;
		//cout << id[x] << endl ;
		cnt += (id[x]%k==0?id[x]/k-1:id[x]/k) + 1 ;
		if (id[x] > 1) {
			id[x] -- ;
			int xx = mp[id[x]] ;
			mp[id[x]] = x ;
			mp[id[x]+1] = xx ;
			id[xx] ++ ;
		}
	}
	cout << cnt << endl ;
	return 0 ;
}
