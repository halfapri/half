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

char s[10000+10] , t[10000+10] ;
char pool[10000+10] ;
int lens , lent ;
const int mod = 12345647 ;
int dp[10000+10][8][3] ;

void init (char *h , int &len) {
	int l=0 ;
	while (pool[l]=='0') l++ ;
	if (pool[l]==0) len=1,h[0]='0',h[1]='\0' ;
	else {
		len = 0 ;
		for (;pool[l]!=0;l++) h[len++] = pool[l] ;
		h[len] = '\0' ;
	}
}

int judge (bool flag , int cur , int f) {
	return flag?f>=cur:f>cur ;
}

int calc (int pos , int status , int carry) {
	//printf ("pos=%d,status=%d,carry=%d\n" , pos,status,carry) ;
	if (pos==-1) return status==7 && carry==0 ;
	if (dp[pos][status][carry]!=-1)
		return dp[pos][status][carry] ;

	int ret = 0 ;
	int a , b , c ;
	for (int i=0 ; i<10 ; i++) {
		if (i==3) continue ;
		for (int j=0 ; j<10 ; j++) { 
			if (j==3) continue ;
			int tmp=i+j+carry ;
			a=judge((status>>2)&1,t[pos]-'0',i) ;
			b=judge((status>>1)&1,t[pos]-'0',j) ;
			for (int k=0 ; k<3 ; k++) {
				int tot = k*10+s[pos]-'0' ;
				int z = tot-tmp ;
				if (z<0||z>9||z==3) continue ;
				c=judge(status&1,t[pos]-'0',z) ;
				//printf ("k=%d:%d,%d,%d\n" ,k,i,j,z) ;
				ret += calc(pos-1,(a<<2)+(b<<1)+c,k) ;
				ret %= mod ;
			}
		}
	}
	return dp[pos][status][carry]=ret ;
}

int main () {
	while (~ scanf ("%s" ,pool)) {
		init (s,lens) ;
		scanf ("%s" , pool) ; 
		init (t,lent) ;
		if (s[0]=='0'&&t[0]=='0'&&lens==1&&lent==1) break ;

		for (int i=0 ; i<=lens-lent ; i++) {
			if (i==lens-lent) {
				pool[i]='\0' ;
				break ;
			}
			pool[i]='0' ;
		}
		strcat(pool,t) ;
		strcpy(t,pool) ;
		for (int i=0 ; i<lens ;i++)
			for (int j=0 ; j<8 ; j++)
				for (int z=0 ; z<3 ; z++)
					dp[i][j][z] = -1 ;
		printf ("%d\n" , calc(lens-1,7,0)) ;
	}
	return 0 ;
}
