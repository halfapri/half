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
const ll INF = (ll)1e18 ;

const int M = 20000+10 ;
char s[M] ;
int lens ;
char key1[M] , key2[M] ;
int beg1 , beg2 ;

inline int add (int a) {
	return a>=lens?a-lens:a ;
}

void maxway (char *s , char *key , int &beg) {
	int i = 0 , j = 1 , k = 0 ;
	while (i<lens && j<lens && k<lens) {
		int tmp = s[add(i+k)]-s[add(j+k)] ;
		if (tmp == 0) k ++ ;
		else {
			if (tmp>0) j += k+1 ;
			else i += k+1 ;
			if (i==j) j ++ ;
			k = 0 ;
		}
	}
	beg = min(i,j) ;
	for (int i = beg , j = 0 ; j < lens ; j ++ , i ++) {
		key[j] = s[add(i)] ;
	}
	key[lens] = '\0' ;
}


int nxt[M] ;
void get_nxt () {
	nxt[0] = -1 ;
	for (int i = 1 , j = -1 ; i < lens ; i ++) {
		while (j!=-1 && s[i]!=s[j+1]) j=nxt[j] ;
		nxt[i] = s[i]==s[j+1]?++j:-1 ;
	}
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf ("%d%s" , &lens , s) ;
		maxway(s,key1 , beg1) ;
		reverse(s , s+lens) ;
		maxway(s,key2 , beg2) ;

		get_nxt () ;
		int cycle = lens-1-nxt[lens-1] ;
		if (lens%cycle==0) 
			beg2 += (lens/cycle-1)*cycle;
		beg2 = lens-1-beg2 ;
		int flag = strcmp(key1,key2) ;
		if (flag==0) {
			if (beg1<=beg2) 
				printf ("%d %d\n" , beg1+1,0) ;
			else 
				printf ("%d %d\n" , beg2+1,1) ;
		}
		else
			flag>0?printf ("%d %d\n" , beg1+1,0) :
				printf ("%d %d\n" , beg2+1,1) ;
	}
	return 0 ;
}
