#include<bits/stdc++.h>
using namespace std;
const int mod = (int)1e9 + 7;

inline void add (int &a,int b) {
	a += b; if (a<0) a+=mod; if (a>=mod) a-=mod;
}

inline int ADD (int a,int b) {
	a += b; if (a<0) a+=mod; if (a>=mod) a-=mod;
	return a;
}

struct AC {
	int go[210][2];
	int fail[210];
	int end[210];
	int o;
	int rt;
	int rm[128];

	inline int NewNode() {
		for (int i=0; i<2; ++i) {
			go[o][i] = -1;
		}
		end[o] = 0;
		return o++;
	}

	inline void Init () {
		rm['R'] = 0;
		rm['D'] = 1;
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
		end[now] = 1<<type;
	}

	void Fail () {
		queue<int> q;
		for (int i=0; i<2; ++i) {
			if (go[rt][i] == -1) {
				go[rt][i] = rt;
			} else {
				fail[go[rt][i]] = rt;
				q.push (go[rt][i]);
			}
		}
		while (!q.empty()) {
			int now = q.front(); q.pop();
			for (int i=0; i<2; ++i) {
				if (go[now][i] == -1) {
					go[now][i] = go[fail[now]][i];
				} else {
					fail[go[now][i]] = go[fail[now]][i];
					end[go[now][i]] |= end[go[fail[now]][i]];
					q.push (go[now][i]);
				}
			}
		}
	}

	int dp[210][101][101][1<<2];
	int Solve(int n,int m) {
		for (int i=0; i<o; ++i) {
			for (int j=0; j<n+1; ++j) {
				for (int z=0; z<m+1; ++z) {
					for (int s=0; s<1<<2; ++s) {
						dp[i][j][z][s] = 0;
					}
				}
			}
		}
		dp[rt][0][0][0] = 1;
		for (int j=0; j<n+m; ++j) {
			for (int r=0; r<=j && r<=n; ++r) {
				int d = j-r;
				if (d>m) continue;
				for (int i=0; i<o; ++i) {
					for (int s=0; s<1<<2; ++s) {
						if (dp[i][r][d][s]==0) continue;
						for (int t=0; t<2; ++t) {
							int _r = r, _d = d;
							t == 0 ? ++_r : ++_d;
							if (_r>n || _d>m) continue;
							int _i = go[i][t];
							int _s = s | end[_i];
							add(dp[_i][_r][_d][_s], dp[i][r][d][s]);
							//printf ("dp(%d,%d,%d,%d)=%d --> dp(%d,%d,%d,%d)=%d\n",i,r,d,s,dp[i][r][d][s],_i,_r,_d,_s,dp[_i][_r][_d][_s]);
						}
					}
				}
			}
		}
		int ret=0;
		for (int i=0; i<o; ++i) {
			add(ret, dp[i][n][m][3]);
		}
		return ret;
	}
}ac;

int main () {
	int CASE;
	int n, m;
	char s[111];
	scanf ("%d", &CASE);
	for (int cas=1; cas<=CASE; ++cas) {
		scanf ("%d%d", &n,&m);
		ac.Init();
		scanf ("%s", s);
		ac.Ins(s, 0);
		scanf ("%s", s);
		ac.Ins(s, 1);
		ac.Fail();
		printf ("%d\n", ac.Solve(n, m));
	}
	return 0;
}
