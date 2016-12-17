#include<bits/stdc++.h>
using namespace std;
int n , t ;
double p ;
const int M = 2010 ;
double dp[M][M] ;

int main () {
	cin >> n >> p >> t ;
	dp[0][0] = 1 ;
	for (int i = 1 ; i <= t ; i ++) {
		dp[i][0] = dp[i-1][0]*(1.0-p) ;
		for (int j = 1 ; j <= n ; j ++) {
			if (j != n) dp[i][j] = dp[i-1][j-1]*p + 
				dp[i-1][j]*(1-p) ;
			else dp[i][j] = dp[i-1][j] + dp[i-1][j-1]*p ;
			//printf ("dp[%d][%d]=%.6f\n" , i,j,dp[i][j]) ;
		}
	}
	//cout.precision(10) ;
	//for (int i = 1 ; i <= t ; i ++) printf ("dp[%d][%d]=%.6f\n" ,i,n,dp[i][n]) ;
	//cout << dp[t][n] << endl ;
	//cout << n << endl ;
	double num = 0 ;
	for (int i = 1 ; i <= n ; i ++) num += dp[t][i]*i ;
	printf ("%.6f\n" , num) ;
	return 0 ;
}
