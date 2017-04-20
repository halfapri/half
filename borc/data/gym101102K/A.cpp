#include<bits/stdc++.h>
using namespace std;

#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r

const int M = 100000+10;
const int inf = 0x3f3f3f3f;

struct Node {
	int x;
	int in;
	int mk;
	inline void Mark (int _mk) {
		mk += _mk;
		in -= _mk;
	}
}T[M<<2];
int in[M];

struct SegTree {
	inline Node up(const Node &a,const Node &b) {
		Node ret;
		if (a.in >= b.in) {
			ret = b;
		} else {
			ret = a;
		}
		ret.mk = 0;
		return ret;
	}

	inline void down (int o) {
		T[o<<1].Mark(T[o].mk);
		T[o<<1|1].Mark(T[o].mk);
		T[o].mk = 0;
	}

	void build (int o,int l,int r) {
		T[o].mk = 0;
		if (l == r) {
			T[o].in = in[l];
			T[o].x = l;
			return;
		}
		int mid = l+r>>1;
		build (lson);
		build (rson);
		T[o] = up(T[o<<1], T[o<<1|1]);
	}

	void update (int o,int l,int r,int pl,int pr) {
		if (pl<=l && r<=pr) {
			T[o].Mark (1);
			return;
		}
		down (o);
		int mid = l+r>>1;
		if (pl<=mid) update (lson,pl,pr);
		if (pr>mid)  update(rson,pl,pr);
		T[o] = up(T[o<<1], T[o<<1|1]);
	}

	inline int ask() {
		return T[1].x;
	}

	void del (int o,int l,int r,int x) {
		if (l == r) {
			T[o].in = inf;
			return;
		}
		down(o);
		int mid = l+r>>1;
		if (x<=mid) del (lson,x);
		else del (rson,x);
		T[o] = up(T[o<<1], T[o<<1|1]);
	}
} sgt;

vector<int> g[M];
vector<int> ans;

int main () {
	int CASE;
	int n, m;
	scanf ("%d", &CASE);
	for (int cas=1; cas<=CASE; ++cas) {
		scanf ("%d%d", &n,&m);
		for (int i=1; i<=n; ++i) {
			in[i] = i-1;
			g[i].clear();
		}
		for (int i=0,u,v; i<m; ++i) {
			scanf ("%d%d", &u,&v);
			--in[v];
			g[u].emplace_back(v);
		}
		for (int i=1; i<=n; i++) {
			sort(g[i].begin(), g[i].end());
		}
		sgt.build(1,1,n);
		ans.clear();
		for (int i=0; i<n; i++) {
			int x = sgt.ask();
			ans.emplace_back(x);
			sgt.del(1,1,n,x);
			int l = x+1;
			for (int &r : g[x]) {
				if (l <= r-1) {
					//printf ("(%d, %d)\n", l, r-1);
					sgt.update (1,1,n,l,r-1);
				}
				l = r+1;
			}
			if (l<=n) {
				//printf ("(%d, %d)\n", l, n);
				sgt.update (1,1,n,l,n);
			}
		}
		for (int i=0; i<ans.size(); i++) {
			printf ("%d%c", ans[i], i==ans.size()-1?'\n':' ');
		}
	}
	return 0;
}
