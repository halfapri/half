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

const int M = 1e5 ;
struct Palindromic {
	int S[M] ;//1based
	int sL , oL , last ;
	int go[M][26] ;
	int fail[M] ;
	int len[M] ; //每种回文串的长度
	int pal[M] ; //不同类型的回文串的数量
	int num[M] ; //以i下标作为结尾的回文串的数量

	int newnode (int l) {
		for (int i=0 ; i<26 ; i++) go[pL][i]=0 ;
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
		last = 1 ;
		fail[0] = 1 ;
	}

	int get_fail (int x) {
		while (S[sL-len[x]-1] != S[sL]) x = fail[x] ;
		return x;
	}
		
	void Insert (char v) {
		v -= 'a' ;
		S[++sL] = v ;
		int cur = get_fail (last) ;
		if (!go[cur][v]) {
			int now = newnode(len[cur]+2) ;
			fail[now] = go[get_fail(fail[cur])][v] ;
			go[cur][v] = now ;
			num[sL] = num[fail[now]] + 1 ;
		}
		last = go[cur][v] ;
		pal[last] ++ ;
	}

	void count () {
		for (int i=oL-1 ; i>=0 ; i--)
			cnt[fail[i]] += cnt[i] ;
	}
} pt;
