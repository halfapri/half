#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
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

const int mod = 100000 ;

struct Matrix {
	int n ;
	int mat[110][110] ;

	Matrix () {}
	Matrix (int _n) : n(_n) {
		for (int i=0 ; i<n ; i ++) 
			for (int j=0 ; j<n ; j++) 
				mat[i][j] = i==j ;
	}

	inline Matrix operator * (const Matrix &a) const {
		Matrix ans(n) ;
		for (int i=0 ; i<n ; i ++) {
			for (int j=0 ; j<n ; j++) {
				ll tmp=0 ;
				for (int k=0 ; k<n ; k++) {
					tmp += 1ll*mat[i][k]*a.mat[k][j]%mod ;
					if (tmp>(ll)1e18)
						tmp %= mod ;
				}
				ans.mat[i][j] = tmp%mod ;
			}
		}
		return ans ;
	}

	inline Matrix operator ^ (int pw) const {
		Matrix ret(n) ;
		Matrix x=*this ;
		for (; pw ; pw>>=1) {
			if (pw&1) ret = ret*x ;
			x = x*x ;
		}
		return ret ;
	}
} ;

struct Trie {
	int go[110][4] , fail[110] ;
	bool end[110] ;
	int table[128] ;
	int o , root ;

	void init () {
		o = 0 ;
		table['A']=0 , table['C']=1 , table['T']=2 ,table['G']=3;
		root = newNode () ; 
	}

	int newNode () {
		memset (go[o] , -1 , sizeof(go[o])) ;
		end[o] = 0 ;
		return o ++ ;
	}

	void Insert (char *s) {
		int now = root ;
		for (; *s ; s ++) {
			if (go[now][table[*s]]==-1)
				go[now][table[*s]] = newNode () ;
			now = go[now][table[*s]] ;
		}
		end[now] = 1 ;
	}

	void get_fail () {
		queue<int> q ;
		for (int i=0 ; i<4 ; i++) {
			if (go[root][i]==-1)
				go[root][i] = root ;
			else {
				fail[go[root][i]] = root ;
				q.push (go[root][i]) ;
			}
		}
		while (!q.empty()) {
			int now = q.front() ; q.pop () ;
			end[now] |= end[fail[now]] ;
			for (int i=0 ; i<4 ; i++) {
				if (go[now][i]==-1)
					go[now][i] = go[fail[now]][i] ;
				else {
					fail[go[now][i]] = go[fail[now]][i] ;
					q.push (go[now][i]) ;
				}
			}
		}
	}

	void get_mat (Matrix &a) {
		for (int i=0 ; i<o ; i++) 
			for (int j=0 ; j<4 ; j++) 
				if (end[go[i][j]]==0 && end[i]==0)
					a.mat[i][go[i][j]] ++ ;
	}
}ac ;

int n , m ;
char s[15] ;


void solve () {
	Matrix a(ac.o) ;
	for (int i=0 ; i<a.n ; i++) 
		a.mat[i][i] = 0 ;

	ac.get_mat (a) ;
	a = a^n ;
	int sum = 0 ;
	for (int i=0 ; i<a.n ; i++)  
		sum = (sum + a.mat[0][i])%mod ;
	printf ("%d\n" , sum) ;
}

int main () {
	while (~ scanf ("%d%d" , &m,&n)) {
		ac.init () ;
		for (int i=0 ; i<m ; i ++) {
			scanf ("%s" , s) ;
			ac.Insert (s) ;
		}
		ac.get_fail () ;

		solve () ;
	}
	return 0 ;
}
