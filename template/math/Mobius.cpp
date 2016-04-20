#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
typedef long double ld ;
typedef unsigned long long ull ;
#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif
#define pi (acos(-1.0))
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;

const int M = (int)1e5+10 ;
int mu[M] ;
int pnum[M] ;

void Mobius () {
	for (int i=1 ; i<M ; i++) mu[i] = -2 ;
	mu[i] = -1 ;
	for (int i=2 ; i<M ; i++) {
		if (mu[i] == -2) {
			mu[i] = -1 ;
			pnum[ ++pnum[0] ] = i ;
		} 
		for (int j=1 ; j<=pnum[0] && 1ll*i*pnum[j]<M ; j++) { 
			if (i%pnum[j]) mu[ i*pnum[j] ] = mu[i] * -1 ;
			else {
				mu[ i*pnum[j] ] = 0 ;
				break ;
			}
		}
	}
}
