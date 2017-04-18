#include<bits/stdc++.h>
using namespace std;

const int M = 60000+10;
const int inf = 0x3f3f3f3f;
struct AC {
	int go[M][2];
	int fail[M];
	int end[M];//0: , 1:resource, 2:virus
	int rt;
	int o;
	int rm[128];
	vector<int> ss; //resource node
	int d[11][11];
	int dis[M];

	inline int NewNode() {
		for (int i=0; i<2; ++i) {
			go[o][i] = -1;
		}
		end[o] = 0;
		return o++;
	}

	inline int Init() {
		ss.clear();
		rm['0'] = 0;
		rm['1'] = 1;
		o = 0;
		rt = NewNode();
	}

	inline void Ins(char *s,int type) {
		int now = rt;
		for (; *s; ++s) {
			if (go[now][rm[*s]] == -1) {
				go[now][rm[*s]] = NewNode();
			}	
			now = go[now][rm[*s]];
		}
		if (type==1) {
			ss.emplace_back(now);
		}
		end[now] = type;
	}

	void Fail() {
		queue<int> q;
		for (int i=0; i<2; ++i) {
			if (go[rt][i] == -1) {
				go[rt][i] = rt;
			} else {
				fail[go[rt][i]] = rt;
				q.push(go[rt][i]);
			}
		}
		while (!q.empty()) {
			int now = q.front(); q.pop();
			for (int i=0; i<2; ++i) {
				if (go[now][i] == -1) {
					go[now][i] = go[fail[now]][i];
				} else {
					fail[go[now][i]] = go[fail[now]][i];
					if (end[go[now][i]] == 0) {
						end[go[now][i]] = end[fail[go[now][i]]];
					}
					q.push (go[now][i]);
				}
			}
		}
	}

	void BFS (int n) {
		queue<int> q;
		ss.emplace_back(rt);
		for (int beg=0; beg<n+1; beg++) {
			memset (dis, -1, sizeof(dis[0])*o);
			while (!q.empty()) q.pop();
			q.push(ss[beg]);
			dis[ss[beg]] = 0;
			while (!q.empty()) {
				int now = q.front(); q.pop();
				for (int i=0; i<2; i++) {
					if (dis[go[now][i]]!=-1 || end[go[now][i]]==2)continue;
					dis[go[now][i]] = dis[now] + 1;
					q.push (go[now][i]);
				}
			}
			for (int i=0; i<n+1; i++) {
				d[beg][i] = dis[ss[i]];
			}
		}
	}

	int dp[1<<10][10];
	int Solve(int n) {
		for (int i=0; i<1<<n; i++) {
			for (int j=0; j<n; j++) {
				dp[i][j] = inf;
			}
		}
//		for (int i=0; i<n+1; i++) {
//			for (int j=0; j<n+1; j++) {
//				printf ("%d ", d[i][j]);
//			} puts ("");
//		} puts ("");
		for (int i=0; i<n; i++) {
			dp[1<<i][i] = d[n][i];
			//printf ("d[%d][%d]=%d\n", n, i, d[n][i]);
		}
		for (int i=1; i<1<<n; i++) {
			for (int j=0; j<n; j++) {
				if ((i>>j & 1) == 0) continue;
				for (int z=0; z<n; z++) {
					if ((i>>z & 1) == 1) continue;
					dp[i | 1<<z][z] = min(dp[i | 1<<z][z],
							dp[i][j] + d[j][z]);
				}
			}
		}
		int ret = inf;
		for (int i=0; i<n; i++) {
			ret = min(ret, dp[(1<<n)-1][i]);
		}
		return ret;
	}
} ac;

char s[M];

int main () {
	int n, m;
	while (~scanf("%d%d", &n,&m) && n+m) {
		ac.Init();
		for (int i=0; i<n; i++) {
			scanf ("%s", s);
			ac.Ins(s, 1);
		}
		for (int i=0; i<m; i++) {
			scanf ("%s", s);
			ac.Ins(s, 2);
		}
		ac.Fail();
		ac.BFS(n);
		printf ("%d\n", ac.Solve(n));
	}
	return 0;
}
