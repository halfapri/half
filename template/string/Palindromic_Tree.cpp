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

struct Palindromic {
#define M 10000+10 ;
	char s[M] ;//1based
	int sL ;
	int go[M][26] ;
	int fail[M] ;
	int len[M] ; //每种回文串的长度
	int pal[M] , pL; //不同类型的回文串的数量
	int num[M] ; //以i下标作为结尾的回文串的数量

	int newnode (int l) {
		for (int i=0 ; i<26 ; i++) go[pL][i]=-1 ;
		pal[pL]=0 ;
		len[pL]=l ;
		num[pL]=0 ;
		return pL ++ ;
	}

	void init () {
		sL=pL=0 ;
		newnode (0) ;//偶数回文串的根
		newnode (-1) ;//奇数回文串的根
		s[sL++] = '$';
		fail[0] = 1 ;
	}

	int get_fail (int x) {
		while (s[sL-len[x]-1] != s[sL]) x = fail[x] ;
		return x;
	}
		
	void Insert () {
		int last=0 ;
		for (; s[sL] ; sL++) {
			int x = s[sL]-'a' ;
			int cur = get_fail (last) ;
			if (go[cur][x]!=-1) {
				int now = newnode(len[cur]+2) ;
				fail[now] = go[get_fail(fail[cur])][x] ;
				go[cur][x] = now ;
				num[sL] = num[fail[now]] + 1 ;
			}
			last = go[cur][x] ;
			pal[last] ++ ;
		}

		for (int i=p-1 ; i>=0 ; i--) 
			pal[fail[i]] += pal[i] ;
	}
} pt;

int main () {
	pt.init () ;
	scanf ("%s" , pt.s+1) ;
	pt.Insert () ;
	return 0 ;
}
