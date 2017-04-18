#include<bits/stdc++.h>
using namespace std;

const int M = 510;
const double inf = 1e13;
const double eps = 1e-9;

double d[50][50];

inline int Sign(double x) {
	return x < -eps ? -1 : x > eps;
}

struct AC {
	int go[M][50];
	int fail[M];
	bool end[M];
	int rt;
	int o;
	int fn;

	inline int NewNode() {
		for (int i=0; i<fn; ++i) {
			go[o][i] = -1;
		}
		end[o] = false;
		return o++;
	}

	void Init (int _fn) {
		fn = _fn;
		o = 0;
		rt = NewNode();
	}

	inline void Ins (int *s,int n) {
		int now = rt;
		for (int i=0; i<n; ++i) {
			if (go[now][s[i]] == -1) {
				go[now][s[i]] = NewNode();
			}
			now = go[now][s[i]];
		}
		end[now] = true;
	}

	void Fail() {
		queue<int> q;
		for (int i=0; i<fn; ++i) {
			if (go[rt][i] == -1) {
				go[rt][i] = rt;
			} else {
				fail[go[rt][i]] = rt;
				q.push (go[rt][i]);
			}
		}
		while (!q.empty()) {
			int now = q.front(); q.pop();
			for (int i=0; i<fn; i++) {
				if (go[now][i] == -1) {
					go[now][i] = go[fail[now]][i];
				} else {
					fail[go[now][i]] = go[fail[now]][i];
					end[go[now][i]] |= end[go[fail[now]][i]];
					q.push(go[now][i]);
				}
			}
		}
	}

	struct Node {
		double d;
		int u;
		int v;//以哪种形式被访问到节点 u
		Node (double _d,int _u,int _v):d(_d),u(_u),v(_v) {}
		inline bool operator < (const Node &rhs) const {
			return d > rhs.d;
		}
	};

	double dis[M][50];
	bool vis[M][50];
	void Solve() {
		for (int i=0; i<o; ++i) {
			for (int j=0; j<fn; ++j) {
				dis[i][j] = inf;
				vis[i][j] = false;
			}
		}
		dis[go[rt][0]][0] = 0;
		priority_queue<Node> q;
		q.push(Node(0, go[rt][0], 0));
		while (!q.empty()) {
			Node now = q.top(); q.pop();
			if (vis[now.u][now.v]) continue;
			vis[now.u][now.v] = true;
			//printf ("dis[%d][%d]=%.3f\n", now.u,now.v,dis[now.u][now.v]);
			for (int i=now.v+1; i<fn; ++i) {
				int _u = go[now.u][i];
				if (end[_u]) continue;
				if (vis[_u][i]==false && 
					dis[_u][i]>dis[now.u][now.v]+d[now.v][i]) {
					dis[_u][i] = dis[now.u][now.v] + d[now.v][i];
					//printf ("-->dis[%d][%d]=%.3f\n", _u, i, dis[_u][i]);
					q.push(Node(dis[_u][i], _u, i));
				}
			}
		}
		double ret = inf;
		for (int i=0; i<o; ++i) {
			ret = min(ret, dis[i][fn-1]);
		}
		if (Sign(ret-inf) == 0) {
			puts ("Can not be reached!");
		} else {
			printf ("%.2f\n", ret);
		}
	}
}ac;

struct Pt {
	double x, y;
}a[55];

inline double Dist (Pt a,Pt b) {
	return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

int main () {
	int n, m;
	int s[10];
	while (~scanf("%d%d",&n,&m) && n+m) {
		for (int i=0; i<n; ++i) {
			scanf ("%lf%lf", &a[i].x, &a[i].y);
		}
		for (int i=0; i<n; ++i) {
			for (int j=0; j<n; ++j) {
				d[i][j] = Dist(a[i], a[j]);
			}
		}
		ac.Init(n);
		for (int i=0, k; i<m; ++i) {
			scanf ("%d",&k);
			for (int j=0; j<k; ++j) {
				scanf ("%d", s+j);
				--s[j];
			}
			ac.Ins(s, k);
		}
		ac.Fail();
		ac.Solve();
	}
	return 0;
}
