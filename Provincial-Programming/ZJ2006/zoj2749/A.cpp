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

char s[11][11] ;
int n , m ;
int sx , sy , ex , ey ;
bool road[11][11] ;
int color = 0 ;
int step[4][2] = {{1,0},{0,1},{-1,0},{0,-1}} ;
int path[11][11] ;

struct node {
	int row , col ;
	node () {}
	node (int _row , int _col) : row(_row),col(_col) {}
	bool operator == (const node &rhs) const {
		return rhs.row==row&&rhs.col==col ;
	}
} ;

bool judge () {
	for (int i=1 ; i<n-1 ; i++) {
		for (int j=1 ; j<m-1 ; j++) {
			if ((road[i][j] && !path[i][j]) || (road[i][j]==0&&path[i][j]))
				return false ;
		}
	}
	return true ;
}

bool dfs (node now) {
	if (now==node(ex,ey)) {
		//printf ("end(%d,%d)\n" , now.row,now.col) ;
		return judge () ;
	}
	for (int i=0 ; i<4 ; i++) {
		node tmp = node (now.row+step[i][0],now.col+step[i][1]) ;
		if (tmp.row<0||tmp.col<0||tmp.row>=n||tmp.col>=m) continue ;
		if (path[tmp.row][tmp.col] || road[tmp.row][tmp.col]==0) continue ;

		path[tmp.row][tmp.col] = path[now.row][now.col]+1 ;
		if (dfs (tmp)) return true ;
		path[tmp.row][tmp.col] = 0 ;
	}
	return false ;
}

bool solve (int status) {
	memset (road , 0 , sizeof(road)) ;
	for (int i=1 ; i<n-1 ; i++) {
		char ch = status&1?'1':'2';
		for (int j=1 ; j<m-1 ; j++) {
			road[i][j] = s[i][j]==ch?0:1 ;
		}
		status>>= 1 ;
	}
	for (int i=0 ; i<n ; i++)
		road[i][0] = road[i][m-1] = 1 ;
	for (int i=0 ; i<m ; i++)
		road[0][i] = road[n-1][i] = 1 ;
	if (road[sx][sy]==0 || road[ex][ey]==0) return false ;

	memset (path , 0 , sizeof(path)) ;
	path[sx][sy] = 1 ;
	return dfs (node(sx,sy)) ;
}

void Print () {
	//puts ("") ;
	//for (int i=1 ; i<n-1 ; i++) {
	//	for (int j=1 ; j<m-1 ; j++) {
	//		printf ("%d" ,road[i][j]) ;
	//	} puts ("") ;
	//} puts ("") ;
	//for (int i=0 ; i<n ; i++) {
	//	for (int j=0 ; j<m ; j++) {
	//		printf ("%-4d" , path[i][j]) ;
	//	} puts ("") ;
	//} puts ("") ;

	//for (int i=0 ; i<n ; i++) {
	//	for (int j=0 ; j<m ; j++) {
	//		if (s[i][j]=='0') printf ("%c" , s[i][j]) ;
	//		else if (path[i][j]) printf ("%c" , s[i][j]=='1'?'2':'1') ;
	//		else printf ("%c" , s[i][j]) ;
	//	} puts ("") ;
	//} puts ("") ;
	printf ("%d\n" , path[ex][ey]) ;
	queue<node>q ;
	q.push (node(sx,sy)) ;
	while (!q.empty()) {
		node now=q.front() ; q.pop() ;
		if (now==node(ex,ey)) {
			printf ("%d %d\n" , ex,ey) ;
			break ;
		}
		else printf ("%d %d -> " , now.row,now.col) ;
		for (int i=0 ; i<4 ; i++) {
			node tmp=node(now.row+step[i][0],now.col+step[i][1]) ;
			if (tmp.row>=n||tmp.row<0||tmp.col<0||tmp.col>=m) continue ;
			if (path[tmp.row][tmp.col] != path[now.row][now.col]+1) continue ;
			q.push (tmp) ;
		}
	}
}

int main () {
	while (~ scanf ("%d%d",&n,&m)) {
		if (n==0&&m==0) break ;
		scanf ("%d%d%d%d",&sx,&sy,&ex,&ey) ;
		for (int i=0 ; i<n ; i++) {
			scanf ("%s" , s+i) ;
		}

		for (int i=0 ; i<(1<<(n-2)) ; i++) {
			if (solve(i)) {
				Print () ;
				break ;
			}
		}
	}
	return 0 ;
}
