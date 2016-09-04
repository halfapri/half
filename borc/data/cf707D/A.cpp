#include <stdio.h>
#include <bitset>
#include <string.h>
#include <stack>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <math.h>
#include <queue>
#include <complex>
#include <functional>
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
#define sqr(x) ((x)*(x))
#define ALL(v) (v).begin(),(v).end()
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

int n, m, Q;

struct Nodex {
	int v;
	Nodex *ls, *rs;
}poolx[100010*50], *NULLx=new Nodex;
int szx;
inline Nodex *alloc (Nodex *o=NULLx) {
	poolx[szx] = *o;
	return poolx + szx++;
}
void buildx (Nodex *o,int l,int r) {
	o->v = 0;
	if (l == r) return;
	int mid = l+r>>1;
	buildx (o->ls=alloc(NULLx),l,mid);
	buildx (o->rs=alloc(NULLx),mid+1,r);
}
void insx (Nodex *o,int l,int r,Nodex *u,int x,int val) {
	if (l == r) {u->v = val; return;}
	int mid = l+r>>1;
	if (x<=mid) insx (o->ls,l,mid,u->ls=alloc(o->ls),x,val);
	else insx (o->rs,mid+1,r,u->rs=alloc(o->rs),x,val);
	u->v = u->ls->v + u->rs->v;
}
//////////////////////////////////////////////////////////////////

struct Nodey {
	int v, rev;
	Nodey *ls, *rs;
	Nodex *rtx;
}pooly[100010*13], *NULLy=new Nodey;
int szy;
inline Nodey *alloc (Nodey *o) {
	pooly[szy] = *o;
	return pooly + szy++;
}
void buildy (Nodey *o,int l,int r) {
	o->v = o->rev = 0;
	if (l == r) {buildx (o->rtx=alloc(NULLx),1,m);return;}
	int mid = l+r>>1;
	buildy (o->ls=alloc(NULLy),l,mid);
	buildy (o->rs=alloc(NULLy),mid+1,r);
}
void insy (Nodey *o,int l,int r,Nodey *u,int x,int y,int op) {
	if (l == r) {
		u->rtx = alloc(o->rtx);
		if (op<=2) insx (o->rtx,1,m,u->rtx,y,u->rev ^ op==1);
		else u->rev ^= 1;
		u->v = u->rev ? m - u->rtx->v : u->rtx->v;
		return;
	}
	int mid = l+r>>1;
	if (x<=mid) insy (o->ls,l,mid,u->ls=alloc(o->ls),x,y,op);
	else insy (o->rs,mid+1,r,u->rs=alloc(o->rs),x,y,op);
	u->v = u->ls->v + u->rs->v;
}
//////////////////////////////////////////////////////////////////

Nodey *rt[100010];

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d%d%d", &n, &m, &Q)) {
		szx = szy = 0;
		buildy (rt[0]=alloc(NULLy),1,n);
		for (int i=1; i<=Q; i++) {int op,x,y;
			scanf ("%d", &op);
			if (op<=2) {
				scanf ("%d%d", &x,&y);
				insy (rt[i-1],1,n,rt[i]=alloc(rt[i-1]),x,y,op);
			} else if (op==3) {
				scanf ("%d", &x);
				insy (rt[i-1],1,n,rt[i]=alloc(rt[i-1]),x,y,op);
			} else {
				scanf ("%d", &x);
				rt[i] = alloc(rt[x]);
			}
			printf ("%d\n", rt[i]->v);
		} puts ("");
	}
	return 0;
}
