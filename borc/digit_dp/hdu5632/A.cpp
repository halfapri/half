#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 305;
int s;
 
struct bign {
    int len;
    int num[MAXN];
 
    bign () {
        len = 0;
        memset(num, 0, sizeof(num));
    }
 
    bign (const char* number) {*this = number;}
 
    void DelZero ();
 
    void operator = (char* number);
 
    bign operator / (const int& b);
    int operator % (const int& b);
};
 
const int N = 1005;
const int MOD = 998244353;
 
int T;
char str[N];
bign n;
int bit[N], bn;
int dp[N][N * 2][2][2][2];
 
inline int add(int x, int y) {
    x += y;
	return x>=MOD?x-MOD:x ;
}
 
int dfs(int pos , int dif , bool flag , bool wild1 , bool wild2) {
	if (pos==-1) 
		return flag && dif>0 ;
	if (~dp[pos][dif +1000][flag][wild1][wild2])
		return dp[pos][dif +1000][flag][wild1][wild2] ;
	int f1 = wild1?bit[pos]:1 , f2 = wild2?bit[pos]:1 ;
	int ret = 0 ;

	for (int i=0 ; i<=f1 ; i++) {
		for (int j=0 ; j<=f2 ; j++) {
			bool tmp = 0 ;
			if (flag == 0) {
				if (i>j) continue ;
				if (i<j) tmp = 1 ;
			}
			ret = add (ret , dfs(pos-1,dif+i-j,flag||tmp,wild1&(i==f1),wild2&(j==f2)) ) ;
		}
	}
	dp[pos][dif +1000][flag][wild1][wild2] = ret ;
	return ret ;
}

int bitcount(int x) {
	int ans = 0;
	while (x) {
		ans += (x&1);
		x >>= 1;
	}
	return ans;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		memset (dp , -1 , sizeof(dp)) ;
		scanf("%s", str);
		n = str;
		bn = 0;
		while (n.len != 1 || n.num[0] != 0LL) {
			n = (n / 2);
			bit[bn++] = s;
		}
		//for (int i = 0 ; i < bn ; i ++) printf ("%d" ,bit[i]) ; puts ("") ;
		printf("%d\n", dfs(bn-1,0,0,1,1));
	}
	return 0;
}



/*********************************************/

void bign::DelZero () {
	while (len && num[len-1] == 0) len--;
	if (len == 0) num[len++] = 0;
}

void bign::operator = (char* number) {
	len = strlen(number);
	for (int i = 0; i < len; i++)
		num[i] = number[len - i - 1] - '0';
	DelZero ();
}

bign bign::operator / (const int& b) {
	bign ans;
	s = 0;
	for (int i = len - 1; i >= 0; i--) {
		s = s * 10 + num[i];
		ans.num[i] = s / b;
		s %= b;
	}
	ans.len = len;
	ans.DelZero();
	return ans;
}

