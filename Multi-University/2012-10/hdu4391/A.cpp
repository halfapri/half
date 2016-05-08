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
#define fi first
#define se second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
int sign(double x){return x<-eps?-1:x>eps;}

struct BLOCK {
	map<int,int> mp ;
	int add ;
	void init (int n) {
		add=-1 ; mp.clear() ;
	}
} block[333] ;
int col[100010] ;
int blocks , block_len;
int n , m ;

void down (int id) {
	block[id].mp.clear () ;
	block[id].mp[block[id].add] = block_len ;
	for (int i=id*block_len ; i<(id+1)*block_len ; i++)
		 col[i] = block[id].add ;
	block[id].add = -1 ;
}

void ins(int id,int l,int r,int color) {
	if (block[id].add!=-1) down(id) ;
	block[id].mp[color] += r-l+1 ;
	for (int i=l ; i<=r ; i++) {
		--block[id].mp[col[i]] ;
		col[i] = color ;
	}
}

void ask (int &cnt,int id,int l,int r,int color) {
	if (block[id].add!=-1) down(id) ;
	for (int i=l ; i<=r ; i++) {
		if (col[i]==color) cnt ++ ;
	}
}

void solve () {
	while (m --) {
		int a,l,r,z;
		scanf ("%d%d%d%d",&a,&l,&r,&z) ;
		int st=l/block_len , ed=r/block_len ;
		int xl=block_len*(st+1)-1,rx=block_len*ed;
		if (a==1) {
			if(st==ed) ins(st,l,r,z) ;
			else ins(st,l,xl,z),ins(ed,rx,r,z) ;
			for (int i=st+1 ; i<=ed-1 ; i++) 
				block[i].add = z ;
		} else {
			int cnt=0 ;
			if(st==ed) ask(cnt,st,l,r,z) ;
			else ask(cnt,st,l,xl,z),ask(cnt,ed,rx,r,z) ;
			for (int i=st+1 ; i<=ed-1 ; i++) {  
				if (block[i].add==z) cnt+=block_len ;
				else if (block[i].add==-1 && block[i].mp.count(z)) cnt += block[i].mp[z] ;
			}
			printf ("%d\n" , cnt) ;
		}
	}
}

int main () {
	while (~ scanf ("%d%d",&n,&m)) {
		block_len = (int)sqrt(1.0*n+eps) ;
		blocks = n/block_len+1 ;
		for (int i=0 ; i<blocks ; i++) block[i].init(block_len) ;
		for (int i=0 ; i<n ; i++) {
			int x=i/block_len ;
			scanf ("%d",&col[i]) ;
			block[x].mp[col[i]] ++ ;
		}
		solve () ;
	}
	return 0 ;
}
